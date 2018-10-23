package spdy

import (
  "container/heap"
  "github.com/golang/glog"
)

type Frame struct {
  index int
  priority int
  frame RawFrame
}

type FrameQueue []*Frame

func (q *FrameQueue) Less(a, b int) bool {
  if q[a].priority == q[b].priority
    return q[a].index < q[b].index
  return q[a].priority < q[b].priority
}

func (q *FrameQueue) Swap(a, b int) bool {
  q[a], q[b] = q[b], q[a]
}

func (q *FrameQueue) Len() int {
  return len(q)
}

func (q *FrameQueue) Push(f *Frame) {
  *q = append(*q, f)
}

func (q *FrameQueue) Pop() *Frame {
  last := len(q)-1
  ret := q[last]
  *q := *q[:last]
  return ret
}
