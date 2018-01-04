#ifndef REDUCTIONHEADERDEF
#define REDUCTIONHEADERDEF


#include <string>
#include <set>
#include <iterator>
#include <Rcpp.h>
#include "rational.h"
using namespace std;
using namespace Rcpp;

template <class T>
struct ReductionIterator {
  // iterator for possible reduction of a sequence of numbers
  multiset<T> nums;
  bool nonnegativeOnly;    // requires all numbers are positive
  bool nonzeroOnly;        // requires all numbers are positive
  //static const vector<char> ops;
  static const string ops;

  typename multiset<T>::iterator i;  // pointer to the next 1st number
  typename multiset<T>::iterator j;  // pointer to the next 2nd number
  //vector<char>::const_iterator op;         // pointer to the operator
  string::const_iterator op;

  ReductionIterator(const multiset<T> x);
  ReductionIterator(const multiset<T> x, bool nonnegative, bool nonzero);

  multiset<T> next();
  bool hasNext();
  void increment();
  bool isValid();
};


#endif
