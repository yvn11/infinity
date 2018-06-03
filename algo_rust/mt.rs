// Multithreading in RUST
// Author: Zex Li <dbloodwxp@gmail.com>
use std::sync::{Arc, Mutex};
use std::sync::mpsc::channel;
use std::sync::mpsc::TryRecvError;
use std::time::{Instant};
use std::thread;
use std::time::Duration;
use std::vec;

extern crate rand;
use rand::{thread_rng, Rng};

fn go_zoo(id: usize, name: String) {
    println!("[{}] {} go to zoo", id, name);
}

fn thr_group() {
    let tasks = thread::spawn(||{
        let name = "zex";

        for i in 1..100 {
            go_zoo(i, name.to_string());
            thread::sleep(Duration::from_millis(1));
        }
    });

    let res = tasks.join(); 
    println!("tasks done: ok:{} err:{}", res.is_ok(), res.is_err());

    let mut task_list = vec::Vec::new();
    let name = "rust";
    for i in 1..10 {
        task_list.push(thread::spawn(move ||{
            let each_name = format!("{}/{}", name, thread_rng().gen_range(10, 30));
            go_zoo(i, each_name.to_string());
            thread::sleep(Duration::from_millis(1));
        }));
    }
    for _t in task_list {let _ = _t.join();}
}


fn txrx() {
    let big_block = Arc::new(Mutex::new(0));
    let (tx, rx) = channel();
    let name = "ZOO";
    let mut task_list = vec::Vec::new();

    for _ in 1..100 {
        let thr_tx = tx.clone();
        let data = big_block.clone();
        task_list.push(thread::spawn(move || {
            *data.lock().unwrap() += 10;
            let each_name = format!("{}/{}", name, thread_rng().gen_range(10, *data.lock().unwrap()));
            println!("[{:?}] tx: {} {}", Instant::now(), each_name.clone(),
                     thr_tx.send(each_name).is_ok());
        }));
    }

    let mut ans = rx.try_recv();
    loop {
        match ans {
            Err(TryRecvError::Disconnected) => { break; }
            Err(TryRecvError::Empty) => { break; }
            Ok(_) => {
                println!("[{:?}] rx: {}", Instant::now(), ans.unwrap());
                ans = rx.try_recv();
            }
        }
    } 
    for _t in task_list {let _ = _t.join();}
}

fn main() {
    thr_group();
    txrx();
}
