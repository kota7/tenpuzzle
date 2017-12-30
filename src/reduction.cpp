#include <string>
#include <set>
#include <iterator>
#include <Rcpp.h>
#include "rational.h"
#include "reduction.h"
#include "with-expr.h"
using namespace std;
using namespace Rcpp;


//template <class T>
//const vector<char> ReductionIterator<T>::ops({ '+', '-', '*', '/' });

template <class T>
const string ReductionIterator<T>::ops = "+-*/";

template <class T>
ReductionIterator<T>::ReductionIterator(const multiset<T> x) {
  nums = x;
  i = nums.begin();
  j = nums.begin();
  op = ops.begin();
  positiveOnly = false;
  if (!isValid()) increment();
}

template <class T>
ReductionIterator<T>::ReductionIterator(const multiset<T> x, const bool positive) {
  nums = x;
  i = nums.begin();
  j = nums.begin();
  op = ops.begin();
  positiveOnly = positive;
  if (!isValid()) increment();
}

template <class T>
multiset<T> ReductionIterator<T>::next() {
  multiset<T> ret;
  T x;
  if (*op == '+') {
    x = *i + *j;
  } else if (*op == '-') {
    x = *i - *j;
  } else if (*op == '*') {
    x = *i * *j;
  } else if (*op == '/') {
    x = *i / *j;
  }
  ret.insert(x);
  for (typename multiset<T>::iterator k = nums.begin(); k != nums.end(); ++k) {
    if (k != i && k != j) ret.insert(*k);
  }

  increment();
  return ret;
}

template <class T>
bool ReductionIterator<T>::hasNext() {
  return (op != ops.end());
}

template <class T>
void ReductionIterator<T>::increment() {
  // increment i, j, op to the next value
  // order will be:
  // for each op:
  //   for each i:
  //     for each j:
  ++j;
  if (j == nums.end()) {
    ++i;
    j = nums.begin();
  }
  if (i == nums.end()) {
    ++op;
    i = nums.begin();
  }
  if (op == ops.end()) return; // end of whole loop

  if (!isValid()) increment();
}


// checks if the current pair is valid or not
// criteria may vary by the class
template <>
bool ReductionIterator<int>::isValid() {
  // i must not be equal to j
  if (i == j) return false;

  // positive requirement
  if (positiveOnly && *op == '-' && !(*i > *j)) return false;

  // if op is division, then
  //   j must not be zero and
  //   i mof j must equal zero
  if (*op == '/') {
    if ((*j == 0) || (*i % *j != 0)) return false;
  }

  return true;
}

template <>
bool ReductionIterator<Rational>::isValid() {
  // i must not be equal to j
  if (i == j) return false;

  // positive requirement
  if (positiveOnly && *op == '-' && !(*i > *j)) return false;

  // if op is division, j must not be zero
  if ((*op == '/') && (j->den == 0)) return false;

  return true;
}

template <>
bool ReductionIterator< NumberWithExpr<int> >::isValid() {
  // i must not be equal to j
  if (i == j) return false;

  // positive requirement
  if (positiveOnly && *op == '-' && !(*i > *j)) return false;

  // if op is division, then
  //   j must not be zero and
  //   i mof j must equal zero
  if (*op == '/') {
    if ((*j == 0) || (i->data % j->data != 0)) return false;
  }

  return true;
}

template <>
bool ReductionIterator< NumberWithExpr<Rational> >::isValid() {
  // i must not be equal to j
  if (i == j) return false;

  // positive requirement
  if (positiveOnly && *op == '-' && !(*i > *j)) return false;

  // if op is division, j must not be zero
  if ((*op == '/') && (j->data.den == 0)) return false;


  return true;
}

// template class instantiation
template struct ReductionIterator<int>;
template struct ReductionIterator<Rational>;
template struct ReductionIterator< NumberWithExpr<int> >;
template struct ReductionIterator< NumberWithExpr<Rational> >;




