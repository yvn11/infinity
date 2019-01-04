USE woody;
INSERT INTO data_status (code,short_desc,created_at,updated_at) values ('ONLINE','Record is currently in use',toTimestamp(now()),toTimestamp(now()));
INSERT INTO data_status (code,short_desc,created_at,updated_at) values ('DELETE','Record is marked deleted',toTimestamp(now()),toTimestamp(now()));
INSERT INTO data_status (code,short_desc,created_at,updated_at) values ('OFFLINE','Record is marked offline for maintenance purpose',toTimestamp(now()),toTimestamp(now()));
