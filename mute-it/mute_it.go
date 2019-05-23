package main

import (
  "html/template"
  "net/http"
  "time"
  "fmt"
)

type About struct{
  Today string
  FirstName string
  LastName string
}

func handleAbout(w http.ResponseWriter, r *http.Request) {
  about := About{
    Today : time.Now().Format("dd-mm-yyyy"),
    FirstName: "Zex",
    LastName: "Li",
  }

  templ := template.Must(template.ParseFiles("templates/mute_it.html"))
  if err := templ.Execute(w, about); err != nil {
    http.Error(w, err.Error(), http.StatusInternalServerError)
  }
}

func main() {
  http.HandleFunc("/", handleAbout)
  http.Handle("/static/",
    http.StripPrefix("/static/", http.FileServer(http.Dir("static"))))
  if err := http.ListenAndServe(":31542", nil); err != nil {
      fmt.Println("[muteit] start failed", err)
  }
}
