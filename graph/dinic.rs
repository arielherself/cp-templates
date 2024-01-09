// loj-101.rs

use std::collections::VecDeque;

#[derive(Clone, Copy, Debug)]
struct Edge {
    to: usize,
    flow: i64,
    cap: i64,
    rev: usize,
}

struct Net(Vec<Vec<Edge>>, Vec<usize>, Vec<bool>);

impl Net {
    fn new(n: usize) -> Self {
        Self(vec![vec![]; n+1], vec![0; n+1], vec![false; n+1])
    }
    fn add_edge(&mut self, from: usize, to: usize, cap: i64) {
        let to_edge = Edge {to, cap, flow: 0, rev: self.0[to].len()};
        self.0[from].push(to_edge);
        let from_edge = Edge {to: from, flow: 0, cap: 0, rev: self.0[from].len() - 1};
        self.0[to].push(from_edge);
    }
    fn bfs(&mut self, s: usize, t: usize) -> bool {
        self.1.fill(0);
        let mut dq = VecDeque::new();
        self.1[s] = 1;
        dq.push_back((s, 1));
        while let Some((v, l)) = dq.pop_front() {
            for e in &self.0[v] {
                if self.1[e.to] == 0 && e.cap > e.flow {
                    self.1[e.to] = l + 1;
                    dq.push_back((e.to, l + 1));
                }
            }
        }
        self.1[t] != 0
    }
    fn dfs(&mut self, s: usize, t: usize, cap: i64) -> i64 {
        if self.2[s] { return 0; }
        self.2[s] = true;
        if s == t { return cap; }
        let mut res = 0;
        let n = self.0[s].len();
        for i in 0..n {
            let e = self.0[s][i];
            if e.cap > e.flow && self.1[e.to] == self.1[s] + 1 {
                let new = self.dfs(e.to, t, (cap - res).min(e.cap - e.flow));
                self.0[s][i].flow += new;
                self.0[e.to][e.rev].flow -= new;
                res += new;
                if res == cap { return res; }
            }
        }
        res
    }
    fn max_flow(&mut self, s: usize, t: usize) -> i64 {
        let mut res = 0;
        while self.bfs(s, t) {
            self.2.fill(false);
            res += self.dfs(s, t, i64::MAX);
        }
        res
    }
}

fn main() {
    let mut buf = String::new();
    std::io::stdin().read_line(&mut buf).ok();
    let nmst: Vec<usize> = buf.trim().split(' ').map(|x|x.parse::<usize>().unwrap()).collect::<Vec<usize>>();
    let (n, m, s, t) = (nmst[0], nmst[1], nmst[2], nmst[3]);
    let mut net = Net::new(n);
    for _ in 0..m {
        buf.clear();
        std::io::stdin().read_line(&mut buf).ok();
        let uvc: Vec<i64> = buf.trim().split(' ').map(|x|x.parse::<i64>().unwrap()).collect::<Vec<i64>>();
        let (u, v, c) = (uvc[0] as usize, uvc[1] as usize, uvc[2]);
        net.add_edge(u, v, c);
    }
    println!("{}", net.max_flow(s, t));
}
