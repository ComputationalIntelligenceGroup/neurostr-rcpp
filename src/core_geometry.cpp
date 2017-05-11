#include <RcppCommon.h>

// [[Rcpp::plugins("cpp14")]]
// [[Rcpp::depends(BH)]]

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
#include <boost/variant/variant.hpp>
#include <boost/variant/apply_visitor.hpp>
#include <boost/variant/variant_fwd.hpp>

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
  neurostr::geometry::point_type q = Rcpp::as<neurostr::geometry::point_type>(Rcpp::wrap(nm.row(1)));
  neurostr::geometry::point_type r = Rcpp::as<neurostr::geometry::point_type>(Rcpp::wrap(nm.row(2)));
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

NumericVector traslate(NumericVector& p, const NumericVector& v){
  neurostr::geometry::point_type point = ::as<neurostr::geometry::point_type>(::wrap(p));
  neurostr::geometry::point_type vector = ::as<neurostr::geometry::point_type>(::wrap(v));
  neurostr::geometry::traslate(point,vector);
  return NumericVector(::wrap(point));
}

NumericVector scale_1(NumericVector& p, float scale, const NumericVector& ref){
  neurostr::geometry::point_type point = ::as<neurostr::geometry::point_type>(::wrap(p));
  neurostr::geometry::point_type reference = ::as<neurostr::geometry::point_type>(::wrap(ref));
  neurostr::geometry::scale(point,scale,reference);
  return NumericVector(::wrap(point));
}

NumericVector scale_2(NumericVector& p, float rx, float ry, float rz){
  neurostr::geometry::point_type point = ::as<neurostr::geometry::point_type>(::wrap(p));
  neurostr::geometry::scale(point,rx,ry,rz);
  return NumericVector(::wrap(point));
}

NumericVector scale_3(NumericVector& p, float scale){
  neurostr::geometry::point_type point = ::as<neurostr::geometry::point_type>(::wrap(p));
  neurostr::geometry::scale(point,scale);
  return NumericVector(::wrap(point));
}

NumericVector scale(NumericVector& p, float arg2, SEXP arg3, SEXP arg4){
  if(TYPEOF(arg4) != NILSXP){
    return scale_2(p, arg2, ::as<float>(arg3), ::as<float>(arg4));
  }else{
    if(TYPEOF(arg3) == NILSXP){
      return scale_3(p, arg2);
    }else{
      return scale_1(p, arg2, NumericVector(arg3));
    }
  }
}

bool equal(NumericVector& a, NumericVector& b){
  if(a.size() == 2){
    return neurostr::geometry::equal(::as<neurostr::geometry::planar_point>(::wrap(a)), ::as<neurostr::geometry::planar_point>(::wrap(b)));
  }
  return neurostr::geometry::equal(::as<neurostr::geometry::point_type>(::wrap(a)), ::as<neurostr::geometry::point_type>(::wrap(b)));
}

/*
typedef boost::variant<neurostr::geometry::point_type, neurostr::geometry::box_type, neurostr::geometry::segment_type, neurostr::geometry::planar_point> Geometry;

Geometry convert(const SEXP &g){
  if(::Rf_inherits(g, "point_type")){
    neurostr::geometry::point_type p(::as<neurostr::geometry::point_type>(g));
    return Geometry(p);
  }
  if(::Rf_inherits(g, "box_type")){
    neurostr::geometry::box_type b(::as<neurostr::geometry::box_type>(g));
    return Geometry(b);
  }
  if(::Rf_inherits(g, "segment_type")){
    neurostr::geometry::segment_type s(::as<neurostr::geometry::segment_type>(g));
    return Geometry(s);
  }
  if(::Rf_inherits(g, "planar_point")){
    neurostr::geometry::planar_point p(::as<neurostr::geometry::planar_point>(g));
    return Geometry(p);
  }
  throw std::runtime_error("unexpected");
}

struct myvisitor : boost::static_visitor<bool> {
  
  template<typename T, typename S>
  bool operator()(T g1, S g2) const {
    return neurostr::geometry::covered_by(g1,g2);
  }

};

bool covered_by(SEXP g1, SEXP g2){
  auto geo1 = convert(g1);
  auto geo2 = convert(g2);
  return boost::apply_visitor(myvisitor{}, geo1, geo2);
}
*/

List segment_cross_plane(const NumericMatrix & s,
                         const NumericVector & v,
                         int p){
  neurostr::geometry::segment_type s_s = ::as<neurostr::geometry::segment_type>(::wrap(s));
  neurostr::geometry::point_type p_v = ::as<neurostr::geometry::point_type>(::wrap(v));
  neurostr::geometry::point_type p_i;
  switch(p){
    case 0: return List::create(neurostr::geometry::segment_cross_plane<0>(s_s,p_v,p_i), p_i);
    case 1: return List::create(neurostr::geometry::segment_cross_plane<1>(s_s,p_v,p_i), p_i);
    case 2: return List::create(neurostr::geometry::segment_cross_plane<2>(s_s,p_v,p_i), p_i);
    default: return NAN;
  }
}

RCPP_MODULE(core_geometry){
  
  function( "get", &neurostr::geometry::get);
  function( "getx", &neurostr::geometry::getx);
  function( "gety", &neurostr::geometry::gety);
  function( "getz", &neurostr::geometry::getz);
  function( "planar_projection", &neurostr::geometry::planar_projection);
  function( "distance", &neurostr::geometry::distance);
  function( "vector_from_to", &neurostr::geometry::vectorFromTo);
  function( "traslate", &traslate);
  function( "scale", &scale, List::create( _["p"], _["arg2"], _["arg3"] = R_NilValue, _["arg4"] = R_NilValue));
  function( "cross_product", &neurostr::geometry::cross_product);
  function( "norm", &neurostr::geometry::norm);
  function( "equal", &equal);
  function( "get_basis", &neurostr::geometry::get_basis);
  function( "segment_segment_distance", &neurostr::geometry::segment_segment_distance);
  //function( "align_vectors", &neurostr::geometry::align_vectors);
  function( "segment_box_intersection", &segment_box_intersection);
  //function( "covered_by", &covered_by);
  function( "segment_cross_plane", &segment_cross_plane);
  function( "box_box_intersection", &neurostr::geometry::box_box_intersection);
  function( "segment_segment_distance", &neurostr::geometry::segment_segment_distance);
  
}

