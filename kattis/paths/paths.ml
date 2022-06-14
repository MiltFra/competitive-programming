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
  let colours = Array1.create int8_unsigned c_layout n in
  for i = 0 to n-1 do
    Scanf.scanf "%i " (fun x -> Array1.set colours i x)
  done;
  colours

let get_edges n m k = 
  let edges = Array2.create int8_unsigned c_layout (n + 1) (n+1) in
  for _ = 1 to n do
    let (x,y) = Scanf.scanf "%i %i\n" (fun x y -> (x,y)) in
    let num_neighbours_x = Array2.get edges x 0 in
    let num_neighbours_y = Array2.get edges y 0 in
    Array2.set edges x 0 (num_neighbours_x + 1);
    Array2.set edges y 0 (num_neighbours_y + 1);
    Array2.set edges x num_neighbours_x y;
    Array2.set edges y num_neighbours_y x
  done;
  edges

let get_instance = 
  let (n, m, k) =  get_parameters in
  let colours = get_colours n m k in
  let edges = get_edges n m k in
  { n; m; k; colours; edges }

type dfs_instance = {
  visited : int list;
  colours : bool array;
}

let dfs_next paths current =
  let successors = ref [] in
  let v = List.hd current.visited in
  let num_neighbours = Array2.get paths.edges v 0 in
  for i = 1 to num_neighbours do
    let u = Array2.get paths.edges v i in
    let colour = Array1.get paths.colours u in
    if List.find_opt ((=) u) current.visited = Option.Some _ then () (** already visited *)
    else if current.colours.(colour) then () (** colour has already been taken *)
    else 
      let visited = u :: current.visited in
      let colours = Array.copy current.colours in
      colours.(colour) <- true;
      successors := {visited; colours} :: !successors
  done;
  successors

let num_paths_from_instance dfs =
  ()

let num_paths_starting_at paths v = ()

let () = 
  let paths = get_instance in
  ()
