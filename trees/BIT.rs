struct BIT(usize, Vec<i64>);

impl BIT {
    fn new(n: usize) -> Self {
        Self(n, vec![0;n+1])
    }
    fn query(&self, mut i: usize) -> i64 {
        let lowbit = |x: i64|x&-x;
        let mut res = 0;
        while i > 0 {
            res += self.1[i];
            i -= lowbit(i as i64) as usize;
        }
        res
    }
    fn insert(&mut self, mut i: usize) {
        let lowbit = |x: i64| x & -x;
        while i <= self.0 {
            self.1[i] += 1;
            i += lowbit(i as i64) as usize;
        }
    }
}
