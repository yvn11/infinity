import { async, ComponentFixture, TestBed } from '@angular/core/testing';

import { ClickstreamComponent } from './clickstream.component';

describe('ClickstreamComponent', () => {
  let component: ClickstreamComponent;
  let fixture: ComponentFixture<ClickstreamComponent>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ ClickstreamComponent ]
    })
    .compileComponents();
  }));

  beforeEach(() => {
    fixture = TestBed.createComponent(ClickstreamComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
