CREATE KEYSPACE IF NOT EXISTS woody_clickstream WITH replication = {'class':'SimpleStrategy','replication_factor':3};

USE woody_clickstream;

/** events */

CREATE TABLE IF NOT EXISTS click_event (
  session_id varchar,
  ts timestamp,
  item_id varchar,
  category varchar,
  PRIMARY KEY (session_id, ts)
);

CREATE TABLE IF NOT EXISTS buy_event (
  session_id varchar,
  ts timestamp,
  item_id varchar,
  price float,
  quantity int,
  PRIMARY KEY (session_id, ts)
);

/** aggregations */

CREATE TABLE IF NOT EXISTS session_quan (
  session_id varchar,
  quan_bought int,
  PRIMARY KEY (session_id)
);

CREATE TABLE IF NOT EXISTS item_quan (
  item_id varchar,
  quan_bought int,
  PRIMARY KEY (item_id)
);

CREATE TABLE IF NOT EXISTS item_click (
  item_id varchar,
  click_count int,
  PRIMARY KEY (item_id)
);

CREATE TABLE IF NOT EXISTS session_click (
  session_id varchar,
  click_count int,
  PRIMARY KEY (session_id)
);

CREATE TABLE IF NOT EXISTS purchase_delta (
  session_id varchar,
  item_id varchar,
  ts_buy timestamp,
  ts_click timestamp,
  ts_delta timestamp,
  price float,
  PRIMARY KEY (session_id, item_id)
);
