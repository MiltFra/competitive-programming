use std::io;

fn main() {
    let stdin = io::stdin();
    let mut count: i64;
    let mut set_counter: i64 = 0;
    loop {
        let mut buf = String::new();
        stdin
            .read_line(&mut buf)
            .expect("Failed to read name count for set.");
        count = buf.trim().parse().unwrap();
        if count == 0 {
            break;
        }
        set_counter += 1;
        let mut names: Vec<String> = Vec::new();
        for _ in 0..count {
            buf.clear();
            stdin.read_line(&mut buf).expect("Failed to read name.");
            names.push(buf.trim().to_string());
        }
        println!("SET {}", set_counter);
        eprintln!("{:?}, {:?}", count, names);
        let mut i: i64 = 0;
        while i < count {
            println!("{}", names[i as usize]);
            i += 2;
        }
        i -= 1 + 2 * (count % 2);
        while i > 0 {
            println! {"{}", names[i as usize]};
            i -= 2;
        }
    }
}
