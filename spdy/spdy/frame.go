/**
 Reference SPDY Protocol Draft [https://tools.ietf.org/html/draft-mbelshe-httpbis-spdy-00]
*/
package spdy

import (
  "math"
)

type StreamID uint32

func validStreamID(id uint32) error {
  if id == 0 {
    return fmt.Errorf("Stream ID must not be zero")
  }
  if id > uint32(math.MaxInt32) {
    return fmt.Errorf("Stream ID too large")
  }
  return nil
}

var (
  SPDY_VERSION = uint32(3)
)

const (
  MAX_FRAME_SIZE = (1<<24)-1
  NUL = byte(0)
)

const (
  FlagFin = uint8(0x01) // the last frame
  FlagCompress = uint8(0x02) // data has been compressed
  FlagUnidirectional = uint8(0x02) // puts receipient in half-close state
  FlagSettingsPersistValue = uint8(0x01)
  FlagSettingsPersisted = uint8(0x02)
)

const (
  StatusSynReplyProtocolErr uint32 = iota + 1
  StatusSynReplyInvalidStream
  StatusSynReplyRefusedStream
  StatusSynReplyUnsupportedVersion
  StatusSynReplyCancel
  StatusSynReplyInternalErr
  StatusSynReplyFlowControlErr
  StatusSynReplyStreamInUse
  StatusSynReplyStreamAlreadyClosed
  StatusSynReplyInvalidCredentials
  StatusSynReplyFrameTooLarge
)

// Frame type
const (
  TypeSynStream = uint16(0x0001) // Open a new stream
  TypeSynReply = uint16(0x0002) // Remote acknowledgement of a new, open stream
  TypeRstStream = uint16(0x0003) // Close a stream
  TypeSettings = uint16(0x0004)
  TypePing = uint16(0x0006)
  TypeGoaway = uint16(0x0007)
  TypeHeaders = uint16(0x0008)
  TypeWindowUpdate = uint16(0x0009)
)

type Pairs map[uint32]string

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
  Control bool // indicates the frame is control frame or not
  Version uint32
  Type uint32
  Flags uint32
  Len uint32 // data length
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
type DataFrameHeader struct {
  Control bool // indicates the frame is control frame or not
  StreamID uint32
  Flags uint32
  Len uint32 // data length
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
  Priority uint8
  Unused uint8
  Slot uint8
  Entries Pairs
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
  Entries Pairs
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
  StatusCode uint32
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
  Entries Pairs
}

type GoawayFrame {
  Header ControlFrameHeader
  LastID StreamID
  StatusCode uint32
}

const (
  STATUS_GOAWAY_OK = uint32(0)
  STATUS_GOAWAY_PROTOCOL_ERROR = uint32(1)
  STATUS_GOAWAY_INTERNAL_ERROR = uint32(11)
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
func NewGoawayFrame() *GoawayFrame {
  return &GoawayFrame{
    Header: ControlFrameHeader{
      Control: 1,
      Version: SPDY_VERSION,
      Type: TypeGoaway,
      Len: 8,
    }
  }
}

type PingFrame struct {
  Header ControlFrameHeader
  ID StreamID
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
func NewPingFrame() *PingFrame {
  return &PingFrame{
    Header: ControlFrameHeader{
      Control: 1,
      Version: SPDY_VERSION,
      Type: TypeSettings,
      Len: 4,
    }
  }
}

const (
  ID_SETTINGS_UPLOAD_BANDWIDTH = uint32(1) // The value should be the integral number of kb/s
  ID_SETTINGS_DOWNLOAD_BANDWIDTH = uint32(2) // The value should be the integral number of kb/s
  ID_SETTINGS_ROUND_TRIP_TIME = uint32(3) // The value is represented in milliseconds
  ID_SETTINGS_MAX_CONCURRENT_STREAMS = uint32(4) // Value range 100 ~ inf
  ID_SETTINGS_CURRENT_CWND = uint32(5) // Inform peer the current TCP CWND value
  ID_SETTINGS_DOWNLOAD_RETRANS_RATE = uint32(6) // the retransmission rate
                                               // (bytes retransmitted / total bytes transmitted)
  ID_SETTINGS_INITIAL_WINDOW_SIZE = uint32(7)
  ID_SETTINGS_CLIENT_CERTIFICATE_VECTOR_SIZE = uint32(8)
)

type SettingsFrame struct {
  Header ControlFrameHeader
  Entries Pairs
}

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
func NewSettingsFrame() *SettingsFrame {
  return &SettingsFrame{
    Header: ControlFrameHeader{
      Control: 1,
      Version: SPDY_VERSION,
      Type: TypePing,
      Len: 4,
    }
  }
}

type WindowUpdate struct {
  Header ControlFrameHeader
  ID StreamID
  DeltaSize uint32 // 1 ~ 2^31 - 1 (0x7fffffff) bytes
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
func NewWindowUpdateFrame() *WindowUpdateFrame {
  return &WindowUpdateFrame{
    Header: ControlFrameHeader{
      Control: 1,
      Version: SPDY_VERSION,
      Type: TypeWindowUpdate,
      Len: 8,
    }
  }
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
  Slot uint32
  Proof string
  Certificates []string
}

func NewCredFrame() *CredFrame {
  return &CredFrame{
    Header: ControlFrameHeader{
      Control: 1,
      Version: SPDY_VERSION,
      Type: TypeSettings,
      Len: 4,
    }
  }
}
