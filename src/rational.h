#ifndef RATIONALHEADERDEF
#define RATIONALHEADERDEF

#include <iostream>
#include <string>
#include <functional>
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

  // constractors
  Rational();
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

  // printing
  string str() const;
  void print() const { Rcout << str() << "\n"; };
  friend ostream& operator<< (ostream& stream, const Rational& r) {
    stream << r.str();
    return stream;
  }

};


// hash function for rational
namespace std
{
  template <>
  struct hash<Rational>
  {
    size_t operator()(const Rational &r) const {
      bool ne;
      size_t d;
      size_t n;
      if (r.den == 0) {
        ne = false;
        d = 0;
        n = 1;
      } else {
        // simplify as possible to treat 1/3 and 2/6 as same
        size_t g = gcd(r.den, r.num);
        d = r.den/g;
        n = r.num/g;
        ne = r.neg;
      }
      return ((hash<bool>()(ne) ^
        (hash<size_t>()(d) << 1) >> 1) ^
        (hash<size_t>()(n) << 1) >> 1);
    }
  };
}

#endif
