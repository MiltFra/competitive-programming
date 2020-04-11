use std::io;

fn main() {
    let mut buf = String::new();
    io::stdin()
        .read_line(&mut buf)
        .expect("Failed to read line.");
    let nums: Vec<i32> = buf
        .split_whitespace()
        .map(|num| num.parse().unwrap())
        .collect();
    println!("{}", nums[0] * (nums[1] - 1) + 1);
}
