// Quick sort in RUST
// Author: Zex Li <dbloodwxp@gmail.com>
use std::vec;
use std::time::{Instant};

extern crate rand;
use rand::{thread_rng, Rng};

fn qpart(list: &mut vec::Vec<usize>, begin: usize, end: usize) -> usize {
    let pivot = list[end];
    let mut i = begin;

    for j in begin..end {
        if list[j] < pivot {
            list.swap(i, j);
            i += 1;
        }
    }
    list.swap(i, end);
    return i;
}

fn qsort(list: &mut vec::Vec<usize>, begin: usize, end: usize) {
    if end <= begin { return; }
    let pivot = qpart(list, begin, end);
    if pivot > 0 {
        qsort(list, begin, pivot-1);
    }
    qsort(list, pivot+1, end);
}

fn main() {
    let mut data = vec::Vec::new();
    for i in 1..101 {
        data.push(i);
    }

    let mut rng = thread_rng();
    rng.shuffle(&mut data);
    println!("before: {:?}", data);

    let end = data.len() - 1;
    let now = Instant::now();
    qsort(&mut data, 0, end);
    let elapsed = now.elapsed();
    println!("elapsed: {}ms", (elapsed.as_secs() as f64) + f64::from(elapsed.subsec_nanos())/1000_000.0);
    println!("after: {:?}", data);
}
