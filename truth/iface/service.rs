// Service interface
//
use std::String;

pub enum Status {
    ERROR: i32,
    OK: i32,
}


pub struct ServiceStatus {
    name: String;
    status: Status;
    desc: String;
}

trait service {
    fn init(&self);
    fn start(&self);
    fn stop(&self);
    fn status(&self) -> ServiceStatus;
}
