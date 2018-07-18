package main

import (
  "log"
  "fmt"
  "os"

  "github.com/urfave/cli"
  cfg "truth/config"
)

func show_help(ctx *cli.Context) error {
  log.Printf("show_help (%v)", ctx.Command)
  return nil
}

func show_network(ctx *cli.Context) error {
  log.Printf("show_network (%v)", ctx.Command)
  return nil
}

func main() {
  log.Printf("Truth App %s", cfg.VERSION)
  start_app()
}

func start_app() {
  app := cli.NewApp()
  app.Name = cfg.APP_NAME
  app.Usage = fmt.Sprintf("%s <subcommand>", app.Name)
  app.Version = cfg.VERSION
  app.Commands = []cli.Command{
    {
      Name: "sn",
      Usage: "show network information",
      Action: show_network,
    },
    {
      Name: "help",
      Usage: "show help message",
      Action: show_help,
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
