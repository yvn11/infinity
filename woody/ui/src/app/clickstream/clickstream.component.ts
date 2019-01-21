import { Component, OnInit } from '@angular/core';
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

  constructor() {
  }

  ngOnInit() {
    this.start()
  }

  bar_chart() {
    //d3Axis.axisScale<string>()
    //.scale(scaleOrdinal<number>())
    const xAxis = scaleLinear() 
        .orient("bottom")
        .tickFormat(format("%Y-%m"));

    const yAxis = scaleLinear() 
        .orient("left")
        .ticks(10);

    const svg = d3.select("body").append("svg")
      .attr("width", 400)
      .attr("height", 400)
      .append("g");
  }

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
