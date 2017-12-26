#include <set>
#include <iterator>
#include <Rcpp.h>
using namespace std;
using namespace Rcpp;

template <class T>
struct ReductionIterator {
  // iterator for possible reduction of a sequence of numbers
  multiset<T> origin;
  typename multiset<T>::iterator i;  // pointer to the next 1st number
  typename multiset<T>::iterator j;  // pointer to the next 2nd number

  ReductionIterator(const multiset<T> x);

  bool hasNext();
  multiset<T> next();
};


