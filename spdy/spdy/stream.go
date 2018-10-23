package spdy

type Stream struct {
  ID StreamID
  conn Connection
  frames FrameQueue
}
