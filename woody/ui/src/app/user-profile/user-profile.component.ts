import { Component, OnInit } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import { environment } from '../../environments/environment';
import * as Plotly from 'plotly.js';

// HTML <script type='text/javascript' src="https://cdnjs.cloudflare.com/ajax/libs/proj4js/2.3.6/proj4.js"></script>
// import * as proj4 from 'proj4.js';
// export default proj4;
// (window as any).proj4 = proj4;
import * as Highcharts from 'highcharts/highmaps';

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

    // this.refresh_event_geo(data);
    this.geo_layout();
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

  geo_layout() {
    const layout = {
      title: 'global event',
      titlefont: {
        size: 20
      },
      font: {
        family: 'Droid Serif, serif',
        size: 10,
        color: '#000999'
      },
      geo: {
        scope: 'world',
        projection: { type: 'mercator' },
        showcoastlines: false,
        showframe: false,
        showland: true,
        landcolor: 'rgb(220, 220, 220)',
        // showrivers: true,
        showlakes: true,
        lakecolor: 'lightblue',
        showcountries: true,
        // countrycolor: 'rgb(217, 244, 244)',
        countrywidth: 0.5,
        subunitcolor: 'rgb(217, 217, 217)',
        lataxis: { range: [-10] },
        // lonaxis: { range: [-180] },
        resolution: 50
      },
      reversescale: true,
      dragmode: false,
      autosize: true,
      width: 1000,
      height: 700
    };

    const data: Plotly.ScatterData[] = [{
      type: 'scattergeo',
      mode: 'text+markers',
      text: ['Coffee Shop', 'Miscellaneous Shop', 'Subway', 'Subway', 'Subway', 'Cosmetics Shop', 'Ramen /  Noodle House', 'Convenience Store', 'Food & Drink Shop', 'Housing Development'],
      lat: [40.712033033064166, 40.75313016065781, 40.71037756449118, 40.71037756449118, 40.71037756449118, 35.705101088587135, 35.715581120393146, 35.714542173995646, 35.72559198908874, 35.656083091901124],
      lon: [-74.00699299251195, -73.97621627458902, -74.00755405426025, -74.00755405426025, -74.00755405426025, 139.61959004402158, 139.8003172874451, 139.4800649934587, 139.7766325938853, 139.734045462721],
      name: 'NYC',
      marker: {
        line: {
          color: '#000000',
          width: 1
        }
      }
    }];
    
    Plotly.plot('container_geo', data, layout, {showlink: false});
  }
}
