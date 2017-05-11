test_that("gets coordinates", {
  point <- point_type(1, 2, 3)
  expect_equal(geometry$get(point, 0), 1)
  expect_equal(geometry$get(point, 1), 2)
  expect_equal(geometry$get(point, 2), 3)
})

test_that("gets x coordinate", {
  point <- point_type(1, 2, 3)
  expect_equal(geometry$getx(point), 1)
})

test_that("gets y coordinate", {
  point <- point_type(1, 2, 3)
  expect_equal(geometry$gety(point), 2)
})

test_that("gets z coordinate", {
  point <- point_type(1, 2, 3)
  expect_equal(geometry$getz(point), 3)
})

test_that("planar projection", {
  point <- point_type(1, 2, 3)
  p0 <- geometry$planar_projection(point, 0)
  expect_equal(2, geometry$get(p0, 0))
  expect_equal(3, geometry$get(p0, 1))
  p1 <- geometry$planar_projection(point, 1)
  expect_equal(1, geometry$get(p1, 0))
  expect_equal(3, geometry$get(p1, 1))
  p2 <- geometry$planar_projection(point, 2)
  expect_equal(1, geometry$get(p2, 0))
  expect_equal(2, geometry$get(p2, 1))
})

test_that("distance", {
  p <- point_type(1, 0, 0)
  q <- point_type(0, 0, 0)
  r <- point_type(1, 1, 1)
  expect_equal(1, geometry$distance(p, q))
  expect_equal(geometry$distance(q, p), geometry$distance(p, q))
  expect_equal(0, geometry$distance(p, p))
  expect_true(abs(sqrt(3) - geometry$distance(q, r)) < 1e-6)
})

test_that("vector from to", {
  p <- point_type(1, 0, 0)
  q <- point_type(0, 0, 0)
  r <- point_type(1, 1, 1)
  expect_equal(0, geometry$distance(r, geometry$vector_from_to(q, r)))
  expect_equal(0,
               geometry$distance(point_type(0, 1, 1), geometry$vector_from_to(p, r)))
  expect_equal(0, geometry$distance(q, geometry$vector_from_to(p, p)))
})

test_that("traslate", {
  p <- point_type(0, 0, 0)
  t <- point_type(1, 0, 0)
  expect_equal(0, geometry$distance(geometry$traslate(p, t), t))
})

test_that("scale", {
  p <- point_type(1, 0, 0)
  q <- point_type(1, 0, 1)
  r <- point_type(0, 0, 0)
  expect_true(abs(0 - geometry$distance(
    geometry$scale(p, 0.5, r), point_type(0.5, 0, 0)
  )) < 1e-6)
  expect_true(abs(0 - geometry$distance(
    geometry$scale(q, 0.5, r), point_type(0.5, 0, 0.5)
  )) < 1e-6)
})

test_that("scale zero", {
  p <- point_type(1, 0, 0)
  q <- point_type(1, 0, 1)
  r <- point_type(1, 3, 2)
  expect_true(abs(0 - geometry$distance(geometry$scale(p, 0.0, r), r)) < 1e-6)
  expect_true(abs(0 - geometry$distance(geometry$scale(q, 0.0, r), r)) < 1e-6)
})

test_that("scale axis", {
  p <- point_type(1, 1, 1)
  expect_equal(0, geometry$distance(
    geometry$scale(p, 0.3, 0.5, 0.7),
    point_type(0.3, 0.5, 0.7)
  ))
})

test_that("cross product", {
  p <- point_type(1, 0, 0)
  q <- point_type(0, 1, 0)
  expect_equal(0, geometry$distance(geometry$cross_product(p, q), point_type(0, 0, 1)))
})

test_that("cross product zero", {
  p <- point_type(0, 0, 0)
  q <- point_type(1, 1, 1)
  expect_equal(0, geometry$distance(geometry$cross_product(p, q), point_type(0, 0, 0)))
})

test_that("cross product same", {
  p <- point_type(1, 0, 0)
  q <- point_type(1, 0, 0)
  expect_equal(0, geometry$distance(geometry$cross_product(p, q), point_type(0, 0, 0)))
})

test_that("euclidean norm", {
  p <- point_type(0, 0, 0)
  q <- point_type(1, 1, 1)
  expect_equal(0, geometry$norm(p))
  expect_true(abs(sqrt(3) - geometry$norm(q)) < 1e-6)
})

test_that("equality", {
  p <- point_type(0, 0, 0)
  q <- point_type(0, 0, 0)
  expect_true(geometry$equal(p, p))
  expect_true(geometry$equal(p, q))
  
  r <- planar_point(0, 0)
  s <- planar_point(0, 0)
  expect_true(geometry$equal(r, r))
  expect_true(geometry$equal(r, s))
})

test_that("inequality", {
  p <- point_type(0, 0, 0)
  q <- point_type(1, 1, 1)
  r <- point_type(1e-6, 0, 0)
  expect_false(geometry$equal(p, q))
  expect_false(geometry$equal(p, r))
  
  s <- planar_point(0, 0)
  t <- planar_point(1, 1)
  expect_false(geometry$equal(s, t))
})

