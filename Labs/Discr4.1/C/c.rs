use std::io::Write;
use std::io;

fn main() {
    let modul : i64 = 1_000_000_007;
    
    let stdin = io::stdin();
    
    let k : u16;
    let m : u16;
    
    {
        let mut buf = String::new();
        stdin.read_line(&mut buf).unwrap();
        let mut iter = buf.trim().split_whitespace();
        k = iter.next().unwrap().parse().unwrap();
        m = iter.next().unwrap().parse().unwrap();
    }
    
    let mut c : Vec<i64> = vec![];
    let mut d : Vec<i64> = vec![];
    let mut t : Vec<i64> = vec![0; m as usize];

    {
        let mut buf = String::new();
        stdin.read_line(&mut buf).unwrap();
        let mut iter = buf.trim().split_whitespace();
        for _i in 0..k {
            c.push(iter.next().unwrap().parse().unwrap());
        }
    }
    
    d.push(1);
    t[0] = 1;
    for w in 1..m + 1 {
        let mut dw : i64 = 0;
        for ci in &c {
            dw = (dw + if w as i64 - ci < 0 { 0 } else { t[(w as i64 - ci) as usize] }) % modul;
        }
        
        d.push(dw);
        
        for i in 0..w + 1 {
            if i + w < m {
                t[(i + w) as usize] = (t[(i + w) as usize] + if i != w { 2 } else { 1 } * dw * d[i as usize]) % modul;
            }
        }
        
        print!("{} ", dw);
    }
    
    println!();
    io::stdout().flush().unwrap();
}
