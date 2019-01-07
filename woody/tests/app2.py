def main():
    global db_table;
    global producer;
    if len(sys.argv) != 3:
        #print("Usage: thisfile.py <zk> <topic>", file=sys.stderr) #i get an error about file=sys.stderr for some reason
        print("Usage: thisfile.py <zk> <topic>")
        exit(-1)

    #ssc.checkpoint("hdfs://ec2-52-41-224-1.us-west-2.compute.amazonaws.com:9000/imgSrchRqstCkpts")
    #example of what can be done
    #db_table=sc.cassandraTable(keyspace,"vname") #doesn't work
    print("about to do map and persist")
    db_table=sc.cassandraTable(keyspace,"vname").select("hashvalue","youtubelink","videoname",'framenumber','frametime').persist(StorageLevel.MEMORY_ONLY)
    db_table.repartition(36)
    print("about to take")
    tempTake1=db_table.take(1);
    print("take 1 of db_table: ", tempTake1)
    zkQuorum, myTopic = sys.argv[1:]
    # Specify all the nodes you are running Kafka on
    kafkaBrokers = {"metadata.broker.list": "52.33.155.170:9092,54.69.1.84:9092,52.41.224.1:9092"}
    streamFromKafka = KafkaUtils.createDirectStream(ssc, [myTopic], kafkaBrokers)
    print("stream fm kafka:", streamFromKafka)
    streamFromKafka.foreachRDD(doEverything)
    producer.send('searchReturns',"Hello, producer is working. Time is: " + str(time.time()))
    print("starting")
    ssc.start()
    ssc.awaitTermination() 
