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



