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

  void solve(const multiset< NumberWithExpr<T> > &x,
             const bool &findone, const bool &useup);
};


template <class T>
void TenSolver<T>::solve(const multiset< NumberWithExpr<T> > &x,
                         const bool &findone, const bool &useup) {
  if (findone && answers.size() > 0) return;

  if (!useup || x.size() == 1) {
    for (typename multiset< NumberWithExpr<T> >::iterator it=x.begin();
         it != x.end(); ++it) {
      if (*it == tgt) {
        answers.insert(it->expr);
        if (findone) return;
      }
    }
  }
  if (x.size() == 1) return;

  ReductionIterator< NumberWithExpr<T> > iter(x);
  while (iter.hasNext()) {
    solve(iter.next(), findone, useup);
    if (findone && answers.size() > 0) return;
  }
}





#endif
