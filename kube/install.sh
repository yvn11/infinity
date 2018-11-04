#export K8S_VERSION=$(curl -sS https://storage.googleapis.com/kubernetes-release/release/stable.txt)
export K8S_VERSION=v1.12.2
export ARCH=amd64

docker run -d --volume=/:/rootfs:ro \
--volume=/sys:/sys:rw --volume=/var/lib/docker/:/var/lib/docker:rw \
--volume=/var/lib/kubelet/:/var/lib/kubelet:rw --volume=/var/run:/var/run:rw \
--net=host --pid=host --name=hyperkube-installer \
--privileged gcr.io/google_containers/hyperkube-${ARCH}:${K8S_VERSION}\  
/hyperkube kubelet --containerized \
--hostname-override=127.0.0.1 --api-servers=http://localhost:8080 \
--config=/etc/kubernetes/manifests --allow-privileged --v=2
