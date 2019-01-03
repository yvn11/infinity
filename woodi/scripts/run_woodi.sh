#!/bin/bash

# local debug
export WOODI_ROOT=/opt/woodi
export PYTHONPATH=/opt/woodi:`pwd`
export KAFKA_BROKERS=192.168.100.220:17812,192.169.100.35:17813,192.168.100.94:17814
export CONSUMERS=IMsg
export PRODUCERS=IMsg
#ZOOKEEPER=192.168.100.220:2171,192.168.100.189:2171,192.168.100.140:2171

#source config/woodi-env
#python3 ./woodi/input/producer_entry.py
python3 ./woodi/output/consumer_entry.py
