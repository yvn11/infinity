#!/bin/bash

systemctl restart etcd\
 kube-controller-manager\
 kube-apiserver\
 kube-scheduler
