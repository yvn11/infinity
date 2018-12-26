#!/bin/bash

# local debug
export WOODI_ROOT=/opt/woodi
export PYTHONPATH=/opt/woodi:`pwd`
export KAFKA_BROKERS=192.168.100.189:17812,192.168.100.35:17812,192.168.100.94:17812
export CONSUMERS=IMsg
export PRODUCERS=IMsg

#source config/woodi-env
#python3 ./woodi/input/producer_entry.py
python3 ./woodi/output/consumer_entry.py
