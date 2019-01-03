CREATE KEYSPACE IF NOT EXISTS aggregate WITH replication = {'class':'SimpleStrategy','replication_factor':3};

USE aggregate;
CREATE TABLE IF NOT EXISTS profile (
  id uuid PRIMARY KEY,
  age int,
  gender int,
  citizenship text,
  face_feature list<uuid>,
  created_at timestamp,
  updated_at timestamp,
);

CREATE TABLE IF NOT EXISTS feature (
  id uuid PRIMARY KEY,
  feat list<blob>,
  created_at timestamp,
  updated_at timestamp
);
