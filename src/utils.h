#ifndef UTILSHEADERDEF
#define UTILSHEADERDEF


#include <string>
#include <Rcpp.h>
using namespace std;
using namespace Rcpp;


int gcd(int a, int b);
string intToStr(int x);
string toStr(const int &x);
bool isPositive(const int &x);
bool isNegative(const int &x);
bool isZero(const int &x);


#endif
