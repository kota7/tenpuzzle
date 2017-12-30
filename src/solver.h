#ifndef SOLVERHEADERDEF
#define SOLVERHEADERDEF

#include <string>
#include <set>
#include <unordered_set>
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
  pair< T, set<string> > best;
  // `best` stores the closest expressions to the target;
  // first element is the deviation from the target,
  // second is the set of expressions that give the deviation;

  unordered_set< multiset< NumberWithExpr<T> > > noAns;
  // `noAns` records a set of numbers that we know already result in no answer
  // hash function shall be defined below


  TenSolver(T t) { tgt = NumberWithExpr<T>(t); }

  // returns true if some answer is found
  bool solve(const multiset< NumberWithExpr<T> > &x,
             const bool &findone, const bool &useup, const bool &positive);
};


template <class T>
bool TenSolver<T>::solve(const multiset< NumberWithExpr<T> > &x,
                         const bool &findone, const bool &useup,
                         const bool &positive) {
  bool ret = false;

  if (!useup || x.size() == 1) {
    for (typename multiset< NumberWithExpr<T> >::iterator it=x.begin();
         it != x.end(); ++it) {
      // update the best so far
      T dev = abs(it->data - tgt.data);
      if (best.second.size() == 0 || dev < best.first) {
        // if this is the first candidate, any answer is the best
        // or this is strictly better than the current, the best is replaced
        best.first = dev;
        best.second.clear();
        best.second.insert(it->expr);
      } else if (dev == best.first) {
        // same as the current, so append the expression
        best.second.insert(it->expr);
      }

      if (*it == tgt) {
        answers.insert(it->expr);
        ret = true;
        if (findone) return ret;
      }
    }
  }
  if (x.size() == 1) return ret;

  ReductionIterator< NumberWithExpr<T> > iter(x, positive);
  while (iter.hasNext()) {
    multiset< NumberWithExpr<T> > y = iter.next();
    // skip if we already know y gets no answer
    if (noAns.find(y) != noAns.end()) continue;

    // record if this node gets no answer;
    // this record is used for tree pruning;
    // to save memory, currently sets with two elements or smaller
    // are not recorded
    bool found = solve(y, findone, useup, positive);
    if (!found && y.size() > 2) {
      /*
      Rcout << "no ans: [";
      for (typename multiset< NumberWithExpr<T> >::iterator i=y.begin();
           i != y.end(); ++i) {
        Rcout << *i << "; ";
      }
      Rcout << "]\n";
      */
      noAns.insert(y);
    }

    ret = ret || found;  // update the status of current set of numbers

    if (findone && answers.size() > 0) return ret;
  }

  return ret;
}



namespace std
{
  // equal predicates for multiset
  template <class T>
  struct equal_to< multiset< NumberWithExpr<T> > >
  {
    typedef multiset< NumberWithExpr<T> > elemtype;

    bool operator() (const elemtype &x, const elemtype &y) const {
      if (x.size() != y.size()) return false;
      typename elemtype::iterator ix = x.begin();
      typename elemtype::iterator iy = y.begin();
      while (ix != x.end() && iy != y.end()) {
        if (ix->data != iy->data) return false;
        ++ix; ++iy;
      }
      return true;
    }
  };

  // hash function for multiset
  template <class T>
  struct hash< multiset< NumberWithExpr<T> > >
  {
    size_t operator()(const multiset< NumberWithExpr<T> > &x) const {
      size_t ret = x.size();
      for (typename multiset< NumberWithExpr<T> >::iterator i = x.begin();
           i != x.end(); ++i) {
        ret ^= ((hash< NumberWithExpr<T> >()(*i) << 1 ) >> 1);
      }
      return ret;
    }
  };
}

#endif
