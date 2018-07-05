// Trust service
//
use iface;

fn main() {
    println!("trust backend started");
    logging::init();
    let trust = Trust::new();
    trust.start();
}
