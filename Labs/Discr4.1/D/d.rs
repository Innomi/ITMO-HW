use std::io::Write;
use std::io;

fn main() {
    let modul : i64 = 998_244_353;
    
    let stdin = io::stdin();
    
    let k : usize;
    let n : usize;
    
    {
        let mut buf = String::new();
        stdin.read_line(&mut buf).unwrap();
        let mut iter = buf.trim().split_whitespace();
        k = iter.next().unwrap().parse().unwrap();
        n = iter.next().unwrap().parse().unwrap();
    }
    
    let mut a : Vec<i64> = vec![];
    let mut c : Vec<Vec<i64>> = vec![vec![0; k]; k];
    let mut d : Vec<i64> = vec![];

    for i in 0..k {
        c[i][0] = 1;
        for j in 1..i + 1 {
            c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % modul;
        }
    }
    
    for i in 0..(k + 1) >> 1 {
        if i & 1 != 0 {
            a.push(c[k - 1 - i][i]);
        } else {
            a.push(modul - c[k - 1 - i][i]);
        }
    }
    
    d.push(1);
    for i in 1..k - 1 {
        let mut di : i64 = 0;
        for j in 0..i {
            di = (di + d[j] * d[i - 1 - j]) % modul;
        }
        d.push(di);
    }

    for i in k - 1..n {
        let mut di : i64 = 0;
        for j in 1..(k + 1) >> 1 {
            di = (di + a[j] * d[i - j]) % modul;
        }
        d.push(di);
    }
    
    for i in 0..n {
        println!("{} ", d[i]);
    }
    
    println!();
    io::stdout().flush().unwrap();
}
