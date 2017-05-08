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

// planar_point wrapping
template <> neurostr::geometry::planar_point as(SEXP point);
template <> SEXP wrap(const neurostr::geometry::planar_point &p);

}

#include <Rcpp.h>
#include <iostream>

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
  neurostr::geometry::point_type p = Rcpp::as<neurostr::geometry::point_type>(Rcpp::wrap(nm.row(0)));
  neurostr::geometry::point_type q = Rcpp::as<neurostr::geometry::point_type>(Rcpp::wrap(nm.row(1)));
  return neurostr::geometry::box_type(p,q);
}
template <> SEXP wrap(const neurostr::geometry::box_type &b){
  neurostr::geometry::point_type min_corner = b.min_corner();
  neurostr::geometry::point_type max_corner = b.max_corner();
  Rcpp::NumericVector nv_min(Rcpp::wrap(min_corner));
  Rcpp::NumericVector nv_max(Rcpp::wrap(max_corner));
  Rcpp::NumericMatrix nm(2,3);
  nm.row(0) = nv_min;
  nm.row(1) = nv_max;
  return Rcpp::wrap(nm);
}

// segment_type
template <> neurostr::geometry::segment_type as(SEXP segment){
  Rcpp::NumericMatrix nm(segment);
  neurostr::geometry::point_type p = Rcpp::as<neurostr::geometry::point_type>(Rcpp::wrap(nm.row(0)));
  neurostr::geometry::point_type q = Rcpp::as<neurostr::geometry::point_type>(Rcpp::wrap(nm.row(1)));
  return neurostr::geometry::segment_type(p,q);
}
template <> SEXP wrap(const neurostr::geometry::segment_type &s){
  neurostr::geometry::point_type first = s.first;
  neurostr::geometry::point_type second = s.second;
  Rcpp::NumericVector nv_min(Rcpp::wrap(first));
  Rcpp::NumericVector nv_max(Rcpp::wrap(second));
  Rcpp::NumericMatrix nm(2,3);
  nm.row(0) = nv_min;
  nm.row(1) = nv_max;
  return Rcpp::wrap(nm);
}

// triangle_type
template <> neurostr::geometry::triangle_type as(SEXP triangle){
  Rcpp::NumericMatrix nm(triangle);
  neurostr::geometry::point_type p = Rcpp::as<neurostr::geometry::point_type>(Rcpp::wrap(nm.row(0)));
  neurostr::geometry::point_type q= Rcpp::as<neurostr::geometry::point_type>(Rcpp::wrap(nm.row(1)));
  neurostr::geometry::point_type r= Rcpp::as<neurostr::geometry::point_type>(Rcpp::wrap(nm.row(2)));
  neurostr::geometry::triangle_type t = {p,q,r};
  return t;
}
template <> SEXP wrap(const neurostr::geometry::triangle_type &t){
  neurostr::geometry::point_type p = std::get<0>(t);
  neurostr::geometry::point_type q = std::get<1>(t);
  neurostr::geometry::point_type r = std::get<2>(t);
  Rcpp::NumericVector nv_p(Rcpp::wrap(p));
  Rcpp::NumericVector nv_q(Rcpp::wrap(q));
  Rcpp::NumericVector nv_r(Rcpp::wrap(r));
  Rcpp::NumericMatrix nm(3,3);
  nm.row(0) = nv_p;
  nm.row(1) = nv_q;
  nm.row(2) = nv_r;
  return Rcpp::wrap(nm);
}

// planar_point
template <> neurostr::geometry::planar_point as(SEXP point){
  Rcpp::NumericVector nv(point);
  return neurostr::geometry::planar_point(nv[0], nv[1]);
}
template <> SEXP wrap(const neurostr::geometry::planar_point &p){
  float x = neurostr::geometry::get<0>(p);
  float y = neurostr::geometry::get<1>(p);
  return Rcpp::wrap(Rcpp::NumericVector::create(x,y));
}

}

using namespace Rcpp;

List segment_box_intersection(const NumericMatrix& box, const NumericMatrix& segment){
  neurostr::geometry::box_type neurostr_box = ::as<neurostr::geometry::box_type>(::wrap(box));
  neurostr::geometry::segment_type neurostr_segment = ::as<neurostr::geometry::segment_type>(::wrap(segment));
  neurostr::geometry::point_type neurostr_point;
  bool intersects = neurostr::geometry::segment_box_intersection(neurostr_box, neurostr_segment, neurostr_point);
  NumericVector nv_i(::wrap(neurostr_point));
  return List::create(intersects, nv_i);
}

RCPP_MODULE(core_geometry){
  
  function( "get", &neurostr::geometry::get);
  function( "getx", &neurostr::geometry::getx);
  function( "gety", &neurostr::geometry::gety);
  function( "getz", &neurostr::geometry::getz);
  function( "planar_projection", &neurostr::geometry::planar_projection);
  function( "distance", &neurostr::geometry::distance);
  function( "vector_from_to", &neurostr::geometry::vectorFromTo);
  function( "box_box_intersection", &neurostr::geometry::box_box_intersection);
  function( "segment_box_intersection", &segment_box_intersection);
  function( "segment_segment_distance", &neurostr::geometry::segment_segment_distance);
  
}

