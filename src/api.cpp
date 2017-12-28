#include <Rcpp.h>
#include "solver.h"
using namespace Rcpp;


// [[Rcpp::export]]
CharacterVector SolveTenPuzzle(IntegerVector x, int tgt, bool one) {
  Rational t(tgt);
  TenSolver<Rational> obj(t);
  multiset< NumberWithExpr<Rational> > y;
  for (size_t i = 0; i < x.size(); i++) {
    Rational tmp(x[i]);
    y.insert(NumberWithExpr<Rational>(tmp));
  }
  obj.solve(y, one);

  CharacterVector ret;
  for (set<string>::iterator i=obj.answers.begin();
       i != obj.answers.end(); ++i) {
    ret.push_back(*i);
  }
  return ret;
}
