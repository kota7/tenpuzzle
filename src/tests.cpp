#include <set>
#include <iterator>
#include <Rcpp.h>
#include "utils.h"
#include "rational.h"
#include "reduction.h"
#include "solver.h"
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
  x.print();

  Rational y(3, 5);
  y.print();

  Rational z(2, 4, true);
  z.print();

  z.simplify();
  z.print();

  Rational w(0);
  w.print();

  Rational v(-15);
  v.print();

  (x + y).print();
  (x - y).print();
  (x * y).print();
  (x / y).print();

  (z + y).print();
  (z - y).print();
  (z * y).print();
  (z / y).print();

  Rcout << (x < y) << "\n";
  Rcout << (z < y) << "\n";

  (y + w).print();
  (y - w).print();
  (y * w).print();
  //Rcout << (y / w).expr << "\n";
  //(y / w).print();

  (w + y).print();
  (w - y).print();
  (w * y).print();
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



// [[Rcpp::export]]
void test_reduction() {
  multiset<int> x;
  x.insert(3);
  x.insert(5);
  x.insert(3);
  x.insert(4);
  ReductionIterator<int> r(x);
  int ct = 0;
  while (r.hasNext()) {
    ct++;
    Rcout << ct << "\tnext is " << *r.i << ' ' << *r.op << ' ' << *r.j << ": ";
    multiset<int> y = r.next();
    for (multiset<int>::iterator i=y.begin(); i != y.end(); ++i) {
      Rcout << *i << ' ';
    }
    Rcout << '\n';
  }

  Rcout << "*********************\n";

  multiset<Rational> z;
  z.insert(Rational(4));
  z.insert(Rational(10, 15));
  z.insert(Rational(10, 15, false));
  z.insert(Rational(3, 2, true));
  ReductionIterator<Rational> s(z);
  ct = 0;
  while (s.hasNext()) {
    ct++;
    Rcout << ct << "\tnext is " << s.i->str() << ' ' <<
      *s.op << ' ' << s.j->str() << ": ";
    multiset<Rational> w = s.next();
    for (multiset<Rational>::iterator i=w.begin(); i != w.end(); ++i) {
      Rcout << i->str() << ' ';
    }
    Rcout << '\n';
  }
}


/* R
 tenpuzzle:::test_utils()
 tenpuzzle:::test_rational()
 tenpuzzle:::test_reduction()
 tenpuzzle:::SolveTenPuzzle(c(1, 1, 9, 9), 10)
*/
