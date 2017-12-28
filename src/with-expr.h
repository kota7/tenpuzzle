#ifndef WITHEXPRHEADERDEF
#define WITHEXPRHEADERDEF


#include <string>
#include <Rcpp.h>
#include "utils.h"
#include "rational.h"
using namespace std;
using namespace Rcpp;


// functions to compute the string expression of a number
string toStr(const int &x);
string toStr(const Rational &x);


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

  // four basic math operations
  NumberWithExpr operator +(const NumberWithExpr &y) const {
    NumberWithExpr ret(data + y.data);
    ret.expr = '(' + expr + ") + (" + y.expr + ')';
    return ret;
  }
  NumberWithExpr operator -(const NumberWithExpr &y) const {
    NumberWithExpr ret(data - y.data);
    ret.expr = '(' + expr + ") - (" + y.expr + ')';
    return ret;
  }
  NumberWithExpr operator *(const NumberWithExpr &y) const {
    NumberWithExpr ret(data * y.data);
    ret.expr = '(' + expr + ") * (" + y.expr + ')';
    return ret;
  }
  NumberWithExpr operator /(const NumberWithExpr &y) const {
    NumberWithExpr ret(data / y.data);
    ret.expr = '(' + expr + ") / (" + y.expr + ')';
    return ret;
  }

  // equality and inequality operation
  bool operator <(const NumberWithExpr &y)  const { return data < y.data; };
  bool operator ==(const NumberWithExpr &y) const { return data == y.data; };
  bool operator >(const NumberWithExpr &y)  const { return y.data < data; }
  bool operator !=(const NumberWithExpr &y) const { return !(data == y.data); }
};



#endif
