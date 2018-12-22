use std::io::Write;
use std::io::Read;
use std::fs::File;

fn main() {
    let mut input = File::open("rps2.in").unwrap();
    let mut output = File::create("rps2.out").unwrap();
    
    let mut buf = String::new();
    input.read_to_string(&mut buf).unwrap();
    let mut iter = buf.trim().split_whitespace();
    
    let r1 : i32 = iter.next().unwrap().parse().unwrap();
    let s1 : i32 = iter.next().unwrap().parse().unwrap();
    let p1 : i32 = iter.next().unwrap().parse().unwrap();
    let r2 : i32 = iter.next().unwrap().parse().unwrap();
    let s2 : i32 = iter.next().unwrap().parse().unwrap();
    let p2 : i32 = iter.next().unwrap().parse().unwrap();
    
    output.write(0.max((p1 - p2 - s2).max((r1 - r2 - p2).max(s1 - s2 - r2))).to_string().as_bytes()).unwrap();
}
