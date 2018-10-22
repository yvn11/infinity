package spdy

import (
  "net"
)

type Connection struct {
  Conn net.Conn
}

func NewConnection(conn net.Conn) (Connection, error) {
  return Connection {
    Conn: conn
  }, nil
}
