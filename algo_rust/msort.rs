// Merge sort in RUST
// Author: Zex Li <dbloodwxp@gmail.com>
use std::vec;
use std::time::{Instant};

extern crate rand;
use rand::{thread_rng, Rng};

fn merge(list: &mut Vec<usize>, aux: &mut Vec<usize>, begin: usize, end: usize) {
    let mid = (begin+end)/2;
    let mut i = begin;
    let mut j = mid+1;
    let mut k = begin;
    
    while i <= mid && j <= end {
        if list[i] < list[j] {
            aux[k] = list[i];
            k += 1; i += 1;
        } else {
            aux[k] = list[j];
            k += 1; j += 1;
        }
    }

    while i <= mid {
        aux[k] = list[i];
        k += 1; i += 1;
    }

    while j <= end {
        aux[k] = list[j];
        k += 1; j += 1;
    }

    for i in begin..end+1 {
        list[i] = aux[i];
    }
}


fn msort(list: &mut Vec<usize>, aux: &mut Vec<usize>, begin: usize, end: usize) {
    if end <= begin { return; }
    let mid = (begin+end)/2;
    msort(list, aux, begin, mid);
    msort(list, aux, mid+1, end);
    merge(list, aux, begin, end);
}


fn main() {
    let mut data = vec::Vec::new();
    for i in 1..101 {
        data.push(i);
    }

    let mut aux = vec![0;data.len()];
    let mut rng = thread_rng();
    rng.shuffle(&mut data);

    println!("before: {:?}", data);
    let now = Instant::now();
    let end = data.len()-1;
    msort(&mut data, &mut aux, 0, end);
    let elapsed = now.elapsed();
    println!("elapsed: {}ms", (elapsed.as_secs() as f64) + f64::from(elapsed.subsec_nanos())/1000_000.0);
    println!("after: {:?}", data);
}
