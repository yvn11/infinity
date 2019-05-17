package main

import (
  "html/template"
  "net/http"
  "time"
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

  templ := template.Must(template.ParseFiles("templates/about.html"))
  if err := templ.Execute(w, about); err != nil {
    http.Error(w, err.Error(), http.StatusInternalServerError)
  }
}

func main() {
  http.HandleFunc("/", handleAbout)
  http.Handle("/static/",
    http.StripPrefix("/static/", http.FileServer(http.Dir("static"))))
  http.ListenAndServe(":31542", nil)
}
