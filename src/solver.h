#ifndef SOLVERHEADERDEF
#define SOLVERHEADERDEF

#include <string>
#include <set>
#include <Rcpp.h>
#include "rational.h"
#include "reduction.h"
using namespace std;
using namespace Rcpp;


// [[Rcpp::export]]
CharacterVector SolveTenPuzzle(IntegerVector x, int tgt);


template <class T>
struct TenSolver {
  T tgt;
  set<string> answers;

  TenSolver(T t) { tgt = t; }

  void solve(const multiset<T> &x);
};


#endif
