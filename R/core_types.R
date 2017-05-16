Node <- function(id = -1, x = 0, y = 0, z = 0, r = 0){
  node <- core$Node
  value <- new(node, id, x, y, z, r)
  value
}