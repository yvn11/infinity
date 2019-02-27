#!/usr/bin/python3
from matplotlib import pyplot as plt
import pandas as pd

df_nyc = pd.read_csv('/data/foursquare/dataset_tsmc2014/dataset_TSMC2014_NYC.txt', delimiter='\\t',names=
        ['user_id','venue_id','venue_category_id','venue_category', 'lat', 'lon', 'tz_offset', 'utc_time'])
df_tky=pd.read_csv('/data/foursquare/dataset_tsmc2014/dataset_TSMC2014_TKY.txt', delimiter='\\t',names=['user_id','venue_id','venue_category_id','venue_category', 'lat', 'lon', 'tz_offset', 'utc_time'])
df_cities=pd.read_csv('/data/foursquare/dataset_tist2015/dataset_TIST2015_Cities.txt',delimiter='\\t',names=['name','lat','lon','country_code','country_name','type'])
df_checkin = pd.read_csv('/data/foursquare/dataset_tist2015/dataset_TIST2015_Checkins.txt', delimiter='\\t', names=['user_id','venue_id','utc_time','tz_offset'],parse_dates=True, nrows=30000)
df_pois=pd.read_csv('/data/foursquare/dataset_tist2015/dataset_TIST2015_POIs.txt',delimiter='\\t',names=['venue_id','lat','lon','venue_cate','country_code'],nrows=10000)

print(df_nyc[df_nyc.user_id==1044])
