def stream(ssc, pwords, nwords, duration):
    kstream = KafkaUtils.createDirectStream(
        ssc, topics = ['twitterstream'], kafkaParams = {"metadata.broker.list": 'localhost:9092'})
    tweets = kstream.map(lambda x: x[1].encode("ascii","ignore"))

    # Each element of tweets will be the text of a tweet.
    # You need to find the count of all the positive and negative words in these tweets.
    # Keep track of a running total counts and print this at every time step (use the pprint function).

    #Get the individual elements in the tweet    
    words = tweets.flatMap(lambda line: line.split(" "))
    
    #Filter the word to contain only positive and negative
    words = words.filter(lambda word: (word in pwords) or (word in nwords))

    #Map each filtered word to psoitive and negative
    wordPairs = words.map(lambda word: ('positive', 1) if (word in pwords) else ('negative', 1))

    #Sum up all positive and negative words in a tweet
    wordCounts = wordPairs.reduceByKey(lambda x, y: x + y)

    #Get an ensemble of total positive and negative counts and print them
    cumulativeCount = wordPairs.updateStateByKey(updateFunction)  
    cumulativeCount.pprint() 
    
    # Let the counts variable hold the word counts for all time steps
    # You will need to use the foreachRDD function.
    # For our implementation, counts looked like:
    #   [[("positive", 100), ("negative", 50)], [("positive", 80), ("negative", 60)], ...]
    counts = []
    wordCounts.foreachRDD(lambda t,rdd: counts.append(rdd.collect()))
    
    ssc.start()                         # Start the computation
    ssc.awaitTerminationOrTimeout(duration)
    ssc.stop(stopGraceFully=True)

    return counts 
