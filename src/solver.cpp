#include <vector>
#include <Rcpp.h>
#include "solver.h"
using namespace std;
using namespace Rcpp;

CharacterVector SolveTenPuzzle(IntegerVector x, int tgt) {
  /*
  TenSolver obj(tgt);
  nums y(0);
  for (size_t i = 0; i < x.size(); i++) y.push_back(Rational(x[i]));
  CharacterVector ret = obj.solve(y);
  */
  CharacterVector ret;
  return ret;
}


/*
struct TenSolver {
  int tgt;
  TenSolver(int t) { tgt = t; }

  vector<nums> getChildren(nums &x);

  CharacterVector solve(nums &x);
  void solve_rec(nums &x, vector<string> &ans);
};
*/


/*** R
*/
