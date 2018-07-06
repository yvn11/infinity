docker run -it --name zookeeper -v zk-data:/data -v zk-log:/datalog -p 2181:2181 -p 2888:2888 -p 3888:3888 docker.io/zookeeper
