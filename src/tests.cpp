#include <set>
#include <iterator>
#include <Rcpp.h>
#include "utils.h"
#include "rational.h"
using namespace std;
using namespace Rcpp;



// [[Rcpp::export]]
void test_utils() {
  Rcout << "gcd(6, 15) = " << gcd(6, 15) << "\n";
  Rcout << "gcd(28, 14) = " << gcd(28, 14) << "\n";
  Rcout << "gcd(-4, 6) = " << gcd(-4, 6) << "\n";
  Rcout << "gcd(-25, -10) = " << gcd(-25, -10) << "\n";

  Rcout << "intToStr(7) = " << intToStr(7) << "\n";
  Rcout << "intToStr(0) = " << intToStr(0) << "\n";
  Rcout << "intToStr(1) = " << intToStr(1) << "\n";
  Rcout << "intToStr(109) = " << intToStr(109) << "\n";
  Rcout << "intToStr(-21) = " << intToStr(-21) << "\n";
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

  Rcout << (x != x) << "\n";
  Rcout << (y != y) << "\n";
  Rcout << (z != z) << "\n";
  Rcout << (w != w) << "\n";

  Rcout << (x == y) << "\n";
  Rcout << (y == z) << "\n";
  Rcout << (z == w) << "\n";
  Rcout << (w == v) << "\n";


  Rcout << (x > w) << "\n";
  Rcout << (w > x) << "\n";
  Rcout << (z > w) << "\n";
  Rcout << (w > z) << "\n";

  Rcout << "multiset for Rational\n";
  multiset<Rational> s;
  s.insert(Rational(7, 21, false));
  s.insert(Rational(8, 20, true));
  s.insert(Rational(1, 3));
  s.insert(Rational(2, 5, true));
  s.insert(Rational(4));
  s.insert(Rational(4, 3, true));
  s.insert(Rational(1, 3, false));
  s.insert(Rational(4, 1, true));
  s.insert(Rational(4, 1, false));
  s.insert(Rational(4, 3, false));
  s.insert(Rational(8, 2, false));
  s.insert(Rational(6, 15, false));
  s.insert(Rational(6, 15, false));

  for (multiset<Rational>::iterator i = s.begin(); i != s.end(); ++i) {
    i -> print();
  }
}





/* R
 tenpuzzle:::test_utils()
 tenpuzzle:::test_rational()
*/