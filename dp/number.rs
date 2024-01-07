struct Sol {
    dp:  Vec<usize>,
    pow: Vec<usize>,
}

impl Sol {
    fn solve(&self, mut x: usize) -> Vec<usize> {
        let mut cnt = x;
        let mut digit = vec![];
        let mut res = vec![0;10];
        let mut len = 0;
        digit.push(0);
        while x != 0 {
            len += 1;
            digit.push(x as usize % 10);
            x /= 10;
        }
        for i in (1..=len).rev() {
            cnt -= digit[i] * self.pow[i-1];
            res[digit[i]] += cnt + 1;
            for b in 0..10 {
                res[b] += self.dp[i-1] * digit[i];
            }
            for j in 0..digit[i] {
                res[j] += self.pow[i-1];
            }
            res[0] -= self.pow[i-1];
        }
        res
    }
}


fn main() {
    let mut buf = String::new();
    std::io::stdin().read_line(&mut buf).ok();
    let ab: Vec<usize> = buf.trim().split(' ').map(|x|x.parse::<usize>().unwrap()).collect::<Vec<usize>>();
    let a = ab[0];
    let b = ab[1];
    let mut dp = vec![0;13];
    let mut pow = vec![1;13];
    for i in 1..13 {
        pow[i] = pow[i-1] * 10;
        dp[i] = dp[i-1] * 10 + pow[i-1];
    }
    let sol = Sol { dp, pow };
    let res_a_1 = sol.solve(a - 1);
    let res_b   = sol.solve(b);
    for i in 0..10 {
        print!("{} ", res_b[i] - res_a_1[i]);
    }
}
