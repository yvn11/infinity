CREATE KEYSPACE IF NOT EXISTS woody WITH replication = {'class':'SimpleStrategy','replication_factor':3};

USE woody;

CREATE TABLE IF NOT EXISTS profile (
  id uuid PRIMARY KEY,
  age int,
  gender int,
  citizenship varchar, /* citizenship code from table `citizenship` */
  face_features list<uuid>, /* uuid in table `feature` */
  source varchar,
  status varchar, /* data status code from table `data_status` */
  created_at timestamp,
  updated_at timestamp
);

CREATE TABLE IF NOT EXISTS feature (
  id uuid PRIMARY KEY,
  feat blob,
  source varchar,
  status varchar, /* data status code from table `data_status` */
  created_at timestamp,
  updated_at timestamp
);

/** initialize by `citizenship.cql` */
CREATE TABLE IF NOT EXISTS citizenship (
  code varchar PRIMARY KEY,
  country varchar,
  source varchar,
  created_at timestamp,
  updated_at timestamp
);

/** initialize by `data_status.cql` */
CREATE TABLE IF NOT EXISTS data_status (
  code varchar PRIMARY KEY,
  short_desc varchar,
  source varchar,
  created_at timestamp,
  updated_at timestamp
);
