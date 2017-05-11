#include <RcppCommon.h>

// [[Rcpp::plugins("cpp14")]]

/*
namespace Rcpp {

// node wrapping
template <> neurostr::Node as(SEXP node);
template <> SEXP wrap(const neurostr::Node &n);

}*/

#include <Rcpp.h>

namespace Rcpp {

/*
// point_type
template <> neurostr::Node as(SEXP node){
  Rcpp::NumericVector nv(point);
  return neurostr::geometry::point_type(nv[0], nv[1], nv[2]);
}
template <> SEXP wrap(const neurostr::Node &n){
  float x = neurostr::geometry::getx(p);
  float y = neurostr::geometry::gety(p);
  float z = neurostr::geometry::getz(p);
  return Rcpp::wrap(Rcpp::NumericVector::create(x,y,z));
}*/

class Node {
public :
  Node(int id_, double x_, double y_, double z_ ):
  id(id_), x(x_), y(y_), z(z_) {}
  int id;
  double x;
  double y;
  double get_z() { return z; }
  void set_z( double z_ ) { z = z_; }
private :
  double z;
};

auto node_z(Node & n){
  return n.get_z();
}

RCPP_MODULE(core) {
  class_<Node>("node")
  
  .constructor<int, double, double, double>()
  
  .method( "set_z", &Node::set_z)
  .method( "get_z", &Node::get_z)
  ;
  
  function( "node_z", &node_z);
}

}