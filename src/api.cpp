#include <Rcpp.h>
#include "solver.h"
using namespace Rcpp;


// [[Rcpp::export]]
CharacterVector SolveTenPuzzle(IntegerVector x, int tgt,
                               bool findone, bool useall, bool intonly,
                               bool nonnegative, bool nonzero) {
  // input validation
  if (nonnegative) {
    for (size_t i = 0; i < x.size(); i++) {
      if (x[i] < 0) stop("negative input with `nonnegative` requirement");
    }
  }
  if (nonzero) {
    for (size_t i = 0; i < x.size(); i++) {
      if (x[i] == 0) stop("zero input with `nonzero` requirement");
    }
  }


  CharacterVector ret;

  if (intonly) {
    TenSolver<int> obj(tgt);
    multiset< NumberWithExpr<int> > y;
    for (size_t i = 0; i < x.size(); i++) {
      int tmp = x[i];
      y.insert(NumberWithExpr<int>(tmp));
    }
    obj.solve(y, findone, useall, nonnegative, nonzero);

    for (set<string>::iterator i=obj.best.second.begin();
         i != obj.best.second.end(); ++i) {
      ret.push_back(*i);
    }
  } else {
    TenSolver<Rational> obj(tgt);
    multiset< NumberWithExpr<Rational> > y;
    for (size_t i = 0; i < x.size(); i++) {
      Rational tmp = x[i];
      y.insert(NumberWithExpr<Rational>(tmp));
    }
    obj.solve(y, findone, useall, nonnegative, nonzero);

    for (set<string>::iterator i=obj.best.second.begin();
         i != obj.best.second.end(); ++i) {
      ret.push_back(*i);
    }
  }
  return ret;
}


