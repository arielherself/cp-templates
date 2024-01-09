// lc-2707.rs

struct Solution;

use std::collections::HashMap;

struct Trie {
    mark: bool,
    nxt: HashMap<u8, Box<Trie>>,
}

impl Trie {
    fn new() -> Self {
        Self {mark: false, nxt: HashMap::new()}
    }
    fn insert(&mut self, s: Vec<u8>) {
        let mut ptr = self;
        for x in s.into_iter().rev() {
            ptr = ptr.nxt.entry(x).or_insert(Box::new(Trie{mark: false, nxt: HashMap::new()}));
        }
        ptr.mark = true;
    }
    fn query(&self, s: &Vec<u8>) -> Vec<usize> {
        let mut ptr = self;
        let mut res = vec![];
        for (i, &x) in s.iter().rev().enumerate() {
            if ptr.mark {
                res.push(i);
            }
            if let Some(p) = ptr.nxt.get(&x) {
                ptr = p.as_ref();
            } else {
                return res;
            }
        }
        if ptr.mark {
            res.push(s.len());
        }
        res
    }
}

impl Solution {
    pub fn min_extra_char(s: String, dictionary: Vec<String>) -> i32 {
        let s = s.into_bytes();
        let n = s.len();
        let mut trie = Trie::new();
        for word in dictionary {
            trie.insert(word.into_bytes());
        }
        // eprintln!("{:?}", trie.query(&("leetcode".to_string().into_bytes())));
        // eprintln!("{:?}", trie.query(&("code".to_string().into_bytes())));
        let mut dp = vec![0;n+1];
        let mut query_string = vec![];
        for i in 1..=n {
            query_string.push(s[i-1]);
            let matchings = trie.query(&query_string);
            dp[i] = (0..i).fold(usize::MAX, |c, j|c.min(i - j + dp[j]));
            dp[i] = dp[i].min(matchings.into_iter().fold(usize::MAX, |c,j|c.min(dp[i-j])));
        }
        dp[n] as i32
    }
}

fn main() {
    let mut buf = String::new();
    std::io::stdin().read_line(&mut buf).ok();
    let s: String = buf.trim().parse::<String>().unwrap();
    buf.clear();
    std::io::stdin().read_line(&mut buf).ok();
    let dictionary: Vec<String> = buf.trim().split(' ').map(|x|x.parse::<String>().unwrap()).collect::<Vec<String>>();
    println!("{}", Solution::min_extra_char(s, dictionary));
}
