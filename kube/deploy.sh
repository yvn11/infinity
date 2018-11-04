
docker exec -it hyperkube-installer /bin/bash

export K8S_VERSION=$(curl -sS https://storage.googleapis.com/kubernetes-release/release/stable.txt)
export ARCH=amd64

curl -sSL "http://storage.googleapis.com/kubernetes-release/release/$K8S_VERSION/bin/linux/$ARCH/kubectl" > /usr/bin/kubectl
chmod +x /usr/bin/kubectl

kubectl get nodes
kubectl get pods
kubectl get namespaces

kubectl run nginx --image=nginx --port=80 ; exit


kubectl get service nginx
ip=$(kubectl get svc nginx --template={{.spec.clusterIP}}

curl "http://$ip:8080"
