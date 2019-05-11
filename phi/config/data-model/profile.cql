CREATE KEYSPACE IF NOT EXISTS phi_userprofile WITH replication = {'class':'SimpleStrategy','replication_factor':3};

USE phi_userprofile;

/** cities reference */
CREATE TABLE IF NOT EXISTS city (
  name varchar,
  ctype varchar, /** city type */
  country_code varchar,
  country_name varchar,
  lat double,
  lon double,
  created_at timestamp,
  updated_at timestamp,
  PRIMARY KEY (country_code, country_name, name, updated_at)
) WITH CLUSTERING ORDER BY (country_name ASC, name ASC, updated_at DESC);

/** pois reference */
CREATE TABLE IF NOT EXISTS poi (
  venue_id varchar,
  venue_cate varchar, /** venue category */
  country_code varchar,
  lat double,
  lon double,
  created_at timestamp,
  updated_at timestamp,
  PRIMARY KEY (venue_id, country_code, venue_cate, updated_at)
) WITH CLUSTERING ORDER BY (country_code ASC, venue_cate ASC, updated_at DESC);

/** events */

CREATE TABLE IF NOT EXISTS checkin (
  user_id varchar,
  venue_id varchar,
  utc_time timestamp,
  tz_offset int,
  PRIMARY KEY (user_id, utc_time, venue_id)
) WITH CLUSTERING ORDER BY (utc_time DESC, venue_id ASC);

/** aggregation */
CREATE TABLE IF NOT EXISTS city_checkin_count (
  city_name varchar,
  checkin_count int,
  lat double,
  lon double,
  created_at timestamp,
  updated_at timestamp,
  PRIMARY KEY (city_name, checkin_count, updated_at)
) WITH CLUSTERING ORDER BY (checkin_count DESC, updated_at DESC);

CREATE TABLE IF NOT EXISTS venue_checkin_count (
  venue_id varchar,
  checkin_count int,
  lat double,
  lon double,
  created_at timestamp,
  updated_at timestamp,
  PRIMARY KEY (venue_id, checkin_count, updated_at)
) WITH CLUSTERING ORDER BY (checkin_count DESC, updated_at DESC);

CREATE TABLE IF NOT EXISTS user_checkin_count (
  user_id varchar,
  checkin_count int,
  lat double,
  lon double,
  created_at timestamp,
  updated_at timestamp,
  PRIMARY KEY (user_id, checkin_count, updated_at)
) WITH CLUSTERING ORDER BY (checkin_count DESC, updated_at DESC);
