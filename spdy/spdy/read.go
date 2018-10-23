package spdy

import (
  "net"
  "fmt"
)

func ReadRawFrame(conn *net.Conn) (interface{}, error) {
  var buf4 uint32
  if err := binary.Read(conn, Endian, &buf) {
    return struct{}, err
  }

  if (buf4 & 0x80000000) == 0 { // data frame
    return readDataFrame(buf4, conn)
  }

  ver := uint16(buf4 & 0x0fff0000)
  ty := uint16(buf4 & 0x0000ffff)

  if err := binary.Read(conn, Endian, &buf) {
    return struct{}, err
  }

  fl := (buf4 & 0xff000000) >> 24
  l := buf4 & 0x00ffffff

  data := make([]byte, l)
  if err := conn.Read(conn, Endian, data) {
    return struct{}, err
  }

  return createCtrlFrame(ControlFrameHeader{
    ctrl: true, ver: ver, t: ty,
    flags: fl, l: l}, conn)
}

func createCtrlFrame(h ControlFrameHeader, conn *net.Conn) (interface{}, error) {
  var fr RawFrame

  switch h.t {
    case TypeSynStream: fr.F = new(SynStreamFrame)
    case TypeSynReply: fr.F = new(SynReplyFrame)
    case TypeRstStream: fr.F = new(RstStreamFrame)
    case TypeSettings: fr.F = new(SettingsFrame)
    case TypePing: fr.F = new(PingFrame)
    case TypeGoaway: fr.F = new(GoawayFrame)
    case TypeHeaders: fr.F = new(HeadersFrame)
    case TypeWindowUpdate: fr.F = new(WindowUpdateFrame)
    case TypeCredential: fr.F = new(CredentialFrame)
    default: return struct{}, ErrIllegalFrameType
  }

  if err := fr.F.Read(h, conn); err != nil {
    return struct{}, err
  }
  return fr, nil
}

func readDataFrame(buf4 uint32, conn &net.Conn) (interface{}, error) {
  return struct{}, nil
}

func (f *SynStreamFrame) Read(h ControlFrameHeader, conn *net.Conn) error {
  var buf4 uint32
  f.Header = h

  if err := binary.Read(conn, Endian, &buf4); err != nil {
    return err
  }
  f.ID = buf4 & 0x7fffffff

  if err := binary.Read(conn, Endian, &buf4); err != nil {
    return err
  }
  f.AssoID = buf4 & 0x7fffffff

  if err := binary.Read(conn, Endian, &f.Priority); err != nil {
    return err
  }
  f.Priority >>= 5

  if err := binary.Read(conn, Endian, &f.Slot); err != nil {
    return err
  }

  if err := binary.Read(conn, Endian, &buf4); err != nil {
    return err
  }

  return nil
}

func (f *SynReplyFrame) Read(h ControlFrameHeader, conn *net.Conn) error {
  return nil
}

func (f *RstStreamlFrame) Read(h ControlFrameHeader, conn *net.Conn) error {
  data, err := decompress(conn.Read())
  return nil
}

func (f *HeaderFrame) Read(h ControlFrameHeader, conn *net.Conn) error {
  return nil
}

func (f *GoawayFrame) Read(h ControlFrameHeader, conn *net.Conn) error {
  return nil
}

func (f *PingFrame) Read(h ControlFrameHeader, conn *net.Conn) error {
  return nil
}

func (f *SettingsFrame) Read(h ControlFrameHeader, conn net.Conn) error {
  return nil
}

func (f *WindowUpdateFrame) Read(h ControlFrameHeader, conn *net.Conn) error {
  return nil
}

func (f *CredFrame) Read(h ControlFrameHeader, conn *net.Conn) error {
  return nil
}
