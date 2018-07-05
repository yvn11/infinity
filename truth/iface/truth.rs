// Trust service
//
extern crate http;

use truth::iface::service;
use http::{Request, Response};

struct Trust {
    running: bool;
}


impl service for Trust {
    fn init(&self) {
        log!("trust initialization");
        self.running = true;
    }

    fn start(&self) {
        log!("starting trust");
        while (self.running) {
            // do something
        }
    }

    fn stop(&self) {
        log!("stopping trust");
        self.running = false;
    }

    fn status(&self) {
        log!("getting status");
    }
}


