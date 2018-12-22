use std::io;
use std::io::Write;

fn comb(n : u64, k : u64) -> u64 {
    if k > n {
        return 0;
    }
    let mut c : u64 = 1;
    for i in n - k + 1..n + 1 {
        c *= i;
    }
    for i in 2..k + 1 {
        c /= i;
    }
    c
}

fn gcd(mut a : usize, mut b : usize) -> usize {
    let mut tmp : usize;
    if a < b {
        tmp = a;
        a = b;
        b = tmp;
    }
    while b > 0 {
        tmp = a % b;
        a = b;
        b = tmp;
    }
    a
}

fn main() {
    let n : usize = 7;
    
    let mut input_str = String::new();
    
    io::stdin().read_line(&mut input_str).unwrap();
    
    let mut stack : Vec<Vec<u64>> = vec![];
    
    for ch in input_str.as_str().chars().rev() {
        match ch {
            'B' => {
                stack.push(vec![0, 1, 0, 0, 0, 0, 0]);
            },
            'L' => {
                let x : Vec<u64> = stack.pop().unwrap();
                let mut l : Vec<u64> = vec![1];
                
                for w in 1..n {
                    l.push(0);
                    for i in 1..w + 1 {
                        l[w] += x[i] * l[w - i];
                    }
                }
                
                stack.push(l);
            },
            'S' => {
                let x : Vec<u64> = stack.pop().unwrap();
                let mut s : Vec<u64> = vec![];
                let mut sd : Vec<Vec<u64>> = vec![vec![0; n]; n];
                
                for i in 0..n {
                    sd[0][i] = 1;
                }
                for i in 1..n {
                    for j in 1..n {
                        if x[j] > 0 {
                            for k in 0..i / j + 1 {
                                    sd[i][j] += comb(x[j] + k as u64 - 1, k as u64) * sd[i - k * j][j - 1];
                            }
                        } else {
                            sd[i][j] = sd[i][j - 1];
                        }
                    }
                }
                
                for w in 0..n {
                    s.push(sd[w][w]);
                }
                
                stack.push(s);
            },
            'C' => {
                let x : Vec<u64> = stack.pop().unwrap();
                let mut c : Vec<u64> = vec![0];
                let mut cd : Vec<Vec<u64>> = vec![vec![0; n]; n];
                
                for i in 0..n {
                    cd[i][1] = x[i];
                    for j in 2..n {
                        for k in 1..i {
                            cd[i][j] += x[k] * cd[i - k][j - 1];
                        }
                    }
                }
                
                for w in 1..n {
                    c.push(0);
                    for l in 1..w + 1 {
                        let mut tmp : u64 = 0;
                        for i in 0..l {
                            let g : usize = gcd(l, i);
                            if w % (l / g) == 0 {
                                tmp += cd[w * g / l][g];
                            }
                        }
                        c[w] += tmp / l as u64;
                    }
                }
                
                stack.push(c);
            },
            'P' => {
                let x : Vec<u64> = stack.pop().unwrap();
                let y : Vec<u64> = stack.pop().unwrap();
                let mut p : Vec<u64> = vec![];
                
                for w in 0..n {
                    p.push(0);
                    for i in 0..w + 1 {
                        p[w] += x[i] * y[w - i];
                    }
                }
                
                stack.push(p);
            },
            _ => (),
        }
    }
    
    for el in &stack[0] {
        print!("{} ", el);
    }
    println!();
    
    io::stdout().flush().unwrap();
}
