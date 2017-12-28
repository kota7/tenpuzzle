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

  void solve(const multiset< NumberWithExpr<T> > &x, bool one);
};


template <class T>
void TenSolver<T>::solve(const multiset< NumberWithExpr<T> > &x, bool one) {
  if (one && answers.size() > 0) return;

  if (x.size() == 1) {
    if (*x.begin() == tgt) {
      answers.insert(x.begin()->expr);
    }
    return;
  }

  ReductionIterator< NumberWithExpr<T> > iter(x);
  while (iter.hasNext()) {
    solve(iter.next(), one);
    if (one && answers.size() > 0) return;
  }
}





#endif
