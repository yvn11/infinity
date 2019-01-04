CREATE KEYSPACE IF NOT EXISTS aggregate WITH replication = {'class':'SimpleStrategy','replication_factor':3};

USE aggregate;

CREATE TABLE IF NOT EXISTS profile (
  id uuid PRIMARY KEY,
  age int,
  gender int,
  citizenship varchar, /* citizenship code from table `citizenship` */
  face_features list<uuid>, /* uuid in table `feature` */
  source varchar,
  created_at timestamp,
  updated_at timestamp
);

CREATE TABLE IF NOT EXISTS feature (
  id uuid PRIMARY KEY,
  feat blob,
  source varchar,
  created_at timestamp,
  updated_at timestamp
);

CREATE TABLE IF NOT EXISTS citizenship (
  code varchar PRIMARY KEY,
  country varchar,
  source varchar,
  created_at timestamp,
  updated_at timestamp
);
