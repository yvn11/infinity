import { Component, OnInit } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import { environment } from '../../environments/environment';
import * as Highcharts from 'highcharts';

import * as d3 from 'd3';
import * as d3Axis from 'd3-axis';
import { scaleOrdinal, scaleLinear } from 'd3-scale';
import { format } from 'd3-format';

interface ResponseSessionClick {
  session_id: string;
  click_count: number;
}

@Component({
  selector: 'app-clickstream',
  templateUrl: './clickstream.component.html',
  styleUrls: ['./clickstream.component.css']
})
export class ClickstreamComponent implements OnInit {

  title = 'The BoringUI for Woody';

  constructor(private http_cli: HttpClient) {
    console.log(this.title);
    this.fetch_item_quan(100, 1000);
    this.fetch_session_quan(100, 1000);
    this.fetch_item_click(100, 100);
    this.fetch_session_click(30, 10);
  }

  ngOnInit() {
  }

  private fetch_item_click(gt: number, page: number) {
    const url = environment.woody_apiserver + '/v1/metrics/item_click'
      + '?' + 'gt=' + gt + '&page=' + page; 
    this.http_cli.get(url)
      .subscribe(rsp => { this.item_click(rsp); });
  }

  item_click(rsp) {
    if (rsp == null) { return; }
    if (rsp['response'] == null) { return; }

    let item_ids = [];
    let counts = [];
    for (let i = 0; i < rsp['response'].length; i++) {
      item_ids.push(rsp['response'][i]['item_id']);
      counts.push(rsp['response'][i]['click_count']);
    }
    
    Highcharts.chart('container_item_click', {
      chart: {
        type: 'bar'
      },
      title: {
        text: 'Item Click Count'
      },
      subtitle: {
        text: '(Count > 100)'
      },
      xAxis: {
        categories: item_ids,
        title: {
          text: 'Item ID'
        }
      },
      yAxis: {
        min: 0,
        title: {
          text: 'Count',
          align: 'high'
        },
        labels: {
          overflow: 'justify' as any
        }
      },
      /**tooltip: {
        valueSuffix: ' millions'
      },*/
      plotOptions: {
        bar: {
          dataLabels: {
            enabled: true
          }
        }
      },
      legend: {
        layout: 'vertical',
        align: 'right',
        verticalAlign: 'top',
        x: -40,
        y: 80,
        floating: true,
        borderWidth: 1,
        backgroundColor: '#FFFFFF',
        shadow: true
      },
      credits: {
        enabled: false
      },
      series: [{
        type: 'bar',
        name: 'Click Count',
        data: counts
        }]
    });
  }

  private fetch_item_quan(gt: number, page: number) {
    const url = environment.woody_apiserver + '/v1/metrics/item_quan'
      + '?' + 'gt=' + gt + '&page=' + page; 
    console.log(url);
    this.http_cli.get(url)
      .subscribe(rsp => { this.item_quan(rsp); });
  }

  item_quan(rsp) {
    if (rsp == null) { return; }
    if (rsp['response'] == null) { return; }

    let item_ids = [];
    let quans = [];
    for (let i = 0; i < rsp['response'].length; i++) {
      item_ids.push(rsp['response'][i]['item_id']);
      quans.push(rsp['response'][i]['quan_bought']);
    }
    
    Highcharts.chart('container_item_quan', {
      chart: {
        type: 'bar'
      },
      title: {
        text: 'Item Quantity Bought'
      },
      subtitle: {
        text: '(Quantity > 100)'
      },
      xAxis: {
        categories: item_ids,
        title: {
          text: 'Item ID'
        }
      },
      yAxis: {
        min: 0,
        title: {
          text: 'Quantity',
          align: 'high'
        },
        labels: {
          overflow: 'justify' as any
        }
      },
      /**tooltip: {
        valueSuffix: ' millions'
      },*/
      plotOptions: {
        bar: {
          dataLabels: {
            enabled: true
          }
        }
      },
      legend: {
        layout: 'vertical',
        align: 'right',
        verticalAlign: 'top',
        x: -40,
        y: 80,
        floating: true,
        borderWidth: 1,
        backgroundColor: '#FFFFFF',
        shadow: true
      },
      credits: {
        enabled: false
      },
      series: [{
        type: 'bar',
        name: 'Quantity Bought',
        data: quans
        }]
    });
  }

  private fetch_session_click(gt: number, page: number) {
    const url = environment.woody_apiserver + '/v1/metrics/session_click'
      + '?' + 'gt=' + gt + '&page=' + page; 
    this.http_cli.get(url)
      .subscribe(rsp => { this.session_click(rsp); });
  }

  session_click(rsp) {
    if (rsp == null) { return; }
    if (rsp['response'] == null) { return; }

    let session_ids = [];
    let counts = [];
    for (let i = 0; i < rsp['response'].length; i++) {
      session_ids.push(rsp['response'][i]['session_id']);
      counts.push(rsp['response'][i]['click_count']);
    }
    
    Highcharts.chart('container_session_click', {
      chart: {
        type: 'bar'
      },
      title: {
        text: 'Session Click Count'
      },
      subtitle: {
        text: '(Count > 35)'
      },
      xAxis: {
        categories: session_ids,
        title: {
          text: 'Session ID'
        }
      },
      yAxis: {
        min: 0,
        title: {
          text: 'Count',
          align: 'high'
        },
        labels: {
          overflow: 'justify' as any
        }
      },
      /**tooltip: {
        valueSuffix: ' millions'
      },*/
      plotOptions: {
        bar: {
          dataLabels: {
            enabled: true
          }
        }
      },
      legend: {
        layout: 'vertical',
        align: 'right',
        verticalAlign: 'top',
        x: -40,
        y: 80,
        floating: true,
        borderWidth: 1,
        backgroundColor: '#FFFFFF',
        shadow: true
      },
      credits: {
        enabled: false
      },
      series: [{
        type: 'bar',
        name: 'Click Count',
        data: counts
        }]
    });
  }

  private fetch_session_quan(gt: number, page: number) {
    const url = environment.woody_apiserver + '/v1/metrics/session_quan'
      + '?' + 'gt=' + gt + '&page=' + page; 
    this.http_cli.get(url)
      .subscribe(rsp => { this.session_quan(rsp); });
  }

  session_quan(rsp) {
    if (rsp == null) { return; }
    if (rsp['response'] == null) { return; }

    let session_ids = [];
    let quans = [];
    for (let i = 0; i < rsp['response'].length; i++) {
      session_ids.push(rsp['response'][i]['session_id']);
      quans.push(rsp['response'][i]['quan_bought']);
    }
    
    Highcharts.chart('container_session_quan', {
      chart: {
        type: 'bar'
      },
      title: {
        text: 'Session Quantity Bought'
      },
      subtitle: {
        text: '(Quantity > 100)'
      },
      xAxis: {
        categories: session_ids,
        title: {
          text: 'Session ID'
        }
      },
      yAxis: {
        min: 0,
        title: {
          text: 'Quantity',
          align: 'high'
        },
        labels: {
          overflow: 'justify' as any
        }
      },
      /**tooltip: {
        valueSuffix: ' millions'
      },*/
      plotOptions: {
        bar: {
          dataLabels: {
            enabled: true
          }
        }
      },
      legend: {
        layout: 'vertical',
        align: 'right',
        verticalAlign: 'top',
        x: -40,
        y: 80,
        floating: true,
        borderWidth: 1,
        backgroundColor: '#FFFFFF',
        shadow: true
      },
      credits: {
        enabled: false
      },
      series: [{
        type: 'bar',
        name: 'Quantity Bought',
        data: quans
        }]
    });
  }
}
