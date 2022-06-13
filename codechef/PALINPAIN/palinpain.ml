open Option
open String

let rec a_first x y =
  match (x, y) with
  | 0, _ -> Option.some (String.make y 'b')
  | 1, _ ->
      if y mod 2 = 1 then Option.none
      else
        let b_string = String.make (y / 2) 'a' in
        Option.some (b_string ^ "a" ^ b_string)
  | _, _ -> (
      match a_first (x - 2) y with
      | Some x -> Option.some ("a" ^ x ^ "a")
      | None -> None)

let b_first x y =
  if y = 0 then a_first x y
  else if y = 1 then Option.none
  else
    match a_first x (y - 2) with
    | Some x -> Option.some ("b" ^ x ^ "b")
    | None -> None

let () =
  let n = Scanf.scanf "%i\n" (fun a -> a) in
  for _ = 1 to n do
    let x, y = Scanf.scanf "%i %i\n" (fun a b -> (a, b)) in
    let first = a_first x y in
    let second = b_first x y in
    match (first, second) with
    | None, _ -> Printf.printf "-1\n"
    | _, None -> Printf.printf "-1\n"
    | Some s, Some t ->
        if String.compare s t = 0 then Printf.printf "-1"
        else Printf.printf "%s\n%s\n" s t
  done
