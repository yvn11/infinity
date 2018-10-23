/**
 Reference SPDY Protocol Draft [https://tools.ietf.org/html/draft-mbelshe-httpbis-spdy-00]
*/
package spdy

import (
  "errors"
  "math"
  "zlib"
  "bytes"
  "io"
  "encoding/binary"
)

type StreamID uint32

func validateStreamID(id StreamID) error {
  if id == 0 {
    return ErrZeroStreamID
  }
  if id > StreamID(math.MaxInt32) {
    return ErrLargeStreamID
  }
  return nil
}

func compress(buf *bytes.Buffer) error {
  w, err := zlib.NewWriterLevelDict(buf, zlib.BestCompression, HeaderDict)
  if err != nil {
    return err
  }
  defer w.Close()
  return w.Flush()
}

func decompress(data []byte) ([]byte, error) {
  buf := bytes.NewReader(data)
  r, err := zlib.NewReaderDict(buf, HeaderDict)
  if err != nil {
    return nil, err
  }
  defer r.Close()

  ret := new(bytes.Buffer)
  if _, err := io.Copy(ret, r); err != nil {
    return nil, err
  }
  return ret.Bytes(), nil
}

var (
  SpdyVersion = uint32(3)
  Endian = binary.BigEndian
)

var(
  ErrFrameSizeExceed = errors.New("Frame length exceeded")
  ErrZeroStreamID = errors.New("Stream ID must not be zero")
  ErrLargeSteamID = errors.New("Stream ID exceeded")
  ErrInvalidStatusCode = errors.New("Invalid status code")
  ErrInvalidWindowSizeDelta = errors.New("Illegal Window size delta")
)

const (
  MaxFrameSize = (1<<24)-1
  MinWindowSizeDelta = 1
  MaxWindowSizeDelta = (1<<31) - 1 // (0x7fffffff)
  Nul = byte(0)
)

type Flag uint8

const (
  FlagFin Flag = 0x01 // the last frame
  FlagCompress Flag = 0x02 // data has been compressed
  FlagUnidirectional Flag = 0x02 // puts receipient in half-close state
  FlagSettingsClearSettings Flag = 0x01
)

type IDFlag uint8

const (
  IDFlagSettingsPersistValue IDFlag = 0x01
  IDFlagSettingsPersisted IDFlag = 0x02
)

type RstStatus uint32

const (
  StatusRstProtocolErr RstStatus = iota + 1
  StatusRstInvalidStream
  StatusRstRefusedStream
  StatusRstUnsupportedVersion
  StatusRstCancel
  StatusRstInternalErr
  StatusRstFlowControlErr
  StatusRstStreamInUse
  StatusRstStreamAlreadyClosed
  StatusRstInvalidCredentials
  StatusRstFrameTooLarge
)

type Type uint16
// Frame type
const (
  TypeSynStream Type = 0x0001 // Open a new stream
  TypeSynReply Type = 0x0002 // Remote acknowledgement of a new, open stream
  TypeRstStream Type = 0x0003 // Close a stream
  TypeSettings Type = 0x0004
  TypePing Type = 0x0006
  TypeGoaway Type = 0x0007
  TypeHeaders Type = 0x0008
  TypeWindowUpdate Type = 0x0009
  TypeCredential Type = 0x000B
)

type NameVal map[string]string
type IDVal map[uint32]uint32

/**
   +----------------------------------+
   |C| Version(15bits) | Type(16bits) |
   +----------------------------------+
   | Flags (8)  |  Length (24 bits)   |
   +----------------------------------+
   |               Data               |
   +----------------------------------+
*/
type ControlFrameHeader struct {
  ctrl bool // indicates the frame is ctrl frame or not
  ver uint16
  t Type
  flags Flag
  l uint32 // data length
}

/**
   +----------------------------------+
   |C|       Stream-ID (31bits)       |
   +----------------------------------+
   | Flags (8)  |  Length (24 bits)   |
   +----------------------------------+
   |               Data               |
   +----------------------------------+
*/
type DataFrame struct {
  ctrl bool // indicates the frame is ctrl frame or not
  ID StreamID
  f Flag
  l uint32 // data length
  data []byte
}

/**
+------------------------------------+
|1|    version    |         1        |
+------------------------------------+
|  Flags (8)  |  Length (24 bits)    |
+------------------------------------+
|X|           Stream-ID (31bits)     |
+------------------------------------+
|X| Associated-To-Stream-ID (31bits) |
+------------------------------------+
| Pri|Unused | Slot |                |
+-------------------+                |
| Number of Name/Value pairs (int32) |   <+
+------------------------------------+    |
|     Length of name (int32)         |    | This section is the "Name/Value
+------------------------------------+    | Header Block", and is compressed.
|           Name (string)            |    |
+------------------------------------+    |
|     Length of value  (int32)       |    |
+------------------------------------+    |
|          Value   (string)          |    |
+------------------------------------+    |
|           (repeats)                |   <+
*/
type SynStreamFrame {
  Header ControlFrameHeader
  ID StreamID
  AssoID StreamID
  Priority uint8 // 3 bits
  // 5 bits unused
  Slot uint8 // 8 bits
  Entries NameVal
}

