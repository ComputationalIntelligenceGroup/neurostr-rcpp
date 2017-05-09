test_that("gets coordinates", {
  point <- c(1,2,3)
  expect_equal(geometry$get(point,0),1)
  expect_equal(geometry$get(point,1),2)
  expect_equal(geometry$get(point,2),3)
})

test_that("gets x coordinate", {
  point <- c(1,2,3)
  expect_equal(geometry$getx(point),1)
})

test_that("gets y coordinate", {
  point <- c(1,2,3)
  expect_equal(geometry$gety(point),2)
})

test_that("gets z coordinate", {
  point <- c(1,2,3)
  expect_equal(geometry$getz(point),3)
})

test_that("planar projection", {
  point <- c(1,2,3)
  p0 <- geometry$planar_projection(point,0)
  expect_equal(2,geometry$get(p0,0))
  expect_equal(3,geometry$get(p0,1))
  p1 <- geometry$planar_projection(point,1)
  expect_equal(1,geometry$get(p1,0))
  expect_equal(3,geometry$get(p1,1))
  p2 <- geometry$planar_projection(point,2)
  expect_equal(1,geometry$get(p2,0))
  expect_equal(2,geometry$get(p2,1))
})

test_that("distance", {
  p <- c(1,0,0)
  q <- c(0,0,0)
  r <- c(1,1,1)
  
  expect_equal(1,geometry$distance(p,q))
  expect_equal(geometry$distance(q,p),geometry$distance(p,q))
  expect_equal(0,geometry$distance(p,p))
  expect_true(abs(sqrt(3) - geometry$distance(q,r)) < 1e-6)
})

test_that("vector from to", {
  p <- c(1,0,0)
  q <- c(0,0,0)
  r <- c(1,1,1)
  
  expect_equal(0,geometry$distance(r,geometry$vector_from_to(q,r)))
  expect_equal(0,geometry$distance(c(0,1,1),geometry$vector_from_to(p,r)))
  expect_equal(0,geometry$distance(q,geometry$vector_from_to(p,p)))
})

test_that("traslate", {
  p <- c(0,0,0)
  t <- c(1,0,0)
  
  expect_equal(0,geometry$distance(geometry$traslate(p,t),t))
})

test_that("scale", {
  p <- c(1,0,0)
  q <- c(1,0,1)
  r <- c(0,0,0)
  expect_true(abs(0 - geometry$distance(geometry$scale(p,0.5,r),c(0.5,0,0))) < 1e-6)
  expect_true(abs(0 - geometry$distance(geometry$scale(q,0.5,r),c(0.5,0,0.5))) < 1e-6)
})

test_that("scale zero", {
  p <- c(1,0,0)
  q <- c(1,0,1)
  r <- c(1,3,2)
  expect_true(abs(0 - geometry$distance(geometry$scale(p,0.0,r),r)) < 1e-6)
  expect_true(abs(0 - geometry$distance(geometry$scale(q,0.0,r),r)) < 1e-6)
})

test_that("scale axis", {
  p <- c(1,1,1)
  #expect_true(abs(0 - geometry$distance(geometry$scale(p,0.3,0.5,0.7),c(0.3,0.5,0.7))) < 1e-6)
  expect_equal(0,geometry$distance(geometry$scale(p,0.3,0.5,0.7),c(0.3,0.5,0.7)))
})

test_that("cross product", {
  p <- c(1,0,0)
  q <- c(0,1,0)
  expect_equal(0,geometry$distance(geometry$cross_product(p,q),c(0,0,1)))
})

test_that("cross product zero", {
  p <- c(0,0,0)
  q <- c(1,1,1)
  expect_equal(0,geometry$distance(geometry$cross_product(p,q),c(0,0,0)))
})

test_that("cross product same", {
  p <- c(1,0,0)
  q <- c(1,0,0)
  expect_equal(0,geometry$distance(geometry$cross_product(p,q),c(0,0,0)))
})

test_that("euclidean norm", {
  p <- c(0,0,0)
  q <- c(1,1,1)
  expect_equal(0,geometry$norm(p))
  expect_true(abs(sqrt(3) - geometry$norm(q)) < 1e-6)
})

test_that("equality", {
  p <- c(0,0,0)
  q <- c(0,0,0)
  expect_true(geometry$equal(p,p))
  expect_true(geometry$equal(p,q))
  
  r <- c(0,0)
  s <- c(0,0)
  expect_true(geometry$equal(r,r))
  expect_true(geometry$equal(r,s))
})

test_that("inequality", {
  p <- c(0,0,0)
  q <- c(1,1,1)
  r <- c(1e-6,0,0)
  expect_false(geometry$equal(p,q))
  expect_false(geometry$equal(p,r))
  
  s <- c(0,0)
  t <- c(1,1)
  expect_false(geometry$equal(s,t))
})

test_that("intersecting boxes intersects", {
  box1 <- matrix(c(0,0,0,1,1,1),2,3, TRUE)
  box2 <- matrix(c(0.5,0.5,0.5,1.5,1.5,1.5),2,3, TRUE)
  expect_true(geometry$box_box_intersection(box1,box2))
})

test_that("same boxes intersects", {
  box <- matrix(c(0,0,0,1,1,1),2,3, TRUE)
  expect_true(geometry$box_box_intersection(box,box))
})

test_that("face limit boxes intersects", {
  box1 <- matrix(c(0,0,0,1,1,1),2,3, TRUE)
  box2 <- matrix(c(1,0,0,1.5,1.5,1.5),2,3, TRUE)
  expect_true(geometry$box_box_intersection(box1,box2))
})

test_that("corner limit boxes intersects", {
  box1 <- matrix(c(0,0,0,1,1,1),2,3, TRUE)
  box2 <- matrix(c(1,1,1,1.5,1.5,1.5),2,3, TRUE)
  expect_true(geometry$box_box_intersection(box1,box2))
})

test_that("non intersecting boxes not intersects", {
  box1 <- matrix(c(0,0,0,1,1,1),2,3, TRUE)
  box2 <- matrix(c(1.1,1.1,1.1,1.5,1.5,1.5),2,3, TRUE)
  expect_false(geometry$box_box_intersection(box1,box2))
})