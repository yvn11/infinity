CREATE KEYSPACE IF NOT EXISTS woody WITH replication = {'class':'SimpleStrategy','replication_factor':3};

USE woody;

CREATE TABLE IF NOT EXISTS click_event (
  session_id varchar,
  ts varchar,
  item_id varchar,
  category varchar,
  PRIMARY KEY (session_id, ts)
);

CREATE TABLE IF NOT EXISTS buy_event (
  session_id varchar,
  ts varchar,
  item_id varchar,
  price varchar,
  PRIMARY KEY (session_id, ts)
);
