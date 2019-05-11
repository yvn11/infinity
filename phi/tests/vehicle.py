#!/usr/bin/python3

import pandas as pd
import numpy as np
import ujson

class VehicleStat(object):
    
    def __init__(self):
        super(VehicleStat, self).__init__()
        self.load()

    def load(self):
        csv_path = "/data/vehicle/v0227-utf8.csv"
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
                .replace('无数据', np.nan)\
                .replace('无', np.nan)\
                .replace('#', np.nan)
        self.df_vehicle['新能源汽车种类'].replace('xnyzl', np.nan, inplace=True)
        self.df_vehicle['事故车损伤部位情况'].replace('sgcssbwqk', np.nan, inplace=True)
        self.df_vehicle['手机号码'].replace('sjhm', np.nan, inplace=True)
        self.df_vehicle['车辆品牌2'].replace('clpp2', np.nan, inplace=True)
        self.df_vehicle['车辆品牌'].replace('clpp', np.nan, inplace=True)
        self.df_vehicle['国产/进口'].replace('gcjk', np.nan, inplace=True)

        # 59 columns left
        _ = [self.df_vehicle.drop(x, 1, inplace=True) \
                for x in self.df_vehicle.columns \
                if self.df_vehicle[x].isnull().all()]

    def metric_brand_percent(self):
        # Count for each brand
        # TODO: Unify same brand, ex: AUDI and AUDI牌 
        self.df_vehicle['车辆品牌2'] = self.df_vehicle['车辆品牌2'][\
          ~self.df_vehicle['车辆品牌2'].isnull()].apply(\
            lambda x: x.upper().strip(' .').replace('牌',''))
        grp_brand = self.df_vehicle.groupby('车辆品牌2')
        res = {k: len(grp_brand.groups[k]) for k in grp_brand.groups.keys()}
        self.metrics['metric_brand'] = {'x': res.keys(), 'y': res.values()}

    def metric_newenergy_percent(self):
        # Count for each new energy type
        # self.df_vehicle.是否新能源汽车, yes(1)/no(2)
        # A:纯电动 B: 燃料电池 C: 插电式混合动力
        grp_ne_total = self.df_vehicle.groupby('是否新能源汽车')
        res = {k: len(grp_ne_total.get_group(k)) for k in grp_ne_total.groups.keys()}
        self.metrics['metric_newenergy'] = {'x': res.keys(), 'y': res.values()}
        grp_ne = self.df_vehicle[self.df_vehicle['是否新能源汽车']=='1'].groupby('新能源汽车种类')
        res = {k: len(grp_ne.groups[k]) for k in grp_ne.groups.keys()}
        self.metrics['metric_newenergy_kind'] = {'x': res.keys(), 'y': res.values()}

    def metric_venture_percent(self):
        # self.df_vehicle['国产/进口'], 国产(A)/进口(B)
        grp_venture = self.df_vehicle.groupby('国产/进口')
        res = {k: len(grp_venture.groups[k]) for k in grp_venture.groups.keys()}
        self.metrics['metric_venture'] = {'x': res.keys(), 'y': res.values()}

    def metric_color_percent(self):
        grp_color = self.df_vehicle.groupby('车身颜色')
        res = {k: len(grp_color.groups[k]) for k in grp_color.groups.keys()}
        self.metrics['metric_color'] = {'x': res.keys(), 'y': res.values()}

    def metric_production_country_percent(self):
        self.df_vehicle['制造国'] = self.df_vehicle['制造国'][\
                ~self.df_vehicle['制造国'].isnull()].apply(\
                    lambda x: self.df_3166['country'][self.df_3166.code==x].values[0])
        grp_production_country = self.df_vehicle.groupby('制造国')
        res = {k: len(grp_production_country.groups[k]) for k in grp_production_country.groups.keys()}
        self.metrics['metric_production_country'] = {'x': res.keys(), 'y': res.values()}

    def metric_capacity(self):
        self.df_vehicle['排量'] = self.df_vehicle['排量'][~self.df_vehicle['排量'].isnull()].astype(int)
        cap_sorted = self.df_vehicle.sort_values(ascending=False, by='排量')
        cap_sorted = cap_sorted[~cap_sorted['排量'].isnull()]['排量']
        self.metrics['metric_cap_sorted'] = {'y': cap_sorted.tolist()}

        med = self.df_vehicle['排量'].median()
        gt = self.df_vehicle['排量'][self.df_vehicle['排量']>med].count().tolist()
        lt = self.df_vehicle['排量'][self.df_vehicle['排量']<med].count().tolist()
        eq = self.df_vehicle['排量'][self.df_vehicle['排量']==med].count().tolist()
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
