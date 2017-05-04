#include <RcppCommon.h>

// [[Rcpp::plugins("cpp14")]]

#include <neurostr/core/geometry.h>

namespace Rcpp {
template <> neurostr::geometry::point_type as(SEXP point);
template <> SEXP wrap(const neurostr::geometry::point_type &p);

template <> neurostr::geometry::box_type as(SEXP box);
template <> SEXP wrap(const neurostr::geometry::box_type &b);
}

#include <Rcpp.h>

namespace Rcpp {

// POINT_TYPE
template <> neurostr::geometry::point_type as(SEXP point){
  Rcpp::NumericVector nv(point);
  return neurostr::geometry::point_type(nv[0], nv[1], nv[2]);
}

template <> SEXP wrap(const neurostr::geometry::point_type &p){
  float x = neurostr::geometry::getx(p);
  float y = neurostr::geometry::gety(p);
  float z = neurostr::geometry::getz(p);
  return Rcpp::wrap(Rcpp::NumericVector::create(x,y,z));
}

// BOX_TYPE
template <> neurostr::geometry::box_type as(SEXP box){
  Rcpp::NumericMatrix nm(box);
  neurostr::geometry::point_type p = Rcpp::as<neurostr::geometry::point_type>(Rcpp::wrap(nm(0,_)));
  neurostr::geometry::point_type q = Rcpp::as<neurostr::geometry::point_type>(Rcpp::wrap(nm(1,_)));
  return neurostr::geometry::box_type(p,q);
}

template <> SEXP wrap(const neurostr::geometry::box_type &b){
  neurostr::geometry::point_type min_corner = b.min_corner();
  neurostr::geometry::point_type max_corner = b.max_corner();
  Rcpp::NumericVector nv_min(Rcpp::wrap(min_corner));
  Rcpp::NumericVector nv_max(Rcpp::wrap(max_corner));
  Rcpp::NumericMatrix nm(2,3);
  nm(0,_) = nv_min;
  nm(1,_) = nv_max;
  return Rcpp::wrap(nm);
}

}
  
using namespace Rcpp;

RCPP_MODULE(core_geometry){
  
  function( "get", &neurostr::geometry::get);
  function( "getx", &neurostr::geometry::getx);
  function( "gety", &neurostr::geometry::gety);
  function( "getz", &neurostr::geometry::getz);
  function( "box_box_intersection", &neurostr::geometry::box_box_intersection);
  
}

