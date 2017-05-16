#include <Rcpp.h>

namespace Rcpp {

/* 
 * The author of this helper functions is Ian Fellows <ian.fellows@stat.ucla.edu>
 * Source:
 * http://lists.r-forge.r-project.org/pipermail/rcpp-devel/2011-December/003226.html
 */ 

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

}