#ifndef WITHEXPRHEADERDEF
#define WITHEXPRHEADERDEF


#include <string>
#include <cmath>
#include <Rcpp.h>
#include "utils.h"
#include "rational.h"
using namespace std;
using namespace Rcpp;



template <class T>
struct NumberWithExpr
{
  // class with a number associated with expression that derives it;
  // in addition to the current state of number,
  // store the whole history of calculation to get to the current state

  T data;       // current number
  string expr;  // mathematical operation

  // constractors
  NumberWithExpr() { }
  NumberWithExpr(const T &x) {
    data = x;
    expr = toStr(data);
  }

  // unary minus operator
  NumberWithExpr<T> operator-() const {
    NumberWithExpr<T> ret = this->operator-();
    ret.expr = "-(" + expr + ')';
    return ret;
  }
  // four basic math operations
  NumberWithExpr<T> operator +(const NumberWithExpr<T> &y) const {
    NumberWithExpr<T> ret(data + y.data);
    ret.expr = '(' + expr + ") + (" + y.expr + ')';
    return ret;
  }
  NumberWithExpr<T> operator -(const NumberWithExpr<T> &y) const {
    NumberWithExpr<T> ret(data - y.data);
    ret.expr = '(' + expr + ") - (" + y.expr + ')';
    return ret;
  }
  NumberWithExpr<T> operator *(const NumberWithExpr<T> &y) const {
    NumberWithExpr<T> ret(data * y.data);
    ret.expr = '(' + expr + ") * (" + y.expr + ')';
    return ret;
  }
  NumberWithExpr<T> operator /(const NumberWithExpr<T> &y) const {
    NumberWithExpr<T> ret(data / y.data);
    ret.expr = '(' + expr + ") / (" + y.expr + ')';
    return ret;
  }

  // equality and inequality operation
  bool operator <(const NumberWithExpr &y)  const { return data < y.data; }
  bool operator ==(const NumberWithExpr &y) const { return data == y.data; }
  bool operator >(const NumberWithExpr &y)  const { return y < *this; }
  bool operator !=(const NumberWithExpr &y) const { return !(*this == y); }


  // ostream
  friend ostream& operator<< (ostream& stream, const NumberWithExpr<T>& x) {
    stream << x.data;
    return stream;
  }

  // absolute value
  friend NumberWithExpr<T> abs(NumberWithExpr<T> &x) {
    NumberWithExpr<T> ret(abs(x.data));
    ret.expr = '|' + x.expr + '|';
    return ret;
  }

};




// hash function for number-with-expr
// just use the hash for the `data` field
namespace std
{
  template <class T>
  struct hash< NumberWithExpr<T> >
  {
    size_t operator()(const NumberWithExpr<T> &x) const {
      return hash<T>()(x.data);
    }
  };
}


#endif
