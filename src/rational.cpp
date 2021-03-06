#include <string>
#include <Rcpp.h>
#include "utils.h"
#include "rational.h"
using namespace std;
using namespace Rcpp;


Rational::Rational() {
  neg = false;
  den = 0;
  num = 1;
}

Rational::Rational(const int &i) {
  neg = (i < 0);
  if (neg) den = -i; else den = i;
  num = 1;
}

Rational::Rational(const int &d, const int &n) {
  if (n == 0) stop("division by zero");
  if (d == 0) {
    den = 0;
    num = 1;
    neg = false;
    return;
  }

  neg = (d < 0 && n > 0) || (d > 0 && n < 0);
  if (d < 0) den = -d; else den = d;
  if (n < 0) num = -n; else num = n;
}

Rational::Rational(const unsigned int &d,
                   const unsigned int &n,
                   const bool &ne) {
  if (n == 0) stop("division by zero");
  if (d == 0) {
    den = 0;
    num = 1;
    neg = false;
    return;
  }

  neg = ne;
  den = d;
  num = n;
}

void Rational::simplify() {
  if (den == 0) {
    neg = false;
    num = 1;
    return;
  }

  size_t g = gcd(den, num);
  if (g > 1) {
    den /= g;
    num /= g;
  }
}

Rational Rational::operator +(const Rational &r) const {
  unsigned int n = num * r.num;
  int s1;
  int s2;
  if (neg) s1 = -1; else s1 = 1;
  if (r.neg) s2 = -1; else s2 = 1;
  int d = s1*den*r.num + s2*r.den*num;
  bool ne = (d < 0);
  if (ne) d *= -1;
  Rational ret(d, n, ne);
  ret.simplify();
  return ret;
}

Rational Rational::operator *(const Rational &r) const {
  bool ne = (neg && !r.neg) || (!neg && r.neg);
  unsigned int d = den * r.den;
  unsigned int n = num * r.num;
  Rational ret(d, n, ne);
  ret.simplify();
  return ret;
}

Rational Rational::operator /(const Rational &r) const {
  bool ne = (neg && !r.neg) || (!neg && r.neg);
  unsigned int d = den * r.num;
  unsigned int n = num * r.den;
  Rational ret(d, n, ne);
  ret.simplify();
  return ret;
}

bool Rational::operator <(const Rational &r) const {
  if (neg && !r.neg) return true;
  if (!neg && r.neg) return false;
  if (neg) return (den*r.num > r.den*num);
  return (den*r.num < r.den*num);
}


bool Rational::operator ==(const Rational &r) const {
  if (neg != r.neg) return false;
  return (den*r.num == r.den*num);
}


string Rational::str() const {
  string ret = intToStr(den);
  if (num != 1) ret += "/" + intToStr(num);
  if (neg) {
    if (num == 1) ret = "-" + ret; else ret = "-(" + ret + ')';
  }
  return ret;
}



Rational strToRational(const string &s) {
  // remove spaces
  string x = "";
  for (string::const_iterator p = s.begin(); p != s.end(); ++p) {
    if (*p != ' ') x += *p;
  }

  // a quick validity check
  if (x.size() == 0) stop("empty string cannot be converted to rational");

  // find sign
  bool ne = false;
  string::iterator p = x.begin();
  if (*p == '-') {
    ne = true;
    ++p;
  } else if (*p == '+') {
    ne = false;
    ++p;
  }

  // denominator
  string den_str = "";
  bool hasNum = false;
  while (p != x.end()) {
    if (*p == '/') {
      hasNum = true;
      ++p;
      break;
    } else {
      den_str += *p;
      ++p;
    }
  }
  if (den_str.size() == 0) stop("empty denominator");
  size_t de = stoi(den_str);
  // numerator
  size_t nu = 1;
  if (hasNum) {
    string num_str(p, x.end());
    if (num_str.size() == 0) stop("empty numerator");
    nu = stoi(num_str);
  }
  Rational ret(de, nu, ne);
  return ret;
}


