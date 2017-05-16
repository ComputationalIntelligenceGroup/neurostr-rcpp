#include <RcppCommon.h>
#include <neurostr/core/node.h>

// [[Rcpp::plugins("cpp14")]]

class Node {
public:
  Node();
  Node(int id_);
  Node(int id_, double x_, double y_, double z_, double r_);
  Node(SEXP);
  operator SEXP();
  neurostr::Node node;
};

#include <Rcpp.h>
#include "include/util.h"

namespace Rcpp {

class Node {
public :
  Node():
  node(){}
  
  Node(int id_):
  node(id_){}
  
  Node(int id_, double x_, double y_, double z_, double r_):
  node(id_, x_, y_, z_, r_) {}
  
  Node(const SEXP & p){
    XPtr<Node> n = unwrap_robject<Node>(p);
    node = n->node;
  }
  
  operator SEXP() const{
    return wrap_in_reference_class<Node>(*this, "Node");
  }
  
  neurostr::Node node;
};

auto get_id(Node n){
  return n.node.id();
}

auto get_radius(Node n){
  return n.node.radius();
}

RCPP_MODULE(core) {
  class_<Node>("Node")
  .constructor()
  .constructor<int>()
  .constructor<int, double, double, double, double>();
  
  function("get_id", &get_id);
  function("get_radius", &get_radius);
}

}