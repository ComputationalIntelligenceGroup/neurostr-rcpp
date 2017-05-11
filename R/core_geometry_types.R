point_type <- function(x, y, z) {
  value <- c(x, y, z)
  class(value) <- "point_type"
  value
}

box_type <- function(p, q) {
  value <- matrix(c(p, q), 2, 3, TRUE)
  class(value) <- "box_type"
  value
}

segment_type <- function(p, q) {
  value <- matrix(c(p, q), 2, 3, TRUE)
  class(value) <- "segment_type"
  value
}

triangle_type <- function(p, q, r) {
  value <- matrix(c(p, q, r), 3, 3, TRUE)
  class(value) <- "triangle_type"
  value
}

planar_point <- function(x, y) {
  value <- c(x, y)
  class(value) <- "planar_point"
  value
}