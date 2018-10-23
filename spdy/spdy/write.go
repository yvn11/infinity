package spdy

import (
  "net"
  "fmt"
  "encoding/binary"
)

func (f *ControlFrameHeader) Write(buf *bytes.Buffer) error {
  if err := binary.Write(buf, Endian, f.ctrl); err != nil {
    return err
  }

  if err := binary.Write(buf, Endian, f.ver); err != nil {
    return err
  }

  if err := binary.Write(buf, Endian, f.t); err != nil {
    return err
  }

  if err := binary.Write(buf, Endian, f.flags); err != nil {
    return err
  }

  return binary.Write(buf, Endian, f.l)
}

func (e *NameVal) Write(buf *bytes.Buffer) error {
  n_pairs := len(e)
  if err := binary.Write(buf, Endian, n_pairs); err != nil {
    return err
  }

  for k, v := range e {
    nk := len(k)
    if err := binary.Write(buf, Endian, nk); err != nil {
      return err
    }
    if err := binary.Write(buf, Endian, k); err != nil {
      return err
    }

    nv := len(v)
    if err := binary.Write(buf, Endian, nv); err != nil {
      return err
    }
    if err := binary.Write(buf, Endian, v); err != nil {
      return err
    }
  }

  return compress(buf)
}

func (e *IDVal) Write(buf *bytes.Buffer) error {
  n_pairs := len(e)
  if err := binary.Write(buf, Endian, n_pairs); err != nil {
    return err
  }

  for k, v := range e {
    if err := binary.Write(buf, Endian, k); err != nil {
      return err
    }

    if err := binary.Write(buf, Endian, v); err != nil {
      return err
    }
  }

  return nil
}
func writeData(data []byte, conn *net.Conn) error {
  if len(data) > MaxFrameSize {
    return ErrFrameSizeExceed
  }

  _, err := conn.Write(data)
  if err != nil {
    return err
  }
  return nil
}

func (f *SynStreamFrame) Write(conn *net.Conn) error {
  if err := validateStreamID(f.ID); err != nil {
    return err
  }

  var buf, nvbuf bytes.Buffer

  if err := f.Entries.Write(&nvbuf); err != nil {
    return err
  }

  f.Header.ctrl = true
  f.Header.ver = SpdyVersion
  f.Header.t = TypeSynStream
  f.Header.flags = FlagFin
  f.Header.l = 10 + len(nvbuf.Bytes())

  if err := f.Header.Write(&buf); err != nil {
    return err
  }

  if err := binary.Write(buf, Endian, f.ID); err != nil {
    return err
  }

  if err := binary.Write(buf, Endian, f.AssoID); err != nil {
    return err
  }

  if err := binary.Write(buf, Endian, f.Priority << 5); err != nil {
    return err
  }

  if err := binary.Write(buf, Endian, f.Slot); err != nil {
    return err
  }

  buf.Write(nvbuf.Bytes())
  return writeData(buf.Bytes(), conn)
}

func (f *SynReplyFrame) Write(conn *net.Conn) error {
  var buf, nvbuf bytes.Buffer

  if err := f.Entries.Write(&nvbuf); err != nil {
    return err
  }

  f.Header.ctrl = true
  f.Header.ver = SpdyVersion
  f.Header.t = TypeSynReply
  f.Header.flags = FlagFin
  f.Header.l = 4 + len(nvbuf.Bytes())

  if err := f.Header.Write(&buf); err != nil {
    return err
  }

  if err := binary.Write(buf, Endian, f.AssoID); err != nil {
    return err
  }

  buf.Write(nvbuf.Bytes())
  return writeData(buf.Bytes())
}

