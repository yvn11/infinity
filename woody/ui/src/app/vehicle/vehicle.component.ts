import { Component, OnInit } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import { environment } from '../../environments/environment';
import * as Plotly from 'plotly.js';

@Component({
  selector: 'app-vehicle',
  templateUrl: './vehicle.component.html',
  styleUrls: ['./vehicle.component.css']
})
export class VehicleComponent implements OnInit {

  venture_map: {};
  newenergy_kind_map: {};
  newenergy_map: {};
  title = 'The BoringUI for Woody';
  constructor(private http_cli: HttpClient) {
    console.log(this.title);
    // TODO: configure
    this.venture_map = {
      'A': '国产',
      'B': '进口'
    };
    this.newenergy_kind_map = {
      'A': '纯电动',
      'B': '燃料电池',
      'C': '插电式混合动力'
    };
    this.newenergy_map = {
      '1': 'Yes',
      '2': 'No',
    };
  }

  ngOnInit() {
    this.fetchMetrics()
  }

  fetchMetrics() {
    const url = environment.woody_apiserver + '/v1/metrics/vehicle';
    this.http_cli.get(url)
      .subscribe(rsp => { this.onMetrics(rsp); });
  }

  onMetrics(rsp) {
    if (rsp == null) { return; }

    this.newenergy_percent(rsp['metric_newenergy']);
    this.brand_percent(rsp['metric_brand']);
    this.production_country_percent(rsp['metric_production_country']);
    this.newenergy_kind_percent(rsp['metric_newenergy_kind']);
    this.venture_percent(rsp['metric_venture']);
    this.color_percent(rsp['metric_color']);
    this.capacity_sorted(rsp['metric_cap_sorted']);
    this.capacity_percent(rsp['metric_cap_dist']);
  }

  brand_percent(metric) {
    if (metric == null || metric['x'] == null || metric['y'] == null) {
      return;
    }

    const layout = {
      title: 'Brand',
      titlefont: {
        size: 20
      },
      font: {
        family: 'Droid Serif, serif',
        size: 10,
        color: '#000999'
      },
      dragmode: false,
    }

    const data: Plotly.PlotData[] = [{
      type: 'pie',
      values: metric['y'],
      labels: metric['x'],
      autocolorscale: true,
      reversescale: false,
      marker: {
        line: {
          color: 'rgb(180,180,180)',
          width: 1
        }
      }
    }];

    Plotly.plot('container_brand', data, layout, {showlink: false});
  }

  production_country_percent(metric) {
    if (metric == null || metric['x'] == null || metric['y'] == null) {
      return;
    }

    const layout = {
      title: 'Production Country',
      titlefont: {
        size: 20
      },
      font: {
        family: 'Droid Serif, serif',
        size: 10,
        color: '#000999'
      },
      dragmode: false,
    }

    const data: Plotly.PlotData[] = [{
      type: 'pie',
      values: metric['y'],
      labels: metric['x'],
      autocolorscale: true,
      reversescale: false,
      marker: {
        line: {
          color: 'rgb(180,180,180)',
          width: 1
        }
      }
    }];

    Plotly.plot('container_production_country', data, layout, {showlink: false});
  }

  newenergy_percent(metric) {
    if (metric == null || metric['x'] == null || metric['y'] == null) {
      return;
    }

    this.translate(metric['x'], this.newenergy_map);

    const layout = {
      title: 'New Energy Vehicle',
      titlefont: {
        size: 20
      },
      font: {
        family: 'Droid Serif, serif',
        size: 10,
        color: '#000999'
      },
      dragmode: false,
    }

    const data: Plotly.PlotData[] = [{
      type: 'pie',
      values: metric['y'],
      labels: metric['x'],
      autocolorscale: true,
      reversescale: false,
      marker: {
        line: {
          color: 'rgb(180,180,180)',
          width: 1
        }
      }
    }];

    Plotly.plot('container_newenergy', data, layout, {showlink: false});
  }

