// Message definition
//
use std::String
use std::vec
use chrono::{DateTime, TimeZone, NaiveDateTime, UTC};
use iface::operation;


struct Message {
    id: String;
    content: String;
    created_at: DateTime;
}


impl Operation for Message {
    fn save(&self) {
        // write db
    }

    fn delete(&self) {
        // write db
    }
}
