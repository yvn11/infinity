package phi

import (
  "runtime"
)

func CurrentScope() (string) {
  pc := make([]uintptr, 10)
  if 0 == runtime.Callers(2, pc) {
    return ""
  }

  frames := runtime.CallersFrames(pc)
  fr, _ := frames.Next()
  return fr.Function
}