/**
+------------------------------------+
|1|    version    |         2        |
+------------------------------------+
|  Flags (8)  |  Length (24 bits)    |
+------------------------------------+
|X|           Stream-ID (31bits)     |
+------------------------------------+
| Number of Name/Value pairs (int32) |   <+
+------------------------------------+    |
|     Length of name (int32)         |    | This section is the "Name/Value
+------------------------------------+    | Header Block", and is compressed.
|           Name (string)            |    |
+------------------------------------+    |
|     Length of value  (int32)       |    |
+------------------------------------+    |
|          Value   (string)          |    |
+------------------------------------+    |
|           (repeats)                |   <+
*/
type SynReplyFrame {
  Header ControlFrameHeader
  AssoID StreamID
  Entries NameVal
}

/**
   +----------------------------------+
   |1|   version    |         3       |
   +----------------------------------+
   | Flags (8)  |         8           |
   +----------------------------------+
   |X|          Stream-ID (31bits)    |
   +----------------------------------+
   |          Status code             |
   +----------------------------------+
*/
type RstStreamFrame {
  Header ControlFrameHeader
  AssoID StreamID
  StatusCode RstStatus
}

/**
+------------------------------------+
|1|   version     |          8       |
+------------------------------------+
| Flags (8)  |   Length (24 bits)    |
+------------------------------------+
|X|          Stream-ID (31bits)      |
+------------------------------------+
| Number of Name/Value pairs (int32) |   <+
+------------------------------------+    |
|     Length of name (int32)         |    | This section is the "Name/Value
+------------------------------------+    | Header Block", and is compressed.
|           Name (string)            |    |
+------------------------------------+    |
|     Length of value  (int32)       |    |
+------------------------------------+    |
|          Value   (string)          |    |
+------------------------------------+    |
|           (repeats)                |   <+

*/
type HeadersFrame {
  Header ControlFrameHeader
  ID StreamID
  Entries NameVal
}

type GoawayStatus uint32

const (
  StatusGoawayOK GoawayStatus = 0
  StatusGoawayProtocolErr GoawayStatus = 1
  StatusGoawayInternalErr GoawayStatus = 11
)

/**
   +----------------------------------+
   |1|   version    |         7       |
   +----------------------------------+
   | 0 (flags) |     8 (length)       |
   +----------------------------------|
   |X|  Last-good-stream-ID (31 bits) |
   +----------------------------------+
   |          Status code             |
   +----------------------------------+
*/
type GoawayFrame {
  Header ControlFrameHeader
  LastID StreamID
  StatusCode GoawayStatus
}

/**
   +----------------------------------+
   |1|   version    |         6       |
   +----------------------------------+
   | 0 (flags) |     4 (length)       |
   +----------------------------------|
   |            32-bit ID             |
   +----------------------------------+
*/
type PingFrame struct {
  Header ControlFrameHeader
  ID StreamID
}

type SettingsID uint32

const (
  SettingsUploadBandwidth SettingsID = iota + 1 // The value should be the integral number of kb/s
  SettingsDownloadBandwidth // The value should be the integral number of kb/s
  SettingsRoundTripTime // The value is represented in milliseconds
  SettingsMaxConcurrentStreams // Value range 100 ~ inf
  SettingsCurrentCWND // Inform peer the current TCP CWND value
  SettingsDownloadRetransRate // the retransmission rate
                                               // (bytes retransmitted / total bytes transmitted)
  SettingsInitialWindowSize
  SettingsClientCertificateVectorSize
)

/**
   +----------------------------------+
   |1|   version    |         4       |
   +----------------------------------+
   | Flags (8)  |  Length (24 bits)   |
   +----------------------------------+
   |         Number of entries        |
   +----------------------------------+
   |          ID/Value Pairs          |
   |             ...                  |
*/
type SettingsFrame struct {
  Header ControlFrameHeader
  // Entry ID = ID Flag(8 bits) + Settings ID(24)
  // ID-value mapping
  Entries IDVal
}

/**
   +----------------------------------+
   |1|   version    |         9       |
   +----------------------------------+
   | 0 (flags) |     8 (length)       |
   +----------------------------------+
   |X|     Stream-ID (31-bits)        |
   +----------------------------------+
   |X|  Delta-Window-Size (31-bits)   |
   +----------------------------------+
*/
type WindowUpdate struct {
  Header ControlFrameHeader
  ID StreamID
  DeltaSize uint32 // 1 ~ 2^31 - 1 (0x7fffffff) bytes
}

/**
  +----------------------------------+
  |1|000000000000001|0000000000001011|
  +----------------------------------+
  | flags (8)  |  Length (24 bits)   |
  +----------------------------------+
  |  Slot (16 bits) |                |
  +-----------------+                |
  |      Proof Length (32 bits)      |
  +----------------------------------+
  |               Proof              |
  +----------------------------------+ <+
  |   Certificate Length (32 bits)   |  |
  +----------------------------------+  | Repeated until end of frame
  |            Certificate           |  |
  +----------------------------------+ <+
*/
type CredFrame struct {
  Header ControlFrameHeader
  Slot uint16
  Proof string
  Certificates []string
}

type RawFrame interface {
  F
  Write(conn *net.Conn) (error)
  Read(conn *net.Conn) (interface{}, error)
}
