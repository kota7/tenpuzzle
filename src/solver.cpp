#include <Rcpp.h>
#include "solver.h"
using namespace std;
using namespace Rcpp;

CharacterVector SolveTenPuzzle(IntegerVector x, int tgt) {
  Rational t = Rational(tgt);
  TenSolver<Rational> obj(t);
  multiset<Rational> y;
  for (size_t i = 0; i < x.size(); i++) y.insert(Rational(x[i]));
  obj.solve(y);

  CharacterVector ret;
  for (set<string>::iterator i=obj.answers.begin();
       i != obj.answers.end(); ++i) {
    ret.push_back(*i);
  }
  return ret;
}



template <class T>
void TenSolver<T>::solve(const multiset<T> &x) {
  if (x.size() == 1) {
    if (*x.begin() == tgt) answers.insert(x.begin()->expr);

    return;
  }

  ReductionIterator<T> iter(x);
  while (iter.hasNext()) {
    solve(iter.next());
  }
}

template class TenSolver<Rational>;


// [[Rcpp::export]]
void test_tensolver() {
  TenSolver<Rational> obj(Rational(10, 1));
  multiset<Rational> x;
  x.insert(Rational(1));
  x.insert(Rational(1));
  x.insert(Rational(9));
  x.insert(Rational(9));
  obj.solve(x);
  for (set<string>::iterator i=obj.answers.begin(); i != obj.answers.end(); ++i) {
    Rcout << *i << '\n';
  }
}

/* R
 tenpuzzle:::test_tensolver()
 tenpuzzle:::SolveTenPuzzle(c(1, 1, 9, 9), 10)
*/
