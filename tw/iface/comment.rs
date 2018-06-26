// Comment definition
//
use std::String;
use std::vec;
use chrono::{DateTime, TimeZone, NaiveDateTime, UTC};
use iface::operation;


struct Comment {
    id: String;
    content: String;
    // http link path
    with_link: vec::Vec<String>;
    // image paths
    with_pic: vec::Vec<String>;
    // @ user id
    with_at: vec::Vec<String>;
    created_at: DateTime;
}

impl Operation for Comment {
    fn save(&self) {
        // write db
    }

    fn delete(&self) {
        // write db
    }
}
