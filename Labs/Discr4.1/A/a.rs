use std::cmp::max;
use std::io::Write;
use std::io;

fn main() {
    let modul : i64 = 998_244_353;
    
    let stdin = io::stdin();
    
    let n : u16;
    let m : u16;
    
    {
        let mut buf = String::new();
        stdin.read_line(&mut buf).unwrap();
        let mut iter = buf.trim().split_whitespace();
        n = iter.next().unwrap().parse().unwrap();
        m = iter.next().unwrap().parse().unwrap();
    }
    
    let mut p : Vec<i64> = vec![0; 1001];
    let mut q : Vec<i64> = vec![0; 1001];

    {
        let mut buf = String::new();
        stdin.read_line(&mut buf).unwrap();
        let mut iter = buf.trim().split_whitespace();
        for i in 0..n + 1 {
            p[i as usize] = iter.next().unwrap().parse().unwrap();
        }
    }

    {
        let mut buf = String::new();
        stdin.read_line(&mut buf).unwrap();
        let mut iter = buf.trim().split_whitespace();
        for i in 0..m + 1 {
            q[i as usize] = iter.next().unwrap().parse().unwrap();
        }
    }
    
    println!("{}", max(n, m));
    for i in 0..max(n, m) + 1 {
        print!("{} ", (p[i as usize] + q[i as usize]) % modul);
    }
    println!();
    
    println!("{}", n + m);
    for i in 0..n + m + 1 {
        let mut tmp : i64 = 0;
        for j in 0..i + 1 {
            tmp = (tmp + if j < 1001 { p[j as usize] } else { 0 } * if i - j < 1001 { q[(i - j) as usize] } else { 0 }) % modul;
        }
        
        print!("{} ", tmp);
    }
    println!();

    let mut t : Vec<i64> = vec![];
    for i in 0..1000 {
        let mut tmp = 0;
        for j in 0..i {
            tmp = (tmp + t[j as usize] * q[(i - j) as usize]) % modul;
        }
        t.push((p[i] + modul - tmp) % modul);
        
        print!("{} ", t[i]);
    }
    println!();
    
    io::stdout().flush().unwrap();
}
