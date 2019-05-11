#!/bin/bash

dest=$1
if [[ -z $dest ]] ;then echo "dest not given"; exit -1; fi
user=ubuntu

ssh $user@$dest "mkdir /home/$user/.kube -p"
rsync -rA /etc/kubernetes/admin.conf ubuntu@$dest:/home/$user/.kube/admin.conf
ssh $user@$dest "sudo chown $(id -u):$(id -g) /home/$user/.kube/admin.conf"
rsync -rA /usr/lib/systemd/system/kubelet.service ubuntu@$dest:.zex/
