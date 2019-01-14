#!/bin/bash

kubectl proxy --address 0.0.0.0 --accept-hosts '.*' &
