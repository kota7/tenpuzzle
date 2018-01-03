#ifndef EVALUATEHEADERDEF
#define EVALUATEHEADERDEF


#include <Rcpp.h>
#include <string>
#include "rational.h"
using namespace std;
using namespace Rcpp;

//' Convert infix mathematical expression to postfix notation
//'
//' @param x character vector of mathematical expression in the infix notation
//' @return character vector of the postfix notation
//' @examples
//' to_postfix(c("1 + 2 + 3", "(4 - 1)*(-3 + 7) / 5", "(2*3 - 6)*(4 + 1/5)"))
//' @export
// [[Rcpp::export]]
CharacterVector to_postfix(CharacterVector x);


//' Convert mathematical expression into reverse polish notation
//'
//' @param x character vector of mathematical expression
//' @return a list
//' @examples
//' eval_expr(c("1 + 2 + 3", "(4 - 1)*(-3 + 7) / 5", "(2*3 - 6)*(4 + 1/5)"))
//' @export
// [[Rcpp::export]]
List eval_expr(CharacterVector x);


string ToPostfixSingle(const string &expr);

struct EvalResult
{
  double result_dbl;
  Rational result_rat;
  bool intonly;
  bool nonzero;
  bool nonnegative;
};

EvalResult EvaluatePostfixSingle(const string &x);

#endif
