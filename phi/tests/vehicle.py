#!/usr/bin/python3

import pandas as pd
import numpy as np
import ujson

class VehicleStat(object):
    
    def __init__(self):
        super(VehicleStat, self).__init__()
        self.load()

    def load(self):
        csv_path = "/data/vehicle/vdata-utf8.csv"
        # made country mapping ISO_3166-1
        self.df_3166 = pd.read_csv('/data/vehicle/iso_3166-1.csv', delimiter=',')
        self.df_3166.code = self.df_3166.code.astype(str)
        self.df_vehicle = pd.read_csv(csv_path, delimiter='\\t')
        self.metrics = {}

    def dump_metrics(self):
        output_metrics = '/data/vehicle/metrics.json'
        with open(output_metrics, 'w') as fd:
            ujson.dump(self.metrics, fd, ensure_ascii=False)

    def cleanup_stage1(self):
        self.df_vehicle = self.df_vehicle.drop(
                    self.df_vehicle[self.df_vehicle.id=='id'].index)\
                .replace('NULL', np.nan)\
                .replace('#', np.nan)
        self.df_vehicle['NE'].replace('xnyzl', np.nan, inplace=True)
        self.df_vehicle['Damage'].replace('sgcssbwqk', np.nan, inplace=True)
        self.df_vehicle['Cell'].replace('sjhm', np.nan, inplace=True)
        self.df_vehicle['Brand'].replace('clpp', np.nan, inplace=True)
        self.df_vehicle['Venture'].replace('gcjk', np.nan, inplace=True)

        # 59 columns left
        _ = [self.df_vehicle.drop(x, 1, inplace=True) \
                for x in self.df_vehicle.columns \
                if self.df_vehicle[x].isnull().all()]

    def metric_brand_percent(self):
        # Count for each brand
        self.df_vehicle['Brand'] = self.df_vehicle['Brand'][\
          ~self.df_vehicle['Brand'].isnull()].apply(\
            lambda x: x.upper().strip(' .').replace('Brand',''))
        grp_brand = self.df_vehicle.groupby('Brand')
        res = {k: len(grp_brand.groups[k]) for k in grp_brand.groups.keys()}
        self.metrics['metric_brand'] = {'x': res.keys(), 'y': res.values()}

    def metric_newenergy_percent(self):
        grp_ne_total = self.df_vehicle.groupby('NELabel')
        res = {k: len(grp_ne_total.get_group(k)) for k in grp_ne_total.groups.keys()}
        self.metrics['metric_newenergy'] = {'x': res.keys(), 'y': res.values()}
        grp_ne = self.df_vehicle[self.df_vehicle['NELabel']=='1'].groupby('NE')
        res = {k: len(grp_ne.groups[k]) for k in grp_ne.groups.keys()}
        self.metrics['metric_newenergy_kind'] = {'x': res.keys(), 'y': res.values()}

    def metric_venture_percent(self):
        grp_venture = self.df_vehicle.groupby('Venture')
        res = {k: len(grp_venture.groups[k]) for k in grp_venture.groups.keys()}
        self.metrics['metric_venture'] = {'x': res.keys(), 'y': res.values()}

    def metric_color_percent(self):
        grp_color = self.df_vehicle.groupby('Color')
        res = {k: len(grp_color.groups[k]) for k in grp_color.groups.keys()}
        self.metrics['metric_color'] = {'x': res.keys(), 'y': res.values()}

    def metric_production_country_percent(self):
        self.df_vehicle['ProdCountry'] = self.df_vehicle['ProdCountry'][\
                ~self.df_vehicle['ProdCountry'].isnull()].apply(\
                    lambda x: self.df_3166['country'][self.df_3166.code==x].values[0])
        grp_production_country = self.df_vehicle.groupby('ProdCountry')
        res = {k: len(grp_production_country.groups[k]) for k in grp_production_country.groups.keys()}
        self.metrics['metric_production_country'] = {'x': res.keys(), 'y': res.values()}

    def metric_capacity(self):
        self.df_vehicle['Capacity'] = self.df_vehicle['Capacity'][~self.df_vehicle['Capacity'].isnull()].astype(int)
        cap_sorted = self.df_vehicle.sort_values(ascending=False, by='Capacity')
        cap_sorted = cap_sorted[~cap_sorted['Capacity'].isnull()]['Capacity']
        self.metrics['metric_cap_sorted'] = {'y': cap_sorted.tolist()}

        med = self.df_vehicle['Capacity'].median()
        gt = self.df_vehicle['Capacity'][self.df_vehicle['Capacity']>med].count().tolist()
        lt = self.df_vehicle['Capacity'][self.df_vehicle['Capacity']<med].count().tolist()
        eq = self.df_vehicle['Capacity'][self.df_vehicle['Capacity']==med].count().tolist()
        self.metrics['metric_cap_dist'] = {'median': med, '>': gt, '<': lt, '=': eq}

if __name__ == '__main__':
    stat = VehicleStat()
    stat.cleanup_stage1() 
    stat.metric_brand_percent()
    stat.metric_newenergy_percent()
    stat.metric_venture_percent()
    stat.metric_color_percent()
    stat.metric_production_country_percent()
    stat.metric_capacity()
    stat.dump_metrics()
