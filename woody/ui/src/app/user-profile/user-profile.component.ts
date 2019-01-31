import { Component, OnInit } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import { environment } from '../../environments/environment';
// import * as Highcharts from 'highcharts/highmaps';
import * as Highcharts from 'highcharts';
import MapModule from 'highcharts/modules/map';

MapModule(Highcharts);
   
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
  geo_world: Array<object>;

  constructor(private http_cli: HttpClient) {
    console.log(this.title);
    this.refreshInterval = 2000;
    this.autoRefresh = true;
    this.geojson_world_url = 'https://code.highcharts.com/mapdata/custom/world.geo.json';
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
    const data = [{
        id: 'London',
        lat: 51.507222,
        lon: -0.1275
    }, {
        id: 'Birmingham',
        lat: 52.483056,
        lon: -1.893611
    }, {
        id: 'Leeds',
        lat: 53.799722,
        lon: -1.549167
    }, {
        id: 'Glasgow',
        lat: 55.858,
        lon: -4.259
    }, {
        id: 'Sheffield',
        lat: 53.383611,
        lon: -1.466944
    }, {
        id: 'Liverpool',
        lat: 53.4,
        lon: -3
    }, {
        id: 'Bristol',
        lat: 51.45,
        lon: -2.583333
    }, {
        id: 'Belfast',
        lat: 54.597,
        lon: -5.93
    }, {
        id: 'Lerwick',
        lat: 60.155,
        lon: -1.145,
    }]

    this.refresh_event_geo(data);
  }

  private fetchGeoWorld() {
    this.http_cli.get(this.geojson_world_url)
      .subscribe(rsp => { this.onGeoWorld(rsp); });
  }

  onGeoWorld(rsp) {
    if (rsp === null) { return; }
    this.geo_world = Highcharts.geojson(rsp);
    console.log(this.geo_world);
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
    console.log(Highcharts.getOptions());
    console.log(Highcharts.maps['countries/gb/gb-all']);
    Highcharts.mapChart('container_geo', {
      chart: {
        map: 'countries/gb/gb-all',
      },
      title: {
        text: 'Event Geo'
      },
      mapNavigation: {
        enabled: true
      },
      series: [{
          type: 'map',
          // mapData: Highcharts.maps['countries/gb/gb-all'],
          data: this.geo_world,
          name: 'Basemap',
          borderColor: '#707070',
          nullColor: 'rgba(200, 200, 200, 0.3)',
          showInLegend: false
          }, /** {
          type: 'mapline',
          name: 'Separators',
          data: Highcharts.geojson(Highcharts.maps['countries/gb/gb-all'], 'mapline'),
          color: '#707070',
          showInLegend: false,
          enableMouseTracking: false
          },*/ {
          type: 'mappoint',
          name: 'Events',
          color: Highcharts.getOptions().colors[1],
          data: data
        }]
    });
  }
}
