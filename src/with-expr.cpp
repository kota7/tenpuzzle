#include <Rcpp.h>
#include "with-expr.h"
using namespace Rcpp;

string toStr(const int &x) {
  return intToStr(x);
}
string toStr(const Rational &x) {
  return x.str();
}
