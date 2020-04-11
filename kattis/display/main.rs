use std::io;

fn main() {
    let digit_lines: Vec<Vec<&str>> = vec![
        vec![
            "+---+", "    +", "+---+", "+---+", "+   +", "+---+", "+---+", "+---+", "+---+",
            "+---+", " ",
        ],
        vec![
            "|   |", "    |", "    |", "    |", "|   |", "|    ", "|    ", "    |", "|   |",
            "|   |", " ",
        ],
        vec![
            "|   |", "    |", "    |", "    |", "|   |", "|    ", "|    ", "    |", "|   |",
            "|   |", "o",
        ],
        vec![
            "+   +", "    +", "+---+", "+---+", "+---+", "+---+", "+---+", "    +", "+---+",
            "+---+", " ",
        ],
        vec![
            "|   |", "    |", "|    ", "    |", "    |", "    |", "|   |", "    |", "|   |",
            "    |", "o",
        ],
        vec![
            "|   |", "    |", "|    ", "    |", "    |", "    |", "|   |", "    |", "|   |",
            "    |", " ",
        ],
        vec![
            "+---+", "    +", "+---+", "+---+", "    +", "+---+", "+---+", "    +", "+---+",
            "+---+", " ",
        ],
    ];
    let mut buf: String = String::new();
    let stdin = io::stdin();
    stdin.read_line(&mut buf).unwrap();
    loop {
        let mut br: bool = false;
        let mut out_vec: Vec<u32> = Vec::new();
        for c in buf.clone().trim().chars() {
            if c.is_numeric() {
                out_vec.push(c.to_digit(10).unwrap());
            } else if c == ':' {
                out_vec.push(10);
            } else {
                br = true;
                println!("end");
                break;
            }
        }
        if br {
            break;
        }
        for i in 0..7 {
            print!("{}", digit_lines[i][out_vec[0] as usize]);
            for j in 1..out_vec.len() {
                print!("  {}", digit_lines[i][out_vec[j] as usize]);
            }
            print!("\n");
        }
        print!("\n\n");
        buf.clear();
        stdin.read_line(&mut buf).unwrap();
    }
}
