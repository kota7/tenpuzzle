#include <Rcpp.h>
#include <stack>
#include "evaluate.h"
using namespace Rcpp;


CharacterVector to_postfix(CharacterVector x) {
  CharacterVector ret = CharacterVector(x.size());
  for (size_t i = 0; i < x.size(); i++) {
    ret[i] = ToPostfixSingle(as<string>(x[i]));
  }

  return ret;
}


List EvaluateExpr(CharacterVector x) {
  NumericVector value(x.size());
  LogicalVector intonly(x.size());
  LogicalVector nonzero(x.size());
  LogicalVector nonnegative(x.size());
  for (size_t i = 0; i < x.size(); i++) {
    string y = ToPostfixSingle(as<string>(x[i]));
    EvalResult tmp = EvaluatePostfixSingle(y);
    value[i]       = tmp.result_dbl;
    intonly[i]     = tmp.intonly;
    nonzero[i]     = tmp.nonzero;
    nonnegative[i] = tmp.nonnegative;
  }

  List ret = List::create(
    Named("value")       = value,
    Named("intonly")     = intonly,
    Named("nonzero")     = nonzero,
    Named("nonnegative") = nonnegative
  );
  return ret;
}


string ToPostfixSingle(const string &expr) {

  // remove all spaces from the input
  string x = "";
  for (string::const_iterator p= expr.begin(); p != expr.end(); ++p) {
    if (!(*p == '+' || *p == '-' || *p == '*' || *p == '/' ||
          *p == ' ' || (*p >= '0' && *p <= '9') ||
          *p == '(' || *p == ')')) {
      string msg = "invalid letter `";
      msg += *p;
      msg += "`";
      stop(msg);
    }
    if (*p != ' ') x += *p;
  }
  // validity check
  int openParen = 0;
  for (size_t i = 0; i < x.size(); i++) {
    char a = x[i];
    if (!(a == '+' || a == '-' || a == '*' || a == '/' ||
          a == ' ' || (a >= '0' && a <= '9') ||
          a == '(' || a == ')')) {
      string msg = "invalid letter `";
      msg += a;
      msg += "`";
      stop(msg);
    }

    if (a == '(') {
      openParen++;
    } else if (a == ')') {
      openParen--;
    }
    if (openParen < 0) stop("no matching opening `(`");

    if (i > 0) {
      char a = x[i];
      char b = x[i-1];
      if ((a == '+' || a == '-' || a == '*' || a == '/') &&
          (b == '+' || b == '-' || b == '*' || b == '/')) {
        string msg = "operators side by side `";
        msg += b;
        msg += a;
        msg += '`';
        stop(msg);
      }
    }
  }
  if (openParen != 0) stop("parenthesis not closed");


  string::iterator p = x.begin();
  string ret = "";
  bool leading = true;  // indicates currently at the beginning of expression or
  stack<char> operators;
  while (p != x.end()) {
    if ((leading && (*p == '+' || *p == '-')) ||
        (*p >= '0' && *p <= '9')) {
      // encountered a number expression
      // push to the ret until the number ends
      // make sure to add a space at the end
      if (*p != '+') ret += *p;
      leading = false;
      ++p;
      while (*p >= '0' && *p <= '9') {
        ret += *p;
        ++p;
      }
      ret += ' ';
      continue;
    } else if (*p == ')') {
      // closing parenthesis
      // push the stacked operators until encountering
      // opening parenthesis
      while (true) {
        if (operators.empty()) stop("no matching `(`");
        char a = operators.top();
        operators.pop();
        if (a == '(') break;
        ret += a;
        ret += ' ';
      }
      ++p;
      leading = false;
    } else if (*p == '(') {
      operators.push('(');
      ++p;
      leading = true;
    } else if (*p == '+' || *p == '-') {
      while (!operators.empty()) {
        if (operators.top() == '+' || operators.top() == '-' ||
            operators.top() == '*' || operators.top() == '/') {
          ret += operators.top();
          ret += ' ';
          operators.pop();
        } else {
          break;
        }
      }
      operators.push(*p);
      ++p;
      leading = false;
    } else if (*p == '*' || *p == '/') {
      while (!operators.empty()) {
        if (operators.top() == '*' || operators.top() == '/') {
          ret += operators.top();
          ret += ' ';
          operators.pop();
        } else {
          break;
        }
      }
      operators.push(*p);
      ++p;
      leading = false;
    } else {
      string msg = "invalid letter: `";
      msg += *p;
      msg += "`";
      stop(msg);
    }
  }

  while (!operators.empty()) {
    // push remaining operators to the outcome
    ret += operators.top();
    ret += ' ';
    operators.pop();
  }

  return ret;
}


EvalResult EvaluatePostfixSingle(const string &x) {
  stack<Rational> numbers;

  bool intonly     = true;
  bool nonzero     = true;
  bool nonnegative = true;

  string::const_iterator p = x.begin();
  while (p != x.end()) {
    if (*p == ' ') {
      ++p;
      continue;
    } else {
      string tmp = "";
      while (p != x.end() && *p != ' ') {
        tmp += *p;
        ++p;
      }
      if (tmp == "+" || tmp == "-" || tmp == "*" || tmp == "/") {
        if (numbers.size() < 2) stop("not enough numbers");
        Rational n1 = numbers.top();
        numbers.pop();
        Rational n2 = numbers.top();
        numbers.pop();

        Rational n3;
        switch (tmp[0]) {
          case '+': n3 = n2 + n1; break;
          case '-': n3 = n2 - n1; break;
          case '*': n3 = n2 * n1; break;
          case '/': n3 = n2 / n1; break;
        }

        if (n3.num != 1)       intonly = false;
        if (n3 == Rational(0)) nonzero = false;
        if (n3 < Rational(0))  nonnegative = false;
        numbers.push(n3);
      } else {
        Rational n = strToRational(tmp);
        if (n.num != 1)       intonly = false;
        if (n == Rational(0)) nonzero = false;
        if (n < Rational(0))  nonnegative = false;
        numbers.push(n);
      }
    }
  }

  if (numbers.size() != 1) stop("invalid expression");
  Rational ans_rat = numbers.top();
  double   ans_dbl = toDouble(ans_rat);

  EvalResult ret;
  ret.result_dbl  = ans_dbl;
  ret.result_rat  = ans_rat;
  ret.intonly     = intonly;
  ret.nonnegative = nonnegative;
  ret.nonzero     = nonzero;
  return ret;
}
