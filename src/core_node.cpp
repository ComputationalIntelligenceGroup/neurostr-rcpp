#include <RcppCommon.h>

// [[Rcpp::plugins("cpp14")]]

class Node {
public:
  Node(int id_, double x_, double y_, double z_);
  Node(SEXP);
  operator SEXP();
  int get_id();
  double get_x();
  double get_y();
  double get_z();
private:
  int x;
  double y;
  double z;
};

#include <Rcpp.h>

namespace Rcpp {

// http://lists.r-forge.r-project.org/pipermail/rcpp-devel/2011-December/003226.html
template<class T>
XPtr<T> unwrap_robject(const SEXP& sexp){
  RObject ro(sexp);
  if(ro.isObject()){
    Language call("as.environment",sexp);
    SEXP ev = call.eval();
    Language call1("get",".pointer",-1,ev);
    SEXP ev1 = call1.eval();
    XPtr<T > xp(ev1);
    return xp;
  }else{
    XPtr<T > xp(sexp);
    return xp;
  }
}

template<class T>
SEXP wrap_in_reference_class(const T& obj,std::string class_name){
  XPtr< T > xp(new T(obj));
  Language call( "new", Symbol( class_name ),xp);
  return call.eval();
}

class Node {
public :
  // not working, the pointer has wrong values...
  Node(const SEXP & p){
    XPtr<Node> n = unwrap_robject<Node>(p);
    Node(n->get_id(), n->get_x(), n->get_y(), n->get_z());
  }
  Node(int id_, double x_, double y_, double z_):
  id(id_), x(x_), y(y_), z(z_) {}
  
  operator SEXP() const{
    return wrap_in_reference_class<Node>(*this, "Node");
  }
  
  int get_id(){
    return id;
  }
  
  double get_x(){
    return x;
  }
  
  double get_y(){
    return y;
  }
  
  double get_z(){
    return z;
  }

private:
  int id;
  double x;
  double y;
  double z;
};

auto node_z(Node n){
  //Node node(n);
  return n.get_z();
}

RCPP_MODULE(core) {
  class_<Node>("Node")
  
  .constructor<int, double, double, double>()
  
  .method( "get_id", &Node::get_id)
  .method( "get_x", &Node::get_x)
  .method( "get_y", &Node::get_y)
  .method( "get_z", &Node::get_z)
  ;
  
  function( "node_z", &node_z);
}

}