use std::io;

fn main() {
    loop {
        let mut items: Vec<i32> = Vec::new();
        let c = get_items(&mut items);
        if c == 0 {
            break;
        }
        let max: i32 = items.iter().cloned().fold(0, i32::max);
        eprintln!("E: Max Val={}", max);
        let mut occs: Vec<u32> = vec![0; max as usize + 1];
        eprintln!("E: Occs={:?}", occs);
        count_into(items, &mut occs);
        let max_index = get_max_index(&occs);
        let mut output: Vec<Vec<u32>> = Vec::new();
        let total_rows = occs[max_index];
        println!("{}", total_rows);
        for _ in 0..total_rows {
            output.push(Vec::new());
        }
        let mut r: u32 = 0;
        let mut item_index: u32 = 1;
        for _ in 0..c {
            while occs[item_index as usize] == 0 {
                item_index += 1;
            }
            output[r as usize].push(item_index);
            occs[item_index as usize] -= 1;
            r = (r + 1) % total_rows;
        }
        print_output(output);
    }
}

fn print_output(output: Vec<Vec<u32>>) {
    eprintln!("E: Printing output={:?}", output);
    for v in output {
        print!("{}", v[0]);
        for i in 1..v.len() {
            print!(" {}", v[i]);
        }
        print!("\n");
    }
}

fn count_into(items: Vec<i32>, occs: &mut Vec<u32>) {
    for x in items {
        occs[x as usize] += 1;
    }
}

fn get_max_index(occs: &Vec<u32>) -> usize {
    let mut max_index: usize = 0;
    for i in 1..occs.len() as usize {
        if occs[i] > occs[max_index] {
            max_index = i;
        }
    }
    max_index
}

fn get_items(items: &mut Vec<i32>) -> u32 {
    let mut buf = String::new();
    let stdin = io::stdin();
    stdin
        .read_line(&mut buf)
        .expect("Failed to read item count.");
    let count: u32 = buf.trim().to_string().parse().unwrap();
    if count == 0 {
        return count;
    }
    while count as usize > items.len() {
        buf.clear();
        stdin
            .read_line(&mut buf)
            .expect("Failed to read item list.");
        let mut line_items: Vec<i32> = buf
            .split_whitespace()
            .map(|num| num.parse().unwrap())
            .collect();
        items.append(&mut line_items);
    }
    count
}
