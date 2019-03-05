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

  title = 'The BoringUI for Woody';
  constructor(private http_cli: HttpClient) {
    console.log(this.title);
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
    this.country_made_percent(rsp['metric_country_made']);
    this.newenergy_each_percent(rsp['metric_newenergy_each']);
    this.source_percent(rsp['metric_source']);
    this.color_percent(rsp['metric_color']);
  }

  brand_percent(metric) {
    if (metric == null || metric['x'] == null || metric['y'] == null) {
      return;
    }

    const layout = {
      title: 'Brand Percentage',
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
      name: 'Brand Percentage',
      marker: {
        line: {
          color: 'rgb(180,180,180)',
          width: 1
        }
      }
    }];

    Plotly.plot('container_brand', data, layout, {showlink: false});
  }

  country_made_percent(metric) {
    if (metric == null || metric['x'] == null || metric['y'] == null) {
      return;
    }

    const layout = {
      title: 'Country Made Percentage',
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

    Plotly.plot('container_country_made', data, layout, {showlink: false});
  }

  newenergy_percent(metric) {
    if (metric == null || metric['x'] == null || metric['y'] == null) {
      return;
    }

    const layout = {
      title: 'Newenergy Percentage',
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

  newenergy_each_percent(metric) {
    if (metric == null || metric['x'] == null || metric['y'] == null) {
      return;
    }

    const layout = {
      title: 'Newenergy Kind Percentage',
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

    Plotly.plot('container_newenergy_each', data, layout, {showlink: false});
  }

  color_percent(metric) {
    if (metric == null || metric['x'] == null || metric['y'] == null) {
      return;
    }

    const layout = {
      title: 'Color Percentage',
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

  source_percent(metric) {
    if (metric == null || metric['x'] == null || metric['y'] == null) {
      return;
    }

    const layout = {
      title: 'Source Percentage',
      titlefont: {
        size: 20
      },
      font: {
        family: 'Droid Serif, serif',
        size: 10,
        source: '#000999'
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

    Plotly.plot('container_source', data, layout, {showlink: false});
  }
}
