#ifndef _CORE_NODE_H
#define _CORE_NODE_H

#include <RcppCommon.h>
#include <neurostr/core/node.h>

class Node {
public:
  Node();
  Node(int id_);
  Node(int id_, double x_, double y_, double z_, double r_);
  Node(const SEXP&);
  operator SEXP();
  neurostr::Node node;
};

#include <Rcpp.h>
#include "util.h"

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

}

#endif
