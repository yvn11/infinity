#!/bin/bash

ISTIO_VERSION=1.0.3
#wget -c https://github.com/istio/istio/archive/$ISTIO_VERSION.zip && \
# unzip $ISTIO_VERSION.zip

#curl -o istio-$ISTIO_VERSION-linux.tar.gz https://github.com/istio/istio/releases/download/$ISTIO_VERSION/istio-$ISTIO_VERSION-linux.tar.gz
#tar xf istio-$ISTIO_VERSION-linux.tar.gz
#curl -L https://git.io/getLatestIstio | sh -

# uninstall
#kubectl delete -f install/kubernetes/helm/istio/templates/crds.yaml -n istio-system

# setup custom resource definitions
kubectl apply -f istio-1.0.3/install/kubernetes/helm/istio/templates/crds.yaml -n istio-system
# setup istio core components
kubectl apply -f istio-1.0.3/install/kubernetes/istio-demo.yaml
# label istio enabled
kubectl label namespace default istio-injection=enabled --overwrite=true
# inject istio 
ISTIOCTL=istio-1.0.3/bin/istioctl
if [[ ! -f "$ISTIOCTL" ]] ;then 
  echo "$ISTIOCTL not found"
  ISTIOCTL_CMD=istio-1.0.3/istioctl/cmd/istioctl
  if [[ ! -f "$ISTIOCTL_CMD" ]] ;then
    echo "$ISTIOCTL_CMD not found, abort"
    exit -1 
  fi
  echo "using $ISTIOCTL_CMD"
  ln -s -r $ISTIOCTL_CMD $ISTIOCTL
fi
istio-1.0.3/bin/istioctl kube-inject -f kube/istio-deployment.yaml |kubectl apply -f -
