#!/bin/bash

# local debug
export WOODI_ROOT=/opt/woodi
export PYTHONPATH=/opt/woodi:`pwd`
export KAFKA_BROKERS=192.168.100.140:17810
export CONSUMERS=IMsg
export PRODUCERS=IMsg

#source config/woodi-env
python3 ./woodi/input/producer_entry.py
