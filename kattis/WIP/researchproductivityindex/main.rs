use std::convert::TryInto;
use std::io;

fn main() {
    let mut buf = String::new();
    let stdin = io::stdin();
    stdin
        .read_line(&mut buf)
        .expect("Failed to read first line.");
    buf.clear();
    stdin
        .read_line(&mut buf)
        .expect("Failed to read paper list.");
    let mut papers: Vec<u8> = buf.split_whitespace().map(|x| x.parse().unwrap()).collect();
    println!("{}", max_expected_rpi(&mut papers));
}

fn max_expected_rpi(papers: &mut Vec<u8>) -> f64 {
    papers.sort_unstable();
    papers.reverse();
    eprintln!("D: {:?}", papers);
    let mut max_rpi: f64 = 0.0;
    for s in 1..papers.len() + 1 {
        let rpi: f64 = expected_rpi(papers, s);
        eprintln!("D: expected_rpi={} for s={}", rpi, s);
        if rpi <= max_rpi {
            eprintln!("D: Breaking due to {} <= {}", rpi, max_rpi);
            break;
        }
        max_rpi = rpi;
    }
    return max_rpi;
}

fn expected_rpi(papers: &Vec<u8>, n: usize) -> f64 {
    eprintln!("D: Getting expected_rpi for s={}", n);
    let mut weighted_rpi: f64 = 0.0;
    for k in 1..n + 1 {
        let p: f64 = prob_k(papers, n, k);
        let rpik = rpi(k.try_into().unwrap(), n.try_into().unwrap());
        eprintln!("D: | p={} and rpi={} for k={}", p, rpik, k);
        weighted_rpi += p * rpik;
    }
    return weighted_rpi;
}

fn prob_k(papers: &Vec<u8>, n: usize, k: usize) -> f64 {
    return prob_ki(papers, n, k, 0);
}

fn prob_ki(papers: &Vec<u8>, n: usize, k: usize, i: usize) -> f64 {
    let mut p: f64 = 1.0;
    // It's impossible to achieve this.
    if k > n - i {
        return 0.0;
    }
    // None can be true.
    if k == 0 {
        for j in i..n {
            p *= 1.0 - papers[j] as f64 / 100.0;
        }
        return p;
    }
    // All have to be true.
    if k == n - i {
        for j in i..n {
            p *= papers[j] as f64 / 100.0;
        }
        return p;
    }
    let p1: f64 = papers[i] as f64 / 100.0;
    let p0: f64 = 1.0 - p1;
    return p0 * prob_ki(papers, n, k, i + 1) + p1 * prob_ki(papers, n, k - 1, i + 1);
}

fn rpi(a: u32, s: u32) -> f64 {
    if a == 0 {
        return 0.0;
    }
    let a = f64::from(a);
    let s = f64::from(s);
    return a.powf(a / s);
}
