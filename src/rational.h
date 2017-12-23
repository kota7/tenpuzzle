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
  Rational operator +(const Rational &r);
  Rational operator -(const Rational &r);
  Rational operator *(const Rational &r);
  Rational operator /(const Rational &r);

  // less-than and equal-to operation
  bool operator <(const Rational &r);
  bool operator ==(const Rational &r);

  void print();

};


