import { Component, OnInit } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import * as Highcharts from 'highcharts';
import { environment } from '../../environments/environment';
import { MetricsConf } from '../common/shared';

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
  itemQuanConf: MetricsConf;
  sessQuanConf: MetricsConf;
  itemClickConf: MetricsConf;
  sessClickConf: MetricsConf;
  cateClickConf: MetricsConf;
  autoRefresh: boolean;
  refreshInterval: number; // ms

  constructor(private http_cli: HttpClient) {
    console.log(this.title);
    this.refreshInterval = 2000;
    this.autoRefresh = true;

    this.itemQuanConf = new MetricsConf();
    this.itemQuanConf.gt = 1000;
    this.itemQuanConf.limit = 100;

    this.itemClickConf = new MetricsConf();
    this.itemClickConf.gt = 10000;
    this.itemClickConf.limit = 100;

    this.sessQuanConf = new MetricsConf();
    this.sessQuanConf.gt = 30;
    this.sessQuanConf.limit = 100;

    this.sessClickConf = new MetricsConf();
    this.sessClickConf.gt = 30;
    this.sessClickConf.limit = 100;

    this.cateClickConf = new MetricsConf();
    this.cateClickConf.gt = 100;
    this.cateClickConf.limit = 100;
  }

  ngOnInit() {
    Highcharts.setOptions({
      plotOptions: {
        series: {
          animation: false
        }
      }
    });

    this.fetchItemQuan();
    this.fetchSessQuan();
    this.fetchItemClick();
    this.fetchSessClick();
    this.fetchCateClick();
  }

  private fetchItemClick() {
    const url = environment.woody_apiserver + '/v1/metrics/item_click'
      + '?' + 'gt=' + this.itemClickConf.gt + '&limit=' + this.itemClickConf.limit;
    this.http_cli.get(url)
      .subscribe(rsp => { this.item_click(rsp); });
  }

  item_click(rsp) {
    if (this.autoRefresh) {
      setTimeout(() => this.fetchItemClick(), this.refreshInterval);
    }

    const item_ids = [];
    const counts = [];

    if (rsp != null && rsp['response'] != null) {
      for (let i = 0; i < rsp['response'].length; i++) {
        item_ids.push(rsp['response'][i]['item_id']);
        counts.push(rsp['response'][i]['click_count']);
      }
    }

    Highcharts.chart('container_item_click', {
      chart: {
        type: 'bar',
        animation: false
      },
      title: {
        text: 'Item Click Count'
      },
      subtitle: {
        text: '(Count > ' + this.itemClickConf.gt + ')'
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

  private fetchItemQuan() {
    const url = environment.woody_apiserver + '/v1/metrics/item_quan'
      + '?' + 'gt=' + this.itemQuanConf.gt + '&limit=' + this.itemQuanConf.limit;
    this.http_cli.get(url)
      .subscribe(rsp => { this.item_quan(rsp); });
  }

  item_quan(rsp) {
    if (this.autoRefresh) {
      setTimeout(() => this.fetchItemQuan(), this.refreshInterval);
    }

    const item_ids = [];
    const quans = [];

    if (rsp != null && rsp['response'] != null) {
      for (let i = 0; i < rsp['response'].length; i++) {
        item_ids.push(rsp['response'][i]['item_id']);
        quans.push(rsp['response'][i]['quan_bought']);
      }
    }

    Highcharts.chart('container_item_quan', {
      chart: {
        type: 'bar'
      },
      title: {
        text: 'Item Quantity Bought'
      },
      subtitle: {
        text: '(Quantity > ' + this.itemQuanConf.gt + ')'
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
        name: 'Quantity',
        data: quans
        }]
    });
  }

  private fetchSessClick() {
    const url = environment.woody_apiserver + '/v1/metrics/session_click'
      + '?' + 'gt=' + this.sessClickConf.gt + '&limit=' + this.sessClickConf.limit;
    this.http_cli.get(url)
      .subscribe(rsp => { this.session_click(rsp); });
  }

  session_click(rsp) {
    if (this.autoRefresh) {
      setTimeout(() => this.fetchSessClick(), this.refreshInterval);
    }

    const session_ids = [];
    const counts = [];

    if (rsp != null && rsp['response'] != null) {
      for (let i = 0; i < rsp['response'].length; i++) {
        session_ids.push(rsp['response'][i]['session_id']);
        counts.push(rsp['response'][i]['click_count']);
      }
    }

    Highcharts.chart('container_session_click', {
      chart: {
        type: 'bar'
      },
      title: {
        text: 'Session Click Count'
      },
      subtitle: {
        text: '(Count > ' + this.sessClickConf.gt + ')'
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

  private fetchCateClick() {
    const url = environment.woody_apiserver + '/v1/metrics/category_click'
      + '?' + 'gt=' + this.cateClickConf.gt + '&limit=' + this.cateClickConf.limit;
    this.http_cli.get(url)
      .subscribe(rsp => { this.category_click(rsp); });
  }

  category_click(rsp) {
    if (this.autoRefresh) {
      setTimeout(() => this.fetchSessClick(), this.refreshInterval);
    }

    const category_ids = [];
    const counts = [];

    if (rsp != null && rsp['response'] != null) {
      for (let i = 0; i < rsp['response'].length; i++) {
        category_ids.push(rsp['response'][i]['category']);
        counts.push(rsp['response'][i]['click_count']);
      }
    }

    Highcharts.chart('container_category_click', {
      chart: {
        type: 'bar'
      },
      title: {
        text: 'Category Click Count'
      },
      subtitle: {
        text: '(Count > ' + this.cateClickConf.gt + ')'
      },
      xAxis: {
        categories: category_ids,
        title: {
          text: 'Category ID'
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

  private fetchSessQuan() {
    const url = environment.woody_apiserver + '/v1/metrics/session_quan'
      + '?' + 'gt=' + this.sessQuanConf.gt + '&limit=' + this.sessQuanConf.limit;
    this.http_cli.get(url)
      .subscribe(rsp => { this.session_quan(rsp); });
  }

  session_quan(rsp) {
    if (this.autoRefresh) {
      setTimeout(() => this.fetchSessQuan(), this.refreshInterval);
    }

    const session_ids = [];
    const quans = [];

    if (rsp != null && rsp['response'] != null) {
      for (let i = 0; i < rsp['response'].length; i++) {
        session_ids.push(rsp['response'][i]['session_id']);
        quans.push(rsp['response'][i]['quan_bought']);
      }
    }

    Highcharts.chart('container_session_quan', {
      chart: {
        type: 'bar'
      },
      title: {
        text: 'Session Quantity Bought'
      },
      subtitle: {
        text: '(Quantity > ' + this.sessQuanConf.gt + ')'
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
        name: 'Quantity',
        data: quans
        }]
    });
  }
}
