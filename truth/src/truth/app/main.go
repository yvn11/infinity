package main

import (
  "github.com/golang/glog"
  "fmt"
  "os"
  "net"

  "github.com/urfave/cli"
  //"bitbucket.org/avd/go-ipc/mq"
  //"github.com/libp2p/go-libp2p-peer"
  _ "truth/app"
  esha3 "github.com/ethereum/go-ethereum/crypto/sha3"
  "golang.org/x/crypto/sha3"
  cfg "truth/config"
)

const (
  truth_mq_path = "/tmp/truth_prio.mq"
  max_mq_size = 100
  max_msg_size = 128
)

func invoke_rpc(ctx *cli.Context) error {
  glog.Info("invoke_rpc (%v)", ctx.Args())
  if len(ctx.Args()) == 0 {
    glog.Fatal("method not given")
    return cli.ShowCommandHelp(ctx, ctx.Command.Name)
  }
  return nil
}

func show_help(ctx *cli.Context) error {
  glog.Info("show_help (%v)", ctx.Command)

  return nil
}

func show_sys(ctx *cli.Context) error {
  glog.Info("show_sys (%v)", ctx.Command)
  data := []byte{32, 67, 15, 0, 9, 0, 10, 15}
//  data = make([]byte, 32)
  h := sha3.Sum256(data)
  glog.Info("%v", h)

  return nil
}

func show_network(ctx *cli.Context) error {
  glog.Info("show_network (%v)", ctx.Command)
  nss, err := net.LookupNS("google.com")
  if err != nil {
    glog.Fatal("Lookup NS failed", err)
  }

  for i, ns := range nss {
    glog.Info(i, ns.Host)
  }

  ifs, err := net.Interfaces()
  if err != nil {
    glog.Fatal("list interfaces failed", err)
  }

  for _, iface := range ifs {
    glog.Info(`
       Index: %d
       Name: %s
       MTU: %d
       Flag: %s
       MAC: %s`,
      iface.Index,
      iface.Name,
      iface.MTU,
      iface.Flags,
      iface.HardwareAddr)
  }

  addrs, err := net.InterfaceAddrs()
  if err != nil {
    glog.Fatal("list interfaces addrs failed", err)
  }

  for _, a := range addrs {
    glog.Info("%s: %s", a.Network(), a.String())
  }


  return nil
}

func main() {
  glog.Info("Truth App %s", cfg.VERSION)
  start_app()
}

func start_app() {
  app := cli.NewApp()
  app.Name = cfg.APP_NAME
  app.Usage = fmt.Sprintf("%s <subcommand>", app.Name)
  app.Version = cfg.VERSION
  app.Commands = []cli.Command{
    {
      Name: "sys",
      Usage: "show sys information",
      Action: show_sys,
    },
    {
      Name: "net",
      Usage: "show network information",
      Action: show_network,
    },
    {
      Name: "help",
      Usage: "show help message",
      Action: show_help,
    },
    {
      Name: "call",
      Usage: "call <method>",
      Action: invoke_rpc,
    },
  }
  app.Authors = []cli.Author{
    {
      Name: "Truth keeper",
      Email: "truth@feet.net",
    },
  }

  app.Run(os.Args)
}
