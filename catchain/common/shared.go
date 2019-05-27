package common

import (
  "os"
  "path"
)

var (
  StorePath = path.Join(os.Getenv("HOME"), "catchain")
)
