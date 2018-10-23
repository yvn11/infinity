package main

import (
  "net"
  "fmt"
  "flag"
  "time"
  "sync"
  "github.com/clockworksoul/smudge"
)

var (
  CLUSTER_NAME = "gossip-1"
  ip = net.ParseIP("172.17.0.2")//127.0.0.1")
  lr = smudge.DefaultLogger{}
  self = ""
  listen_port = flag.Int("p", 0, "listen port")
  begin_port = flag.Int("b", 10000, "begin port")
  end_port = flag.Int("e", 10010, "end port")
)

type StatusListenerImpl struct {}

func (l StatusListenerImpl) OnChange(node *smudge.Node, status smudge.NodeStatus){
  lr.Logf(smudge.LogInfo, "[onchanged] %v, status:%s", node, status)
}

type BroadcastListenerImpl struct {}

func (l BroadcastListenerImpl) OnBroadcast(broadcast *smudge.Broadcast) {
  lr.Logf(smudge.LogInfo, "[%s:onbroadcast] %s: %s", self, broadcast.Label(), string(broadcast.Bytes()))
}

func greeting() {
  err := smudge.BroadcastString(fmt.Sprintf("hi there! this's %s", self))
  if err != nil {
    lr.Log(smudge.LogError, "broadcast failed: ", err)
  }
}

func createNodes() {
  for i := uint16(*begin_port); i <= uint16(*end_port); i++ {
    node, err := smudge.CreateNodeByIP(ip, i)
    if err != nil {
      lr.Log(smudge.LogError, "create node failed: ", err)
      continue
    }

    smudge.AddNode(node)
  }
}

func onUnreachable() {
  t := time.NewTimer(2*time.Second)
  <-t.C
  lr.Logf(smudge.LogInfo, "%v", time.Now())
}


func daemon() {
  wg := sync.WaitGroup{}
  for i := 10; i > 0; i-- {
    wg.Add(1)
    go onUnreachable()
  }
  wg.Wait()
}

func main() {
  flag.Parse()

  smudge.SetClusterName(CLUSTER_NAME)
  smudge.SetListenIP(ip)
  smudge.SetListenPort(*listen_port)

  self = fmt.Sprintf("%s:%d", smudge.GetListenIP(), smudge.GetListenPort())
  lr.Log(smudge.LogInfo, self)
  lr.Logf(smudge.LogInfo, "cluster: %s\n", smudge.GetClusterName())

  //daemon()
  createNodes()
  smudge.AddStatusListener(StatusListenerImpl{})
  smudge.AddBroadcastListener(BroadcastListenerImpl{})
  go func() {
    t := time.NewTimer(3*time.Second)
    <-t.C
    greeting()
  }()
  smudge.Begin()
}
