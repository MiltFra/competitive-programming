use std::io;

fn main() {
    let mut buf = String::new();
    let stdin = io::stdin();
    stdin
        .read_line(&mut buf)
        .expect("Failed to read first line.");
    let nums: Vec<u32> = buf
        .split_whitespace()
        .map(|num| num.parse().unwrap())
        .collect();
    for _ in 0..nums[0] {
        buf.clear();
        stdin
            .read_line(&mut buf)
            .expect("Failed to read matrix row.");
        for _ in 0..nums[2] {
            for x in buf.trim().chars() {
                for _ in 0..nums[3] {
                    print!("{}", x);
                }
            }
            println!("");
        }
    }
}