func (f *RstStreamlFrame) Write(conn *net.Conn) error {
  var buf bytes.Buffer

  f.Header.ctrl = true
  f.Header.ver = SpdyVersion
  f.Header.t = TypeRstStream
  f.Header.flags = FlagFin
  f.Header.l = 8

  if err := f.Header.Write(&buf); err != nil {
    return err
  }

  if err := binary.Write(buf, Endian, f.AssoID); err != nil {
    return err
  }

  if f.StatusCode == 0 {
    return ErrInvalidStatusCode
  }

  if err := binary.Write(buf, Endian, f.StatusCode); err != nil {
    return err
  }

  return writeData(buf.Bytes())
}

func (f *HeadersFrame) Write(conn *net.Conn) error {
  if err := validateStreamID(f.ID); err != nil {
    return err
  }

  var buf, nvbuf bytes.Buffer

  if err := f.Entries.Write(&nvbuf); err != nil {
    return err
  }

  f.Header.ctrl = true
  f.Header.ver = SpdyVersion
  f.Header.t = TypeHeaders
  f.Header.flags = FlagFin
  f.Header.l = 4 + len(nvbuf.Bytes())

  if err := f.Header.Write(&buf); err != nil {
    return err
  }

  if err := binary.Write(buf, Endian, f.ID); err != nil {
    return err
  }

  buf.Write(nvbuf.Bytes())
  return writeData(buf.Bytes(), conn)
}

func (f *GoawayFrame) Write(conn *net.Conn) error {
  var buf bytes.Buffer

  f.Header.ctrl = true
  f.Header.ver = SpdyVersion
  f.Header.t = TypeGoaway
  f.Header.flags = 0
  f.Header.l = 8

  if err := f.Header.Write(&buf); err != nil {
    return err
  }

  // TODO get last ID used by SYN_REPLY or RST_STREAM
  if err := binary.Write(buf, Endian, f.LastID); err != nil {
    return err
  }

  if err := binary.Write(buf, Endian, f.StatusCode); err != nil {
    return err
  }

  return writeData(buf.Bytes(), conn)
}

func (f *PingFrame) Write(conn *net.Conn) error {
  if err := validateStreamID(f.ID); err != nil {
    return err
  }

  var buf bytes.Buffer

  f.Header.ctrl = true
  f.Header.ver = SpdyVersion
  f.Header.t = TypePing
  f.Header.flags = 0
  f.Header.l = 4

  if err := f.Header.Write(&buf); err != nil {
    return err
  }

  if err := binary.Write(buf, Endian, f.ID); err != nil {
    return err
  }

  return writeData(buf.Bytes(), conn)
}

func (f *SettingsFrame) Write(conn net.Conn) error {
  var buf, ivbuf bytes.Buffer

  if err := f.Entries.Write(&ivbuf); err != nil {
    return err
  }

  f.Header.ctrl = true
  f.Header.ver = SpdyVersion
  f.Header.t = TypeSettings
  //f.Header.flags = 0
  f.Header.l = len(ivbuf.Bytes())

  if err := f.Header.Write(&buf); err != nil {
    return err
  }

  buf.Write(ivbuf.Bytes())
  return writeData(buf.Bytes(), conn)
}

func (f *WindowUpdateFrame) Write(conn *net.Conn) error {
  if err := validateStreamID(f.ID); err != nil {
    return err
  }

  var buf bytes.Buffer

  f.Header.ctrl = true
  f.Header.ver = SpdyVersion
  f.Header.t = TypeWindowUpdate
  f.Header.flags = 0
  f.Header.l = 8

  if err := f.Header.Write(&buf); err != nil {
    return err
  }

  if err := binary.Write(buf, Endian, f.ID); err != nil {
    return err
  }

  if f.DeltaSize < MinWindowSizeDelta || f.DeltaSize > MaxWindowSizeDelta {
    return ErrInvalidWindowSizeDelta
  }

  if err := binary.Write(buf, Endian, f.DeltaSize); err != nil {
    return err
  }

  return writeData(buf.Bytes(), conn)
}

func (f *CredFrame) Write(conn *net.Conn) error {
  return nil
}
