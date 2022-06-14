open Bigarray

type paths_instance = {
  n : int;
  m : int;
  k : int;
  colours : (int, int8_unsigned_elt, c_layout) Array1.t;
  edges : (int, int8_unsigned_elt, c_layout) Array2.t;
}

let get_parameters = Scanf.scanf "%i %i %i\n" (fun x y z -> (x, y, z))

let get_colours n m k =
  let colours = Array1.create int8_unsigned c_layout (n + 1) in
  for i = 1 to n do
    Scanf.scanf "%i " (fun x -> Array1.set colours i x)
  done;
  colours

let get_edges n m k =
  let edges = Array2.create int8_unsigned c_layout (n + 1) (n + 1) in
  for i = 1 to n do
    Array2.set edges i 0 0
  done;
  for _ = 1 to m do
    let x, y = Scanf.scanf "%i %i\n" (fun x y -> (x, y)) in
    let num_neighbours_x = 1 + Array2.get edges x 0 in
    let num_neighbours_y = 1 + Array2.get edges y 0 in
    Array2.set edges x 0 num_neighbours_x;
    Array2.set edges y 0 num_neighbours_y;
    Array2.set edges x num_neighbours_x y;
    Array2.set edges y num_neighbours_y x
  done;
  edges

let get_instance =
  let n, m, k = get_parameters in
  let colours = get_colours n m k in
  let edges = get_edges n m k in
  { n; m; k; colours; edges }

type dfs_instance = { visited : int list; colours : bool array }

let print_list l =
  Printf.eprintf "[ ";
  List.iter (Printf.eprintf "%i ") l;
  Printf.eprintf "]\n"

let print_array a =
  Printf.eprintf "[| ";
  Array.iter (Printf.eprintf "%b ") a;
  Printf.eprintf "|]\n"

let dfs_next paths current =
  let successors = ref [] in
  let v = List.hd current.visited in
  let n = Array2.get paths.edges v 0 in
  for i = 1 to n do
    let u = Array2.get paths.edges v i in
    let c = Array1.get paths.colours u in
    match List.find_opt (( = ) u) current.visited with
    | Option.Some x -> ()
    | Option.None ->
        if current.colours.(c) then ()
        else
          let visited = u :: current.visited in
          let colours = Array.copy current.colours in
          colours.(c) <- true;
          successors := { visited; colours } :: !successors
  done;
  !successors

let rec num_paths_from_instance paths current =
  let next_instances = dfs_next paths current in
  let num_longer_paths =
    List.fold_left ( + ) 0
      (List.map (num_paths_from_instance paths) next_instances)
  in
  List.length next_instances + num_longer_paths

let num_paths_starting_at paths v =
  let colours = Array.make (paths.k + 1) false in
  colours.(Array1.get paths.colours v) <- true;
  let current = { visited = [ v ]; colours } in
  num_paths_from_instance paths current

let vertices paths =
  let rec remaining_vertices v =
    if v <= paths.n then v :: remaining_vertices (v + 1) else []
  in
  remaining_vertices 1

let () =
  let paths = get_instance in
  let num_paths_per_vertex =
    List.map (num_paths_starting_at paths) (vertices paths)
  in
  let num_paths = List.fold_left ( + ) 0 num_paths_per_vertex in
  Printf.printf "%i\n" num_paths
