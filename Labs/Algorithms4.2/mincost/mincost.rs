use std::io::Write;
use std::io::Read;
use std::fs::File;
use std::collections::VecDeque;

struct Edge {
    from  : usize,
    to    : usize,
    cap   : i64,
    flow  : i64,
    price : i64,
    rev   : usize,
}

fn main() {
    let mut input = File::open("mincost.in").unwrap();
    let mut output = File::create("mincost.out").unwrap();
    
    let mut buf = String::new();
    input.read_to_string(&mut buf).unwrap();
    let mut iter = buf.trim().split_whitespace();
    let n : usize = iter.next().unwrap().parse().unwrap();
    let m : usize = iter.next().unwrap().parse().unwrap();
    
    let mut edges : Vec<Edge> = vec![];
    let mut graph : Vec<Vec<usize>> = vec![vec![]; n];
    
    for _i in 0..m {
        let from  : usize = iter.next().unwrap().parse().unwrap();
        let to    : usize = iter.next().unwrap().parse().unwrap();
        let cap   : i64 = iter.next().unwrap().parse().unwrap();
        let price : i64 = iter.next().unwrap().parse().unwrap();
        edges.push(Edge { from  : from - 1, 
                          to    : to - 1, 
                          cap   : cap, 
                          flow  : 0, 
                          price : price, 
                          rev   : 0 });
        edges.push(Edge { from  : to - 1, 
                          to    : from - 1, 
                          cap   : 0, 
                          flow  : 0, 
                          price : -price,
                          rev   : 0 });
        let len : usize = edges.len();
        edges[len - 1].rev = len - 2;
        edges[len - 2].rev = len - 1;
        graph[edges[len - 1].from].push(len - 1);
        graph[edges[len - 2].from].push(len - 2);
    }
    
    let mut cost : i64 = 0;
    
    let inf : i64 = 1_000_000_000_000;
    
    /*let mut fi : Vec<i64> = vec![inf; n]; //Djonson's potential
    fi[0] = 0;
    
    loop {
        let mut any : bool = false;
        for (num, edge) in edges.iter().enumerate() {
            if fi[edge.from] < inf 
            && edge.flow < edge.cap 
            && fi[edge.to] > fi[edge.from] + edge.price {
                fi[edge.to] = fi[edge.from] + edge.price;
                any = true;
            }
        }
        
        if !any {
            break;
        }
    }*/
    
    let mut d : Vec<i64> = vec![inf; n];
    let mut p : Vec<usize> = vec![inf as usize; n];
    let mut i : Vec<u16> = vec![0; n];
    let mut q : VecDeque<usize> = VecDeque::new();
    
    loop {
        for el in &mut d {
            *el = inf;
        }
        for el in &mut p {
            *el = inf as usize;
        }
        for el in &mut i {
            *el = 0;
        }
        d[0] = 0;
        q.push_back(0);
        
        while !q.is_empty() {
            let v : usize = q.pop_front().unwrap();
            i[v] = 1;
            for u in &graph[v] {
                let edge : &Edge = &edges[*u];
                if d[v] < inf
                && d[edge.to] > d[v] + edge.price
                && edge.flow < edge.cap {
                    d[edge.to] = d[v] + edge.price;
                    p[edge.to] = *u;
                    if i[edge.to] == 0 {
                        q.push_back(edge.to);
                    } else if i[edge.to] == 1 {
                        q.push_front(edge.to);
                    }
                    i[edge.to] = 1;
                }
            }
        }
        
        if d[n - 1] == inf {
            break;
        } else {
            let mut cur : usize = n - 1;
            let mut min : i64 = inf;
            while p[cur] != inf as usize {
                min = min.min(edges[p[cur]].cap - edges[p[cur]].flow);
                cur = edges[p[cur]].from;
            }
            cur = n - 1;
            while p[cur] != inf as usize {
                edges[p[cur]].flow += min;
                let rev = edges[p[cur]].rev;
                edges[rev].flow -= min;
                cost += min * edges[p[cur]].price;
                cur = edges[p[cur]].from;
            }
        }
    }
    
    output.write(cost.to_string().as_bytes()).unwrap();
}
