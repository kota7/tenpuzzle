#include <string>
#include <Rcpp.h>
#include "clean-paren.h"
using namespace std;
using namespace Rcpp;


CharacterVector CleanParen(CharacterVector expr) {
  for (int i = 0; i < expr.size(); i++) {
    expr[i] = CleanParenSingle(as<string>(expr[i]));
  }

  return expr;
}


string CleanParenSingle(string x) {

  // *** remove unnecessary inner parenthesis
  size_t pos = 0;
  while (pos < x.size()) {
    if (x[pos] == '(') {
      pos = CleanParenHelper(x, pos);
    } else {
      pos++;
    }
  }
  // ***


  // *** remove parenthesis for the whole expression, if any
  int left = -1;
  // search for left parenthesis (before any letter except for space)
  for (size_t i = 0; i < x.size(); i++) {
    // if first letter (except for space) is not parenthesis
    // then there is no parenthesis surrounding all
    if (x[i] != '(' && x[i] != ' ') return x;

    if (x[i] == '(') {
      left = i;
      break;
    }
  }
  // search right parenthesis that match the left
  int right = -1;
  int open = 1;
  for (size_t i = left+1; i < x.size(); i++) {
    if (x[i] == '(') {
      open++;
    } else if (x[i] == ')') {
      open--;
      if (open == 0) {
        right = i;
        break;
      }
    }
  }
  if (right < 0) {
    warning("parenthesis did not close");
    return x;
  }
  // check if there is no letter but space after right
  // othersize, there is no parenthesis surrounding all
  for (size_t i = right+1; i < x.size(); i++) {
    if (x[i] != '(' & x[i] != ')' & x[i] != ' ') return x;
  }
  // reaching here implies the parenthesis at left, right
  // surrounds whole expression
  if (left >= 0 && right >= 0) {
    x[left] = ' ';
    x[right] = ' ';
  }
  // ***

  return x;

}

size_t CleanParenHelper(string &x, size_t pos) {
  // assuming that x[pos] is '(',
  // this function removes unnecessary parentheses
  // until the matching ')'
  //
  // returns the position right after the closing parenthesis
  bool redundant = true;
  size_t i = pos + 1;
  while (i < x.size()) {
    //Rcout << i << '\n';
    if (x[i] == '(') {
      i = CleanParenHelper(x, i);
    } else if (x[i] == ')') {
      if (redundant) {
        x[pos] = ' ';
        x[i] = ' ';
      }
      return i+1;
    } else {
      if (x[i] == '+' || x[i] == '-' || x[i] == '/') redundant = false;
      i++;
    }
  }
  warning("parenthesis did not close\n");
  return x.size();
}








/*** R
tenpuzzle:::CleanParen("(( 8 * 9 + 8 ) / 8 )")
tenpuzzle:::CleanParen(c("(( 8 * 9 + 8 ) / 8 )",
                         "(( 9 * 8 + 8 )) / 8",
                         "( 9 * 8 + 8 ) / 8",
                         "(( 9 * 8 ) + 8 ) / 8"))
tenpuzzle:::CleanParen(c("(((100)))"))
tenpuzzle:::CleanParen(c("(((1 + 2 + 3 + 4 + 5)))"))
*/
