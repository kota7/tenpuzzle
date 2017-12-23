#include <string>
#include <Rcpp.h>
#include "utils.h"
using namespace std;
using namespace Rcpp;


struct Rational
{
  // define a number by its sign, denominator and numerator
  bool neg;
  unsigned int den;
  unsigned int num;
  // preserves a math expression how this number has been created
  string expr;

  // constractors
  Rational(const int &i);
  Rational(const int &d, const int &n);
  Rational(const unsigned int &d, const unsigned int &n, const bool &ne);

  void simplify();  // simplify the denominator and numerator as possible

  // four basic math operations
  Rational operator +(const Rational &r) const;
  Rational operator -(const Rational &r) const;
  Rational operator *(const Rational &r) const;
  Rational operator /(const Rational &r) const;

  // equality and inequality operation
  bool operator <(const Rational &r) const;
  bool operator ==(const Rational &r) const;
  bool operator >(const Rational &r) const  { return (r < *this); }
  bool operator !=(const Rational &r) const { return !(*this == r); }

  void print() const;

};


