#ifndef CLEANPARENHEADERDEF
#define CLEANPARENHEADERDEF

#include <string>
#include <vector>
#include <Rcpp.h>
using namespace std;
using namespace Rcpp;


// [[Rcpp::export]]
CharacterVector CleanParen(CharacterVector expr);

void CleanParenSingle(string &x);
void CleanParenHelper(string &x, size_t &pos,
                      const vector<char> &prevOp, const vector<char> &nextOp);



#endif
