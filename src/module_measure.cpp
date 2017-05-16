#include <RcppCommon.h>
// [[Rcpp::plugins("cpp14")]]
#include "measure_node_measure.h"

namespace Rcpp{

RCPP_MODULE(measure) {
  function( "node_x", &node_x);
}

}