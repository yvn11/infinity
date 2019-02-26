#!/usr/bin/python3
from matplotlib import pyplot as plt
import pandas as pd

df_nyc = pd.read_csv('/data/foursquare/dataset_tsmc2014/dataset_TSMC2014_NYC.txt', delimiter='\\t',names=
        ['user_id','venue_id','venue_category_id','venue_category', 'latitude', 'longitude', 'tz_offset', 'utc_time'])
print(df_nyc[df_nyc.user_id==1044])
