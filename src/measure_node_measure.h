#ifndef _MEASURE_NODE_MEASURE_H
#define _MEASURE_NODE_MEASURE_H

#include <RcppCommon.h>
#include "core_node.h"

float node_x(Node & n);

#include <neurostr/measure/node_measure.h>
#include <Rcpp.h>

namespace Rcpp {

float node_x(Node & n){
  return neurostr::measure::node_x(n.node);
}

}
#endif