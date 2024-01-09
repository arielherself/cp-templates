// loj-101.rs

use std::collections::VecDeque;

#[derive(Clone, Debug)]
struct Edge {
    to: usize,
    cap: i64,
    flow: i64,
    rev: (usize, usize)
}

struct Net(Vec<Vec<Edge>>);

impl Net {
    fn new(n: usize) -> Self {
        Self(vec![vec![];n+1])
    }
    fn add_edge(&mut self, from: usize, to: usize, cap: i64) {
        let to_edge = Edge {to, cap, flow: 0, rev: (to, self.0[to].len())};
        self.0[from].push(to_edge);
        let from_edge = Edge {to: from, cap: 0, flow: 0, rev: (from, self.0[from].len() - 1)};
        self.0[to].push(from_edge);
    }
    fn max_flow(&mut self, s: usize, t: usize) -> i64 {
        let n = self.0.len();
        let mut pa = vec![(0, 0);n+1];
        let mut res = 0;
        loop {
            let mut pf = vec![0;n+1];
            let mut dq = VecDeque::new();
            dq.push_back(s);
            pf[s] = i64::MAX;
            while let Some(v) = dq.pop_front() {
                for (i, ne) in self.0[v].iter().enumerate() {
                    if pf[ne.to] == 0 && ne.cap > ne.flow {
                        pf[ne.to] = pf[v].min(ne.cap - ne.flow);
                        pa[ne.to] = (v, i);
                        dq.push_back(ne.to);
                    }
                }
                if pf[t] != 0 {
                    break;
                }
            }
            if pf[t] == 0 {
                break;
            }
            let mut p = t;
            while pa[p].0 != 0 {
                let (x, y) = pa[p];
                self.0[x][y].flow += pf[t];
                let (z, w) = self.0[x][y].rev;
                self.0[z][w].flow -= pf[t];
                p = x;
            }
            res += pf[t];
        }
        res
    }
}

fn main() {
    let mut buf = String::new();
    std::io::stdin().read_line(&mut buf).ok();
    let tmp: Vec<usize> = buf.trim().split(' ').map(|x|x.parse::<usize>().unwrap()).collect::<Vec<usize>>();
    let (n, m, s, t) = (tmp[0], tmp[1], tmp[2], tmp[3]);
    let mut net = Net::new(n);
    for _ in 0..m {
        buf.clear();
        std::io::stdin().read_line(&mut buf).ok();
        let tmp: Vec<i64> = buf.trim().split(' ').map(|x|x.parse::<i64>().unwrap()).collect::<Vec<i64>>();
        net.add_edge(tmp[0] as usize, tmp[1] as usize, tmp[2]);
    }
    println!("{}", net.max_flow(s, t));
}
