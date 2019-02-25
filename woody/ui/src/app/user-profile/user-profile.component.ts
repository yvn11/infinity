import { Component, OnInit } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import { environment } from '../../environments/environment';
import * as Highcharts from 'highcharts/highmaps';
import * as proj4 from 'proj4';
// import * as Highcharts from 'highcharts';
// import MapModule from 'highcharts/modules/map';

// MapModule(Highcharts);
   
@Component({
  selector: 'app-user-profile',
  templateUrl: './user-profile.component.html',
  styleUrls: ['./user-profile.component.css']
})
export class UserProfileComponent implements OnInit {

  title = 'The BoringUI for Woody';
  autoRefresh: boolean;
  refreshInterval: number; // ms
  geojson_world_url: string;
  // geo_world: Array<object>; // Highcharts.MapDataObject>;
  raw_geo_world: object;

  constructor(private http_cli: HttpClient) {
    console.log(this.title);
    this.refreshInterval = 2000;
    this.autoRefresh = true;
    // this.geojson_world_url = 'https://code.highcharts.com/mapdata/custom/world.geo.json';
    // this.geojson_world_url = 'https://code.highcharts.com/mapdata/custom/world-palestine-highres.geo.json';
    // this.geojson_world_url = 'https://code.highcharts.com/mapdata/countries/gb/gb-all.geo.json';
    this.geojson_world_url = 'https://code.highcharts.com/mapdata/countries/cn/cn-all.geo.json';
  }

  ngOnInit() {
    Highcharts.setOptions({
      plotOptions: {
        series: {
          animation: false
        }
      }
    });

    this.fetchGeoWorld();
    // this.fetchGeo();
  }

  private fetchGeoWorld() {
    this.http_cli.get(this.geojson_world_url)
      .subscribe(rsp => { this.onGeoWorld(rsp); });
  }

  onGeoWorld(rsp) {
    if (rsp === null) { return; }
    this.raw_geo_world = rsp;

    const data = [{
        name: 'London',
        lat: 51.507222,
        lon: -0.1275
    }, {
        name: 'Birmingham',
        lat: 52.483056,
        lon: -1.893611
    }, {
        name: 'Leeds',
        lat: 53.799722,
        lon: -1.549167
    }, {
        name: 'Glasgow',
        lat: 55.858,
        lon: -4.259
    }, {
        name: 'Sheffield',
        lat: 53.383611,
        lon: -1.466944
    }, {
        name: 'Liverpool',
        lat: 53.4,
        lon: -3
    }, {
        name: 'Bristol',
        lat: 51.45,
        lon: -2.583333
    }, {
        name: 'Belfast',
        lat: 54.597,
        lon: -5.93
    }, {
        name: 'Lerwick',
        lat: 60.155,
        lon: -1.145
    }]

    this.refresh_event_geo(data);
  }

  private convXYfromLatLon(data) {
    
  }

  private fetchGeo() {
    /**
    const url = environment.woody_apiserver + '/v1/metrics/item_click'
      + '?' + 'gt=' + this.itemClickConf.gt + '&limit=' + this.itemClickConf.limit;
    this.http_cli.get(url)
      .subscribe(rsp => { this.onItemClick(rsp); });
    */
  }

  onGeo(rsp) {
    if (this.autoRefresh) {
      setTimeout(() => this.fetchGeo(), this.refreshInterval);
    }

    const item_ids = [];
    const counts = [];

    if (rsp != null && rsp['response'] != null) {
      for (let i = 0; i < rsp['response'].length; i++) {
        item_ids.push(rsp['response'][i]['item_id']);
        counts.push(rsp['response'][i]['click_count']);
      }
    }

    // this.refresh_event_geo(data);
  }

  refresh_event_geo(data) {
    const jdata = {
  type: "FeatureCollection",
  features: [
    {
      type: "Feature",
      properties: {},
      geometry: {
        type: "Point",
        coordinates: [
          -268.5417366027832,
          44.86243957826663
        ]
      }
    },
    {
      type: "Feature",
      properties: {"name":"Xizang"},
      geometry: {
        type: "Point",
        coordinates: [
          84.5947265625,
          35.639441068973944
        ]
      }
    }
  ]
  };
    console.log(Highcharts.geojson(jdata, 'mappoint'));
    console.log(this.raw_geo_world);
    // console.log(Highcharts.geojson(this.raw_geo_world, 'mappoint'));
    Highcharts.mapChart('container_geo', {
      /** chart: {
        map: 'countries/gb/gb-all'
      }, */
      title: {
        text: 'Event Geo'
      },
      mapNavigation: {
        enabled: true
      },
      series: [ {
          type: 'map',
          // mapData: Highcharts.geojson(this.raw_geo_world, 'map') as Highcharts.MapDataObject[],
          // mapData: Highcharts.maps['countries/gb/gb-all'],
          data: Highcharts.geojson(this.raw_geo_world, 'map'),
          name: 'Base',
          borderColor: '#707070',
          nullColor: 'rgba(200, 200, 200, 0.3)',
          tooltip: {
            headerFormat: '',
            // pointFormat: '<b>{point.name}</b><br>Lat: {point.properties.latitude}, Lon: {point.properties.longitude}'
            pointFormat: '<b>{point.name}</b><br>Lat: {point.properties.latitude}, Lon: {point.properties.longitude}'
          }, 
          showInLegend: false
          }, {
          type: 'mapline',
          name: 'Separators',
          data: Highcharts.geojson(this.raw_geo_world, 'mapline'), // as Highcharts.MapDataObject[],
          nullColor: '#707070',
          showInLegend: false,
          enableMouseTracking: false
          }, {
          type: 'mappoint',
          name: 'Events',
          color: 'darkblue', // Highcharts.getOptions().colors[2],
          // data: data,//Highcharts.geojson(jdata, 'mappoint'),
          data: data,
          tooltip: {
            headerFormat: '',
            pointFormat: '<b>{point.name}</b><br>Lat: {point.x}, Lon: {point.y}'
          }
        }]
    });
  }
}
