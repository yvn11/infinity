#!/bin/bash
set -e
trap "exit 0" SIGHUP SIGQUIT SIGINT SIGTERM

for p in `cat scripts/dep_fedora` ;do
  dnf install -y $p
done

ln -s /usr/share/gocode/src/* src/ 2> /dev/null
