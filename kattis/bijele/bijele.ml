let () =
  let k, q, r, b, n, p =
    Scanf.scanf "%i %i %i %i %i %i" (fun a b c d e f -> (a, b, c, d, e, f))
  in
  Printf.printf "%i %i %i %i %i %i\n" (1 - k) (1 - q) (2 - r) (2 - b) (2 - n)
    (8 - p)
