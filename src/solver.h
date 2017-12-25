#include <vector>
#include <Rcpp.h>
#include "rational.h"
using namespace std;
using namespace Rcpp;

// define alias for a sequence of rational numbers
typedef vector<Rational> nums;


// [[Rcpp::export]]
CharacterVector SolveTenPuzzle(IntegerVector x, int tgt);


struct TenSolver {
  int tgt;
  TenSolver(int t) { tgt = t; }

  CharacterVector solve(const nums &x);
  void solve_rec(nums &x, vector<string> &ans);
};


struct ReductionIterator {
  // iterator for possible reduction for a sequence of rational numbers
  nums origin;
  size_t i;  // current index for next 1st number
  size_t j;  // current index for next 2nd number
  ReductionIterator(const nums x) {
    origin = x;
    i = 0;
    j = 1;
  }

  nums nextChild();
  bool hasNext();
};

