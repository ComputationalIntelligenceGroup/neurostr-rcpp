/*#include <RcppCommon.h>

// [[Rcpp::plugins("cpp14")]]

#include <neurostr/core/node.h>
#include <neurostr/measure/node_measure.h>

#include <Rcpp.h>

namespace Rcpp {

auto node_x(SEXP & n){
  
  return neurostr::measure::node_x(Rcpp::as<neurostr::Node>(n));
}

RCPP_MODULE(measure) {
  
  function( "node_x", &node_x);
  
}

}*/