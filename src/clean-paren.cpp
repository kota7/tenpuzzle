#include "clean-paren.h"


CharacterVector CleanParen(CharacterVector expr) {
  CharacterVector ret(expr.size());
  for (int i = 0; i < expr.size(); i++) {
    string x = as<string>(expr[i]);
    CleanParenSingle(x);
    ret[i] = x;
  }

  return ret;
}


void CleanParenSingle(string &x) {
  // This function removes unnecessary parentheses
  // from a mathematical expression.
  // It also removes leading plus sign, if any.


  // put the expression inside a parenthesis
  // for ease of later process
  x = '(' + x + ')';

  // as a preparation, store the prev and next operators
  // for each parenthesis;
  vector<char> prevOp(x.size(), ' ');
  vector<char> nextOp(x.size(), ' ');
  char op = ' ';
  for (size_t i=0; i < x.size(); i++) {
    if (x[i] == '(') {
      // new parenthesis started.
      // record its prev as the current op,
      // then clear the op
      prevOp[i] = op;
      op = ' ';
    } else if (x[i] == '+' || x[i] == '-' || x[i] == '*' || x[i] == '/') {
      op = x[i];
    } else if (x[i] == ')') {
      // regard an closing parentheses as implicit multiplication,
      // if there is no operator in between
      // e.g. (1 + 3) (5 - 2)
      op = '*';
    }
  }
  op = ' ';
  for (size_t i = x.size()-1; i+1 > 0; i--) {
    if (x[i] == ')') {
      nextOp[i] = op;
      op = ' ';
    } else if (x[i] == '+' || x[i] == '-' || x[i] == '*' || x[i] == '/') {
      op = x[i];
    } else if (x[i] == '(') {
      op = '*';
    }
  }

  size_t pos = 0;
  while (pos < x.size()) {
    // check for a parenthesis, recursively
    // the helper function returns the new position
    if (x[pos] == '(') CleanParenHelper(x, pos, prevOp, nextOp); else pos++;
  }


  // remove first and last letter, added at the top
  x = x.substr(1, x.size()-2);

}


void CleanParenHelper(string &x, size_t &pos,
                      const vector<char> &prevOp, const vector<char> &nextOp) {
  // Assuming that x[pos] is '(',
  // this function removes unnecessary parentheses
  // until the matching ')'; and leading plus sign, if any
  // Also, leading plus sign is also removed
  //
  // pos is the current position and is update along the way
  // when ending, set to the position right after the closing parenthesis

  size_t pos_s = pos;       // remember the position of opening parenthesis
  pos++;
  bool started = false;     // indicates that some expression has started
  bool noOps = true;        // indicates no operator inside
  bool noPlusMinus = true;  // indicates no plus or minus
  while (pos < x.size()) {
    //Rcout << i << '\n';
    // check for leading plus signs
    if (!started) {
      if (x[pos] == '+') x[pos] = ' ';
      if (x[pos] != ' ') started = true;
    }

    if (x[pos] == '(') {
      CleanParenHelper(x, pos, prevOp, nextOp);
    } else if (x[pos] == ')') {
      char op_l = prevOp[pos_s];
      char op_r = nextOp[pos];
      // sufficient conditions for parentheses being unnecessary
      // - led by minus or division, provided that there is some operator inside
      if (!noOps && (op_l == '-' || op_l == '/')) {
        pos++;
        return;
      }
      // sufficient conditions for parentheses being unnecessary
      // - expression inside has no operator
      // - no operator at left nor right, i.e. independent parenthesis
      // - there is no "multiplication" around; i.e.,
      //   not led by *, /, or - (leading - is same as multiplying -1)
      //   and not followed by * or /
      // - no plus or minus inside, provided that not led by division
      if (noOps || (op_l==' ' && op_r==' ') ||
          (op_l!='*' && op_l!='/' && op_l!='-' &&  op_r!='*' && op_r!='/') ||
          (op_l != '/' && noPlusMinus)) {
        x[pos_s] = ' ';
        x[pos] = ' ';
      }
      pos++;
      return;
    } else {
      // update key status
      if (x[pos] == '+' || x[pos] == '-') {
        noPlusMinus = false;
      }
      if (x[pos] == '+' || x[pos] == '-' || x[pos] == '*' || x[pos] == '/') {
        noOps = false;
      }
      pos++;
    }
  }
  warning("parenthesis did not close\n");
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
