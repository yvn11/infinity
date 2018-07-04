// Logging component
//
extern crate log;
extern crate log4rs;

use common::shared;

fn init() {
    log4rs.init_file(LOGGING_CONFIG_PATH, Default::default()).unwrap();
}


