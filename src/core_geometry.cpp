#include <RcppCommon.h>

// [[Rcpp::plugins("cpp14")]]

#include <neurostr/core/geometry.h>

namespace Rcpp {

// point_type wrapping
template <> neurostr::geometry::point_type as(SEXP point);
template <> SEXP wrap(const neurostr::geometry::point_type &p);

// box_type wrapping
template <> neurostr::geometry::box_type as(SEXP box);
template <> SEXP wrap(const neurostr::geometry::box_type &b);

// segment_type wrapping
template <> neurostr::geometry::segment_type as(SEXP segment);
template <> SEXP wrap(const neurostr::geometry::segment_type &s);

// triangle_type wrapping
template <> neurostr::geometry::triangle_type as(SEXP triangle);
template <> SEXP wrap(const neurostr::geometry::triangle_type &t);

}

#include <Rcpp.h>

namespace Rcpp {

// point_type
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

// box_type
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

// segment_type
template <> neurostr::geometry::segment_type as(SEXP segment){
  Rcpp::NumericMatrix nm(segment);
  neurostr::geometry::point_type p = Rcpp::as<neurostr::geometry::point_type>(Rcpp::wrap(nm(0,_)));
  neurostr::geometry::point_type q = Rcpp::as<neurostr::geometry::point_type>(Rcpp::wrap(nm(1,_)));
  return neurostr::geometry::segment_type(p,q);
}

template <> SEXP wrap(const neurostr::geometry::segment_type &s){
  neurostr::geometry::point_type first = s.first;
  neurostr::geometry::point_type second = s.second;
  Rcpp::NumericVector nv_min(Rcpp::wrap(first));
  Rcpp::NumericVector nv_max(Rcpp::wrap(second));
  Rcpp::NumericMatrix nm(2,3);
  nm(0,_) = nv_min;
  nm(1,_) = nv_max;
  return Rcpp::wrap(nm);
}

}
  
using namespace Rcpp;

Rcpp::List segment_box_intersection(const NumericMatrix& box, const NumericMatrix& segment){
  neurostr::geometry::box_type neurostr_box = ::as<neurostr::geometry::box_type>(::wrap(box));
  neurostr::geometry::segment_type neurostr_segment = ::as<neurostr::geometry::segment_type>(::wrap(segment));
  neurostr::geometry::point_type neurostr_point;
  bool intersects = neurostr::geometry::segment_box_intersection(neurostr_box, neurostr_segment, neurostr_point);
  NumericVector nv_i(::wrap(neurostr_point));
  return Rcpp::List::create(intersects, nv_i);
}

RCPP_MODULE(core_geometry){
  
  function( "get", &neurostr::geometry::get);
  function( "getx", &neurostr::geometry::getx);
  function( "gety", &neurostr::geometry::gety);
  function( "getz", &neurostr::geometry::getz);
  function( "distance", &neurostr::geometry::distance);
  function( "box_box_intersection", &neurostr::geometry::box_box_intersection);
  function( "segment_box_intersection", &segment_box_intersection);
  function( "segment_segment_distance", &neurostr::geometry::segment_segment_distance);
  
}

