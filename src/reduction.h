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
  //static const vector<char> ops;
  static const string ops;

  typename multiset<T>::iterator i;  // pointer to the next 1st number
  typename multiset<T>::iterator j;  // pointer to the next 2nd number
  //vector<char>::const_iterator op;         // pointer to the operator
  string::const_iterator op;

  ReductionIterator(const multiset<T> x);

  multiset<T> next();
  bool hasNext();
  void increment();
  bool isValid();
};


#endif
