// User definition
//
use std::String;
use std::vec;
use chrono::{DateTime, TimeZone, NaiveDateTime, UTC};
use iface::operation;


struct User { 
    id: String;
    name: String;
    comments: vec::Vec<String> ;
    messages: vec::Vec<String>;
    followers: vec::Vec<String>;
    following: vec::Vec<String>;
    created_at: DateTime;
    last_login: DateTime;
    email: String;
}

impl Operation for User {
    fn save(&self) {
        log!("saving user {:?}", self.name);
        // write db
    }

    fn delete (&self) {
        log!("deleting user {:?}", self.name);
        // write db
    }
}
