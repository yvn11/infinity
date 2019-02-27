#!/usr/bin/python3
from pyspark.sql import Row, SparkSession, functions

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
