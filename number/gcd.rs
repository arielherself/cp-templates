let gcd = |mut x: i64, mut y: i64|{
    while y != 0 {
        (x, y) = (y, x % y);
    }
    x
};