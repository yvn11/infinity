/**
*/

drop database if exists truth;
create database truth;

use truth;
drop table if exists 'message';
create table 'message' (
  'id' char primary key not null,
  'content' char,
  'created_at' DataTime,
);
