CREATE KEYSPACE IF NOT EXISTS woody_clickstream WITH replication = {'class':'SimpleStrategy','replication_factor':3};

USE woody_clickstream;

/** events */

CREATE TABLE IF NOT EXISTS click_event (
  session_id varchar,
  ts timestamp,
  item_id varchar,
  category varchar,
  created_at timestamp,
  updated_at timestamp,
  PRIMARY KEY ((item_id, session_id), ts)
) WITH CLUSTERING ORDER BY (ts DESC);

CREATE TABLE IF NOT EXISTS buy_event (
  session_id varchar,
  ts timestamp,
  item_id varchar,
  price float,
  quantity int,
  created_at timestamp,
  updated_at timestamp,
  PRIMARY KEY ((item_id, session_id), ts)
) WITH CLUSTERING ORDER BY (ts DESC);

/** aggregations */

CREATE TABLE IF NOT EXISTS session_quan (
  session_id varchar,
  quan_bought int,
  created_at timestamp,
  updated_at timestamp,
  PRIMARY KEY (session_id, updated_at,created_at)
) WITH CLUSTERING ORDER BY (updated_at DESC, created_at DESC);

CREATE TABLE IF NOT EXISTS item_quan (
  item_id varchar,
  quan_bought int,
  created_at timestamp,
  updated_at timestamp,
  PRIMARY KEY (session_id, updated_at,created_at)
) WITH CLUSTERING ORDER BY (updated_at DESC, created_at DESC);

CREATE TABLE IF NOT EXISTS item_click (
  item_id varchar,
  click_count int,
  created_at timestamp,
  updated_at timestamp,
  PRIMARY KEY (item_id, updated_at,created_at)
) WITH CLUSTERING ORDER BY (updated_at DESC, created_at DESC);

CREATE TABLE IF NOT EXISTS session_click (
  session_id varchar,
  click_count int,
  created_at timestamp,
  updated_at timestamp,
  PRIMARY KEY (session_id, updated_at,created_at)
) WITH CLUSTERING ORDER BY (updated_at DESC, created_at DESC);

CREATE TABLE IF NOT EXISTS purchase_delta (
  session_id varchar,
  item_id varchar,
  ts_buy timestamp,
  ts_click timestamp,
  ts_delta timestamp,
  price float,
  created_at timestamp,
  updated_at timestamp,
  PRIMARY KEY ((session_id, item_id), updated_at, created_at, ts_delta, price)
) WITH CLUSTERING ORDER BY (
  updated_at DESC, created_at DESC, ts_delta ASC, price ASC);

CREATE TABLE IF NOT EXISTS category_click (
  category varchar,
  click_count int,
  created_at timestamp,
  updated_at timestamp,
  PRIMARY KEY (category, updated_at)
) WITH CLUSTERING ORDER BY (updated_at DESC);

CREATE TABLE IF NOT EXISTS total_event (
  event varchar,
  ts timestamp,
  count int,
  PRIMARY KEY (event, ts)
) WITH CLUSTERING ORDER BY (ts DESC);