test_that("segment segment distance parallel", {
  p <- point_type(0, 0, 0)
  q <- point_type(1, 0, 0)
  r <- point_type(0, 1, 0)
  s <- point_type(1, 1, 0)
  expect_equal(1, geometry$segment_segment_distance(p, q, r, s))
})

test_that("segment segment distance crossing", {
  p <- point_type(0, 0, 0)
  q <- point_type(1, 0, 0)
  r <- point_type(0.5, 0.5, 0)
  s <- point_type(0.5, -0.5, 0)
  expect_equal(0, geometry$segment_segment_distance(p, q, r, s))
})

test_that("segment segment distance non parallel", {
  p <- point_type(0, 0, 0)
  q <- point_type(1, 0, 0)
  r <- point_type(1, 10.5, 0)
  s <- point_type(1, 0.5, 0)
  expect_equal(0.5, geometry$segment_segment_distance(p, q, r, s))
})

test_that("segment cross plane reg", {
  s1 <- segment_type(point_type(0, 0, 0), point_type(1, 0, 0))
  s2 <- segment_type(point_type(0, 0, 0), point_type(0, 1, 0))
  s3 <- segment_type(point_type(0, 0, 0), point_type(0, 0, 1))
  p <- point_type(0.5, 0.5, 0.5)
  
  scp1 <- geometry$segment_cross_plane(s1, p, 0)
  expect_true(scp1[[1]])
  expect_equal(0, geometry$distance(scp1[[2]], point_type(0.5, 0, 0)))
  
  scp2 <- geometry$segment_cross_plane(s2, p, 1)
  expect_true(scp2[[1]])
  expect_equal(0, geometry$distance(scp2[[2]], point_type(0, 0.5, 0)))
  
  scp3 <- geometry$segment_cross_plane(s3, p, 2)
  expect_true(scp3[[1]])
  expect_equal(0, geometry$distance(scp3[[2]], point_type(0, 0, 0.5)))
})

test_that("segment cross plane limit", {
  s1 <- segment_type(point_type(0, 0, 0), point_type(1, 0, 0))
  s2 <- segment_type(point_type(0, 0, 0), point_type(0, 1, 0))
  s3 <- segment_type(point_type(0, 0, 0), point_type(0, 0, 1))
  p <- point_type(1,1,1)
  
  scp1 <- geometry$segment_cross_plane(s1, p, 0)
  expect_true(scp1[[1]])
  expect_equal(0, geometry$distance(scp1[[2]], point_type(1, 0, 0)))
  
  scp2 <- geometry$segment_cross_plane(s2, p, 1)
  expect_true(scp2[[1]])
  expect_equal(0, geometry$distance(scp2[[2]], point_type(0, 1, 0)))
  
  scp3 <- geometry$segment_cross_plane(s3, p, 2)
  expect_true(scp3[[1]])
  expect_equal(0, geometry$distance(scp3[[2]], point_type(0, 0, 1)))
})

test_that("segment cross plane no", {
  s1 <- segment_type(point_type(0, 0, 0), point_type(1, 0, 0))
  s2 <- segment_type(point_type(0, 0, 0), point_type(0, 1, 0))
  s3 <- segment_type(point_type(0, 0, 0), point_type(0, 0, 1))
  p <- point_type(2,2,2)
  
  scp1 <- geometry$segment_cross_plane(s1, p, 0)
  expect_false(scp1[[1]])
  scp2 <- geometry$segment_cross_plane(s2, p, 1)
  expect_false(scp2[[1]])
  scp3 <- geometry$segment_cross_plane(s3, p, 2)
  expect_false(scp3[[1]])
})

test_that("intersecting boxes intersects", {
  box1 <- box_type(point_type(0, 0, 0), point_type(1, 1, 1))
  box2 <- box_type(point_type(0.5, 0.5, 0.5), point_type(1.5, 1.5, 1.5))
  expect_true(geometry$box_box_intersection(box1, box2))
})

test_that("same boxes intersects", {
  box <- box_type(point_type(0, 0, 0), point_type(1, 1, 1))
  expect_true(geometry$box_box_intersection(box, box))
})

test_that("face limit boxes intersects", {
  box1 <- box_type(point_type(0, 0, 0), point_type(1, 1, 1))
  box2 <- box_type(point_type(1, 0, 0), point_type(1.5, 1.5, 1.5))
  expect_true(geometry$box_box_intersection(box1, box2))
})

test_that("corner limit boxes intersects", {
  box1 <- box_type(point_type(0, 0, 0), point_type(1, 1, 1))
  box2 <- box_type(point_type(1, 1, 1), point_type(1.5, 1.5, 1.5))
  expect_true(geometry$box_box_intersection(box1, box2))
})

test_that("non intersecting boxes not intersects", {
  box1 <- box_type(point_type(0, 0, 0), point_type(1, 1, 1))
  box2 <- box_type(point_type(1.1, 1.1, 1.1), point_type(1.5, 1.5, 1.5))
  expect_false(geometry$box_box_intersection(box1, box2))
})