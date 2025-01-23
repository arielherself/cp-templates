#[allow(unused_imports)]
use std::io::Write;

const BUFFER_SIZE: usize = 4096;
pub struct InputCast {
    reader: std::io::BufReader<std::io::Stdin>,
    buffer: [u8; BUFFER_SIZE],
    len: usize,
    head: usize,
}

impl InputCast {
    pub fn new() -> Self {
        Self {
            reader: std::io::BufReader::new(std::io::stdin()),
            buffer: [0u8; BUFFER_SIZE],
            len: 0,
            head: 0,
        }
    }
    pub fn fetch(&mut self) -> Result<(), std::io::Error> {
        self.head = 0;
        self.len = std::io::Read::read(&mut self.reader, &mut self.buffer)?;
        Ok(())
    }
    pub fn common_read(&mut self) -> Vec<u8> {
        let mut res = vec![];
        while self.head < self.len && self.buffer[self.head] < 33 {
            self.head += 1;
        }
        loop {
            if self.head == self.len {
                self.fetch().unwrap();
            }
            let idx = self.buffer[self.head..self.len].iter().position(|&x| x < 33);
            if let Some(loc) = idx {
                res.extend_from_slice(&self.buffer[self.head..self.head + loc]);
                self.head += loc;
                break;
            } else {
                res.extend_from_slice(&self.buffer[self.head..self.len]);
                self.head = self.len;
            }
        }
        res
    }
    pub fn read<U: std::str::FromStr>(&mut self) -> U  where <U as std::str::FromStr>::Err: std::fmt::Debug {
        unsafe {
            String::from_utf8_unchecked(self.common_read()).parse().unwrap()
        }
    }
    pub fn read_vec<U: std::str::FromStr>(&mut self, n: usize) -> Vec<U> where <U as std::str::FromStr>::Err: std::fmt::Debug {
        let mut res = Vec::<U>::with_capacity(n);
        for _ in 0..n {
            res.push(self.read());
        }
        res
    }
}

pub struct Writer {
    buf: String,
}

impl Writer {
    pub fn new() -> Self {
        Self {
            buf: String::new(),
        }
    }
}

impl std::io::Write for Writer {
    fn write(&mut self, buf: &[u8]) -> Result<usize, std::io::Error> {
        let buf = unsafe { std::str::from_utf8_unchecked(buf) };
        if self.buf.len() + buf.len() > BUFFER_SIZE {
            self.flush()?;
            print!("{buf}");
        } else {
            self.buf.push_str(buf);
        }
        Ok(buf.len())
    }
    fn flush(&mut self) -> Result<(), std::io::Error> {
        print!("{}", self.buf);
        self.buf.clear();
        Ok(())
    }
}

#[allow(unused)]
fn main() {
    let mut input = InputCast::new();
    let mut output = Writer::new();

    // let n = input.read::<usize>();
    // for _ in 0..n - 1 {
    //     let curr = (input.read::<i32>(), input.read::<i32>());
    //     write!(output, "{:?}\n", curr);
    // }
}
