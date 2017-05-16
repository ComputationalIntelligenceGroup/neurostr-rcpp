#include <RcppCommon.h>
// [[Rcpp::plugins("cpp14")]]
#include "core_node.h"

namespace Rcpp{

RCPP_MODULE(core) {
  class_<Node>("Node")
  .constructor()
  .constructor<int>()
  .constructor<int, double, double, double, double>();
}

}