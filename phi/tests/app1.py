#https://www.programcreek.com/python/example/98361/pyspark.streaming.kafka.KafkaUtils.createDirectStream

def main():
    parser = OptionParser()
    parser.add_option('', '--enriched_data_path', action='store', dest='enriched_data_path', help='path to write enriched data')
    parser.add_option('', '--model_path', action='store', dest='model_path', help='path for model data')
    parser.add_option('', '--kafka_zookeeper_hosts', action='store', dest='kafka_zookeeper_hosts', help='list of Zookeeper hosts (host:port)')
    parser.add_option('', '--kafka_broker_list', action='store', dest='kafka_broker_list', help='list of Kafka brokers (host:port)')
    parser.add_option('', '--kafka_message_topic', action='store', dest='kafka_message_topic', help='topic to consume input messages from')
    parser.add_option('', '--kafka_alert_topic', action='store', dest='kafka_alert_topic', help='topic to produce alert messages to')
    parser.add_option('', '--kafka_enriched_data_topic', action='store', dest='kafka_enriched_data_topic', help='topic to produce enriched data to')
    parser.add_option('', '--streaming_batch_duration_sec', type='float', default=15.0,
        action='store', dest='streaming_batch_duration_sec', help='Streaming batch duration in seconds')
    parser.add_option('', '--max_batches', type='int', default=0,
        action='store', dest='max_batches', help='Number of batches to process (0 means forever)')
    options, args = parser.parse_args()

    sc = SparkContext()
    ssc = StreamingContext(sc, options.streaming_batch_duration_sec)
    sqlContext = getSqlContextInstance(sc)

    # Load saved model.
    model = None
    if options.model_path:
        model = RandomForestModel.load(sc, options.model_path)
    else:
        print('No model loaded.')

    # Create Kafka stream to receive new messages.
    kvs = KafkaUtils.createDirectStream(ssc, [options.kafka_message_topic], {
        'metadata.broker.list': options.kafka_broker_list,
        'group.id': 'spark_streaming_processor.py'})

    # Take only the 2nd element of the tuple.
    messages = kvs.map(lambda x: x[1])

    # Convert RDD of JSON strings to RDD of Rows.
    rows = messages.map(json_to_row)

    # Process messages.
    rows.foreachRDD(lambda time, rdd: 
        process_messages(time, rdd,
            ssc=ssc,
            model=model,
            enriched_data_path=options.enriched_data_path,
            zookeeper_hosts=options.kafka_zookeeper_hosts,
            kafka_alert_topic=options.kafka_alert_topic,
            kafka_enriched_data_topic=options.kafka_enriched_data_topic,
            max_batches=options.max_batches))

    ssc.start()
    ssc.awaitTermination() 
