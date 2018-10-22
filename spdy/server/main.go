package main

import (
  "fmt"
  "net"
  "flag"
  "spdy"
)

var (
  listen_port = flag.Int("p", 17310, "listen port")
)

func forward_spdy(conn net.Conn) {
  spdy_conn, err := spdy.NewConnection(conn)
  if err != nil {
    fmt.Println("forward to spdy failed: ", err)
    return
  }
  go spdy_conn.Serve()
}

func main() {
  flag.Parse()
  l, err := net.Listen("tcp", fmt.Sprint(":%d", listen_port))
  if err != nil {
    fmt.Println("launch failed", err)
    return
  }

  for {
    conn, err := net.Accept()
    if err != nil {
      fmt.Println("accept failed: ", err)
      break
    }
    go forward_spdy(conn)
  }
}
