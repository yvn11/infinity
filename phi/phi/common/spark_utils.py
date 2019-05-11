#!/usr/bin/python3
from pyspark.sql import Row, SparkSession, functions
import sys

def SparkSessionInstance(sparkConf):
    if ('sparkSessionSingletonInstance' not in globals()):
        globals()['sparkSessionSingletonInstance'] = SparkSession\
            .builder\
            .config(conf=sparkConf)\
            .getOrCreate()
    return globals()['sparkSessionSingletonInstance']

def create_allocation_file(sched_file):
    with open(sched_file, 'w') as fd:
        fd.write("""
<allocations> 
  <pool name="production"> 
    <schedulingMode>FAIR</schedulingMode> 
    <weight>2</weight> 
    <minShare>1</minShare> 
  </pool> 
  <pool name="dev"> 
    <schedulingMode>FAIR</schedulingMode> 
    <weight>2</weight> 
    <minShare>1</minShare> 
  </pool> 
  <pool name="clickstream"> 
    <schedulingMode>FAIR</schedulingMode> 
    <weight>3</weight> 
    <minShare>1</minShare> 
  </pool>
  <pool name="userprofile"> 
    <schedulingMode>FAIR</schedulingMode> 
    <weight>3</weight> 
    <minShare>1</minShare> 
  </pool>
</allocations>""")

def now_timestamp():
    from datetime import datetime
    if sys.version_info.major == 2:
        import time
        return int(time.mktime(datetime.utcnow().timetuple()))
    return int(datetime.now().timestamp())