  newenergy_kind_percent(metric) {
    if (metric == null || metric['x'] == null || metric['y'] == null) {
      return;
    }

    this.translate(metric['x'], this.newenergy_kind_map);

    const layout = {
      title: 'New Energy Kind',
      titlefont: {
        size: 20
      },
      font: {
        family: 'Droid Serif, serif',
        size: 10,
        color: '#000999'
      },
      dragmode: false,
    }

    const data: Plotly.PlotData[] = [{
      type: 'pie',
      values: metric['y'],
      labels: metric['x'],
      autocolorscale: true,
      reversescale: false,
      marker: {
        line: {
          color: 'rgb(180,180,180)',
          width: 1
        }
      }
    }];

    Plotly.plot('container_newenergy_kind', data, layout, {showlink: false});
  }

  color_percent(metric) {
    if (metric == null || metric['x'] == null || metric['y'] == null) {
      return;
    }

    const layout = {
      title: 'Color',
      titlefont: {
        size: 20
      },
      font: {
        family: 'Droid Serif, serif',
        size: 10,
        color: '#000999'
      },
      dragmode: false,
    }

    const data: Plotly.PlotData[] = [{
      type: 'pie',
      values: metric['y'],
      labels: metric['x'],
      autocolorscale: true,
      reversescale: false,
      marker: {
        line: {
          color: 'rgb(180,180,180)',
          width: 1
        }
      }
    }];

    Plotly.plot('container_color', data, layout, {showlink: false});
  }

  venture_percent(metric) {
    if (metric == null || metric['x'] == null || metric['y'] == null) {
      return;
    }
    
    this.translate(metric['x'], this.venture_map);

    const layout = {
      title: 'Venture',
      titlefont: {
        size: 20
      },
      font: {
        family: 'Droid Serif, serif',
        size: 10,
        color: '#000999'
      },
      dragmode: false,
    }

    const data: Plotly.PlotData[] = [{
      type: 'pie',
      values: metric['y'],
      labels: metric['x'],
      autosourcescale: true,
      reversescale: false,
      marker: {
        line: {
          source: 'rgb(180,180,180)',
          width: 1
        }
      }
    }];

    Plotly.plot('container_venture', data, layout, {showlink: false});
  }

  private translate(words, translate_map) {
    for (let i = 0; i < words.length; i++) {
      const key = words[i];
      if (translate_map[key] != null) {
        words[i] = translate_map[key];
      }
    }
  }

  capacity_sorted(metric) {
    if (metric == null || metric['y'] == null) {
      return;
    }

    const layout = {
      title: 'Capacity',
      titlefont: {
        size: 20
      },
      font: {
        family: 'Droid Serif, serif',
        size: 10,
        color: '#000999'
      },
      dragmode: false,
    }

    const data: Plotly.PlotData[] = [{
      type: 'bar',
      y: metric['y'],
      autosourcescale: true,
      marker: {
        line: {
          source: 'rgb(180,180,180)',
          width: 1
        }
      }
    }];

    Plotly.plot('container_capacity_sorted', data, layout, {showlink: false});
  }

  capacity_percent(metric) {
    if (metric == null) {
      return;
    }

    const med = metric['median'].toString();
    const layout = {
      title: 'Capacity (median: ' + med + ')',
      titlefont: {
        size: 20
      },
      font: {
        family: 'Droid Serif, serif',
        size: 10,
        color: '#000999'
      },
      dragmode: false,
    }

    const data: Plotly.PlotData[] = [{
      type: 'pie',
      // lables: ['>' + med, '<' + med, '=' + med],
      text: ['>' + med, '<' + med, '=' + med],
      values: [metric['>'], metric['<'], metric['=']],
      autosourcescale: true,
      reversescale: false,
      marker: {
        line: {
          source: 'rgb(180,180,180)',
          width: 1
        }
      }
    }];

    Plotly.plot('container_capacity', data, layout, {showlink: false});
  }
}
