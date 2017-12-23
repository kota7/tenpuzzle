#include <string>
#include <Rcpp.h>
#include "utils.h"
#include "rational.h"
using namespace std;
using namespace Rcpp;


Rational::Rational(const int &i) {

  neg = (i < 0);
  if (neg) den = -i; else den = i;
  num = 1;
  if (neg) expr = "-"; else expr = "";
  expr += intToStr(den);
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

  if (neg) expr = "-"; else expr = "";
  expr += intToStr(d) + " / " + intToStr(n);
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

  if (neg) expr = "-"; else expr = "";
  expr += intToStr(d) + " / " + intToStr(n);
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

Rational Rational::operator +(const Rational &r) {
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
  ret.expr = '(' + this->expr + ") + (" + r.expr + ')';
  return ret;
}

Rational Rational::operator *(const Rational &r) {
  bool ne = (neg && !r.neg) || (!neg && r.neg);
  unsigned int d = den * r.den;
  unsigned int n = num * r.num;
  Rational ret(d, n, ne);
  ret.simplify();
  ret.expr = '(' + this->expr + ") * (" + r.expr + ')';
  return ret;
}

Rational Rational::operator -(const Rational &r) {
  Rational ret = *this + (Rational(-1) * r);
  ret.expr = '(' + this->expr + ") - (" + r.expr + ')';
  return ret;
}

Rational Rational::operator /(const Rational &r) {
  bool ne = (neg && !r.neg) || (!neg && r.neg);
  unsigned int d = den * r.num;
  unsigned int n = num * r.den;
  Rational ret(d, n, ne);
  ret.simplify();
  ret.expr = '(' + this->expr + ") / (" + r.expr + ')';
  return ret;
}

bool Rational::operator <(const Rational &r) {
  if (neg && !r.neg) return true;
  if (!neg && r.neg) return false;

  return (den*r.num < r.den*num);
}

bool Rational::operator ==(const Rational &r) {
  if (neg != r.neg) return false;
  return (den*r.num == r.den*num);
}

void Rational::print() {
  string ret = intToStr(den);
  if (num != 1) ret += " / " + intToStr(num);
  if (neg) ret = "- (" + ret + ')';
  Rcout << ret << "\n";
}


// [[Rcpp::export]]
void test_rational() {
  Rational x(3);
  Rcout << x.expr << "\n";
  x.print();

  Rational y(3, 5);
  Rcout << y.expr << "\n";
  y.print();

  Rational z(2, 4, true);
  Rcout << z.expr << "\n";
  z.print();

  z.simplify();
  Rcout << z.expr << "\n";
  z.print();

  Rational w(0);
  Rcout << w.expr << "\n";
  w.print();

  Rational v(-15);
  Rcout << v.expr << "\n";
  v.print();

  Rcout << (x + y).expr << '\n';
  (x + y).print();
  Rcout << (x - y).expr << "\n";
  (x - y).print();
  Rcout << (x * y).expr << "\n";
  (x * y).print();
  Rcout << (x / y).expr << "\n";
  (x / y).print();

  Rcout << (z + y).expr << "\n";
  (z + y).print();
  Rcout << (z - y).expr << "\n";
  (z - y).print();
  Rcout << (z * y).expr << "\n";
  (z * y).print();
  Rcout << (z / y).expr << "\n";
  (z / y).print();

  Rcout << (x < y) << "\n";
  Rcout << (z < y) << "\n";

  Rcout << (y + w).expr << '\n';
  (y + w).print();
  Rcout << (y - w).expr << "\n";
  (y - w).print();
  Rcout << (y * w).expr << "\n";
  (y * w).print();
  //Rcout << (y / w).expr << "\n";
  //(y / w).print();

  Rcout << (w + y).expr << "\n";
  (w + y).print();
  Rcout << (w - y).expr << "\n";
  (w - y).print();
  Rcout << (w * y).expr << "\n";
  (w * y).print();
  Rcout << (w / y).expr << "\n";
  (w / y).print();

  Rcout << (x < w) << "\n";
  Rcout << (w < x) << "\n";
  Rcout << (z < w) << "\n";
  Rcout << (w < z) << "\n";

  Rcout << (x == x) << "\n";
  Rcout << (y == y) << "\n";
  Rcout << (z == z) << "\n";
  Rcout << (w == w) << "\n";

}

/* R
tenpuzzle:::test_rational()
*/
