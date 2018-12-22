use std::io::Write;
use std::io::Read;
use std::fs::File;

fn main() {
    let mut input = File::open("assignment.in").unwrap();
    let mut output = File::create("assignment.out").unwrap();
    
    let mut buf = String::new();
    input.read_to_string(&mut buf).unwrap();
    let mut iter = buf.trim().split_whitespace();
    let n : usize = iter.next().unwrap().parse().unwrap();
    
    let mut matrix : Vec<Vec<i64>> = vec![];
    for row in 0..n {
        matrix.push(vec![]);
        for _col in 0..n {
            let price : i64 = iter.next().unwrap().parse().unwrap();
            matrix[row].push(price);
        }
    }
    let matrix = matrix;
    
    let mut cost : i64 = 0;
    
    let inf : i64 = 1_000_000_000;
    
    let mut rows   : Vec<i64> = vec![0; n];
    let mut cols   : Vec<i64> = vec![0; n];
    let mut marked : Vec<i64> = vec![-1; n];
    
    for cur_row in 0..n {
        let mut marked_row : i64 = cur_row as i64;
        let mut marked_col : i64 = -1;
        let mut cur_col    : i64;
        
        let mut mins       : Vec<i64> = vec![inf; n];
        let mut used       : Vec<bool> = vec![false; n];
        let mut links      : Vec<i64> = vec![-1; n];
        
        loop {
            cur_col = -1;
            let mut delta : i64 = inf;
            for col in 0..n {
                if !used[col] {
                    let cur : i64 = matrix[marked_row as usize][col] - rows[marked_row as usize] - cols[col];
                    if  cur < mins[col] {
                        mins[col] = cur;
                        links[col] = marked_col;
                    }
                    if mins[col] < delta {
                        delta = mins[col];
                        cur_col = col as i64;
                    }
                }
            }
            
            for col in 0..n {
                if used[col] {
                    rows[marked[col] as usize] += delta;
                    cols[col] -= delta;
                } else {
                    mins[col] -= delta;
                }
            }
            
            cost += delta;
            
            rows[cur_row] += delta;
            used[cur_col as usize] = true;
            marked_col = cur_col;
            marked_row = marked[marked_col as usize];
            if marked_row == -1 {
                break;
            }
        }
        
        loop {
            if links[cur_col as usize] == -1 {
                break;
            }
            marked[cur_col as usize] = marked[links[cur_col as usize] as usize];
            cur_col = links[cur_col as usize];
        }
        marked[cur_col as usize] = cur_row as i64;
    }
    
    output.write((cost.to_string() + "\n").as_bytes()).unwrap();
    for i in 0..n {
        if marked[i] != -1 {
            output.write(((marked[i] + 1).to_string() + " " + &(i + 1).to_string() + "\n").as_bytes()).unwrap();
        }
    }
}
