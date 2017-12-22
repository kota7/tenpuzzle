#include <string>
#include <Rcpp.h>
using namespace std;
using namespace Rcpp;


// [[Rcpp::export]]
CharacterVector CleanParen(CharacterVector expr);

string CleanParenSingle(string x);
size_t CleanParenHelper(string &x, size_t pos);




