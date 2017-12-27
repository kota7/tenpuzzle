#ifndef INTEGERHEADERDEF
#define INTEGERHEADERDEF


#include <string>
#include <Rcpp.h>
#include "utils.h"
using namespace std;
using namespace Rcpp;


struct Integer
{
  // define a number by its sign, denominator and numerator
  int data;
  // preserves a math expression how this number has been created
  string expr;

  // constractors
  Integer();
  Integer(const int &i);

  void simplify();  // simplify the denominator and numerator as possible

  // four basic math operations
  Integer operator +(const Rational &r) const;
  Integer operator -(const Rational &r) const;
  Integer operator *(const Rational &r) const;
  Integer operator /(const Rational &r) const;

  // equality and inequality operation
  bool operator <(const Rational &r) const;
  bool operator ==(const Rational &r) const;
  bool operator >(const Rational &r) const  { return (r < *this); }
  bool operator !=(const Rational &r) const { return !(*this == r); }

  void print() const;
  string str() const;

};


#endif
