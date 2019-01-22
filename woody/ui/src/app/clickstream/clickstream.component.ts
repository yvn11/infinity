import { Component, OnInit } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import { environment } from '../../environments/environment';
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
    this.fetch_item_click();
    this.fetch_item_quan();
    this.fetch_session_click();
    this.fetch_session_click();
  }

  ngOnInit() {
  }

  private fetch_item_click() {
    const url = environment.woody_apiserver + '/v1/metrics/item_click';
    this.http_cli.get(url)
      .subscribe(rsp => { this.item_click(rsp); });
  }

  item_click(rsp) {
    if (rsp == null) { return; }
    if (rsp['response'] == null) { return; }
    console.log('item_click', rsp['response']);
  }

  private fetch_item_quan() {
    const url = environment.woody_apiserver + '/v1/metrics/item_quan';
    console.log(url);
    this.http_cli.get(url)
      .subscribe(rsp => { this.item_quan(rsp); });
  }

  item_quan(rsp) {
    if (rsp == null) { return; }
    if (rsp['response'] == null) { return; }
    console.log('item_quan', rsp['response']);
  }

  private fetch_session_click() {
    const url = environment.woody_apiserver + '/v1/metrics/session_click';
    this.http_cli.get(url)
      .subscribe(rsp => { this.session_click(rsp); });
  }

  session_click(rsp) {
    if (rsp == null) { return; }
    if (rsp['response'] == null) { return; }
    console.log('session_click', rsp['response']);
  }

  private fetch_session_quan() {
    const url = environment.woody_apiserver + '/v1/metrics/session_quan';
    this.http_cli.get(url)
      .subscribe(rsp => { this.session_quan(rsp); });
  }

  session_quan(rsp) {
    if (rsp == null) { return; }
    if (rsp['response'] == null) { return; }
    console.log('session_quan', rsp['response']);
  }
  /**
  bar_chart() {
    // d3Axis.axisScale<string>()
    // .scale(scaleOrdinal<number>())
    const xAxis = scaleLinear()
        .orient('bottom')
        .tickFormat(format('%Y-%m'));

    const yAxis = scaleLinear()
        .orient('left')
        .ticks(10);

    const svg = d3.select('body').append('svg')
      .attr('width', 400)
      .attr('height', 400)
      .append('g');
  }
  */
  start() {
  const chart = d3.json<ResponseSessionClick>('data.json')
      .then((data) => {
        console.log(data);
      })
      .catch((err) => {
        console.error(err);
      });
  }
}
