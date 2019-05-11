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

  title = 'The BoringUI for Phi';
  itemQuanConf: MetricsConf;
  sessQuanConf: MetricsConf;
  itemClickConf: MetricsConf;
  sessClickConf: MetricsConf;
  cateClickConf: MetricsConf;
  eventStreamConf: MetricsConf;
  autoRefresh: boolean;
  refreshInterval: number; // ms
  // event_stream: Map<string, Array<number>>;

  constructor(private http_cli: HttpClient) {
    console.log(this.title);
    this.refreshInterval = 5000;
    this.autoRefresh = true;

    this.itemQuanConf = new MetricsConf();
    this.itemQuanConf.gt = 100;
    this.itemQuanConf.limit = 100;

    this.itemClickConf = new MetricsConf();
    this.itemClickConf.gt = 100;
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

    this.eventStreamConf = new MetricsConf();
    this.eventStreamConf.limit = 80;

    // this.event_stream = new Map<string, Array<number>>();
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
    // this.fetchCateClick();
    this.fetchClickES();
    this.fetchBuyES();
  }

  private fetchItemClick() {
    const url = environment.phi_apiserver + '/v1/metrics/click/item_click'
      + '?' + 'gt=' + this.itemClickConf.gt + '&limit=' + this.itemClickConf.limit;
    this.http_cli.get(url)
      .subscribe(rsp => { this.onItemClick(rsp); });
  }

  onItemClick(rsp) {
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
    this.refresh_item_click(item_ids, counts);
  }

  refresh_item_click(item_ids, counts) {
    Highcharts.chart('container_item_click', {
      chart: {
        type: 'bar',
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
    const url = environment.phi_apiserver + '/v1/metrics/click/item_quan'
      + '?' + 'gt=' + this.itemQuanConf.gt + '&limit=' + this.itemQuanConf.limit;
    this.http_cli.get(url)
      .subscribe(rsp => { this.onItemQuan(rsp); });
  }

  onItemQuan(rsp) {
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
    this.refresh_item_quan(item_ids, quans);
  }

  refresh_item_quan(item_ids, quans) {
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
    const url = environment.phi_apiserver + '/v1/metrics/click/session_click'
      + '?' + 'gt=' + this.sessClickConf.gt + '&limit=' + this.sessClickConf.limit;
    this.http_cli.get(url)
      .subscribe(rsp => { this.onSessClick(rsp); });
  }

  onSessClick(rsp) {
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
    this.refresh_session_click(session_ids, counts);
  }

  refresh_session_click(session_ids, counts) {
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
    const url = environment.phi_apiserver + '/v1/metrics/click/category_click'
      + '?' + 'gt=' + this.cateClickConf.gt + '&limit=' + this.cateClickConf.limit;
    this.http_cli.get(url)
      .subscribe(rsp => { this.onCateClick(rsp); });
  }

  onCateClick(rsp) {
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
    this.refresh_cate_click(category_ids, counts);
  }

  refresh_cate_click(category_ids, counts) {
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
    const url = environment.phi_apiserver + '/v1/metrics/click/session_quan'
      + '?' + 'gt=' + this.sessQuanConf.gt + '&limit=' + this.sessQuanConf.limit;
    this.http_cli.get(url)
      .subscribe(rsp => { this.onSessQuan(rsp); });
  }

  onSessQuan(rsp) {
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
    this.refresh_sess_quan(session_ids, quans);
  }

  refresh_sess_quan(session_ids, quans) {
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

  private fetchClickES() {
    const url = environment.phi_apiserver + '/v1/metrics/click/event_stream'
                + '?' + 'ev=click' + '&limit=' + this.eventStreamConf.limit;
    this.http_cli.get(url)
      .subscribe(rsp => { this.onClickES(rsp); });
  }

  onClickES(rsp) {
    if (this.autoRefresh) {
      setTimeout(() => this.fetchClickES(), this.refreshInterval);
    }

    const esClickTime = [];
    const esClickCount = [];

    if (rsp != null && rsp['response'] != null) {
      for (let i = rsp['response'].length - 1; i >= 0; i--) {
        const k = (new Date(rsp['response'][i]['ts'])).toString();
        /**
        if (this.event_stream[k] == null) {
          this.event_stream[k] = [rsp['response'][i]['count'], 0];
        } else {
          this.event_stream[k][0] = rsp['response'][i]['count'];
        }
        */
        esClickTime.push(k);
        esClickCount.push(rsp['response'][i]['count']);
      }
    }
    this.refreshES('container_es_click', 'Click Event Stream', esClickTime, esClickCount);
  }

  private fetchBuyES() {
    const url = environment.phi_apiserver + '/v1/metrics/click/event_stream'
                + '?' + 'ev=buy' + '&limit=' + this.eventStreamConf.limit;
    this.http_cli.get(url)
      .subscribe(rsp => { this.onBuyES(rsp); });
  }

  onBuyES(rsp) {
    if (this.autoRefresh) {
      setTimeout(() => this.fetchBuyES(), this.refreshInterval);
    }

    const esBuyTime = [];
    const esBuyCount = [];

    if (rsp != null && rsp['response'] != null) {
      for (let i = rsp['response'].length - 1; i >= 0; i--) {
        const k = (new Date(rsp['response'][i]['ts'])).toString();
        esBuyTime.push(k);
        esBuyCount.push(rsp['response'][i]['count']);
      }
    }
    this.refreshES('container_es_buy', 'Buy Event Stream', esBuyTime, esBuyCount);
  }

  refreshES(container, title, ts, counts) {
    Highcharts.chart(container, {
      chart: {
        type: 'line',
      },
      title: {
        text: title
      },
      xAxis: {
        categories: ts,
        title: {
          text: 'time'
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
      plotOptions: {
        line: {
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
        type: 'line',
        name: 'Count',
        data: counts
        }
      ]
    });
  }
}
