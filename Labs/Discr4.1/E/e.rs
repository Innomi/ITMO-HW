use std::io::Write;
use std::io;

fn main() {
    let modul : u64 = 104_857_601;
    
    let stdin = io::stdin();
    
    let k : usize;
    let mut n : usize;
    
    {
        let mut buf = String::new();
        stdin.read_line(&mut buf).unwrap();
        let mut iter = buf.trim().split_whitespace();
        k = iter.next().unwrap().parse().unwrap();
        n = iter.next().unwrap().parse::<usize>().unwrap() - 1;
    }
    
    let mut a : Vec<u64> = vec![0; k << 1];
    let mut c : Vec<u64> = vec![0; k << 1 + 1];
    c[0] = 1;

    {
        let mut buf = String::new();
        stdin.read_line(&mut buf).unwrap();
        let mut iter = buf.trim().split_whitespace();
        for i in 0..k {
            a[i] = iter.next().unwrap().parse().unwrap();
        }
    }

    {
        let mut buf = String::new();
        stdin.read_line(&mut buf).unwrap();
        let mut iter = buf.trim().split_whitespace();
        for i in 1..k + 1 {
            c[i] = modul - iter.next().unwrap().parse::<u64>().unwrap();
        }
    }
    
    while n >= k {
        for i in k..k << 1 {
            let mut ai : u64 = 0;
            for j in 1..k + 1 {
                ai = (ai + (modul - c[j]) *  a[i - j]) % modul;
            }
            a[i] = ai;
        }
        
        let mut new_c : Vec<u64> = vec![0; (k << 1) + 1];
        for i in 0..(k << 1) + 1 {
            let mut ci : u64 = 0;
            for j in 0..i + 1 {
                ci = (ci + if j & 1 == 1 { (modul - c[j]) } else { c[j] } * c[i - j]) % modul;
            }
            if i & 1 == 0 {
                new_c[i >> 1] = ci;
            }
        }
        c = new_c;
        
        for i in 0..k {
            a[i] = a[(i << 1) + (n & 1)];
        }
        
        n >>= 1;
    }
    
    println!("{}", a[n]);
    
    io::stdout().flush().unwrap();
}
