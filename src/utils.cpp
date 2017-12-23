#include <string>
#include <Rcpp.h>
#include "utils.h"
using namespace std;
using namespace Rcpp;


int gcd(int a, int b) {
  // returns the greatest common divisor

  if (a == 0 || b == 0) stop("GCD of zero");

  if (a < 0) a *= -1;
  if (b < 0) b *= -1;

  int m = a % b;
  if (m == 0) return b;
  return gcd(b, m);
}


string intToStr(int x) {
  // convert an integer to string
  if (x == 0) return "0";


  bool neg = (x < 0);
  if (neg) x *= -1;

  string ret = "";
  while (x > 0) {
    int m = x % 10;
    ret += '0' + m;
    x /= 10;
  }
  if (neg) ret += '-';
  reverse(ret.begin(), ret.end());

  return ret;
}


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

/* R
tenpuzzle:::test_utils()
*/
