#ifndef SOLVERHEADERDEF
#define SOLVERHEADERDEF

#include <string>
#include <set>
#include <Rcpp.h>
#include "rational.h"
#include "reduction.h"
#include "with-expr.h"
using namespace std;
using namespace Rcpp;


template <class T>
struct TenSolver {
  NumberWithExpr<T> tgt;
  set<string> answers;

  TenSolver(T t) { tgt = NumberWithExpr<T>(t); }

  void solve(const multiset< NumberWithExpr<T> > &x);
};


template <class T>
void TenSolver<T>::solve(const multiset< NumberWithExpr<T> > &x) {
  if (x.size() == 1) {
    if (*x.begin() == tgt) answers.insert(x.begin()->expr);

    return;
  }

  ReductionIterator< NumberWithExpr<T> > iter(x);
  while (iter.hasNext()) {
    solve(iter.next());
  }
}


// [[Rcpp::export]]
CharacterVector SolveTenPuzzle(IntegerVector x, int tgt) {
  Rational t(tgt);
  TenSolver<Rational> obj(t);
  multiset< NumberWithExpr<Rational> > y;
  for (size_t i = 0; i < x.size(); i++) {
    Rational tmp(x[i]);
    y.insert(NumberWithExpr<Rational>(tmp));
  }
  obj.solve(y);

  CharacterVector ret;
  for (set<string>::iterator i=obj.answers.begin();
       i != obj.answers.end(); ++i) {
    ret.push_back(*i);
  }
  return ret;
}



#endif
