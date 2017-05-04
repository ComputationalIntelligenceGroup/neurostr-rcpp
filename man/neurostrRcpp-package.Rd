\name{neurostrRcpp-package}
\alias{neurostrRcpp-package}
\alias{neurostrRcpp}
\docType{package}
\title{
  NeuroSTR-Rcpp
}
\description{
  A set of R wrappers for using NeuroSTR C++ library.
}
\details{
  Currently it only supports a few interfaces of core/geometry.h
}
\author{
Mario Juez <mjuez@fi.upm.es>

Maintainer: Mario Juez <mjuez@fi.upm.es>
}
\references{
  This optional section can contain literature or other references for
  background information.
}
\keyword{ neurostr, rcpp }
\examples{
> library(neurostrRcpp)
> p <- c(1,2,3);
> xCoord <- geometry$getx(p);
> xCoord
[1] 1
}
