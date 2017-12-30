#include <Rcpp.h>
#include "solver.h"
using namespace Rcpp;


// [[Rcpp::export]]
CharacterVector SolveTenPuzzle(IntegerVector x, int tgt,
                               bool findone, bool useup, bool positive) {
  Rational t(tgt);
  TenSolver<Rational> obj(t);
  multiset< NumberWithExpr<Rational> > y;
  for (size_t i = 0; i < x.size(); i++) {
    Rational tmp(x[i]);
    y.insert(NumberWithExpr<Rational>(tmp));
  }
  obj.solve(y, findone, useup, positive);

  CharacterVector ret;
  for (set<string>::iterator i=obj.answers.begin();
       i != obj.answers.end(); ++i) {
    ret.push_back(*i);
  }
  return ret;
}


// [[Rcpp::export]]
CharacterVector SolveTenPuzzleInt(IntegerVector x, int tgt,
                                  bool findone, bool useup, bool positive) {
  TenSolver<int> obj(tgt);
  multiset< NumberWithExpr<int> > y;
  for (size_t i = 0; i < x.size(); i++) {
    int tmp = x[i];
    y.insert(NumberWithExpr<int>(tmp));
  }
  obj.solve(y, findone, useup, positive);

  CharacterVector ret;
  for (set<string>::iterator i=obj.answers.begin();
       i != obj.answers.end(); ++i) {
    ret.push_back(*i);
  }
  return ret;
}




// [[Rcpp::export]]
CharacterVector SolveCountdown(IntegerVector x, int tgt,
                               bool findone, bool useup, bool positive) {
  TenSolver<Rational> obj(tgt);
  multiset< NumberWithExpr<Rational> > y;
  for (size_t i = 0; i < x.size(); i++) {
    Rational tmp = x[i];
    y.insert(NumberWithExpr<Rational>(tmp));
  }
  obj.solve(y, findone, useup, positive);

  CharacterVector ret;
  for (set<string>::iterator i=obj.best.second.begin();
       i != obj.best.second.end(); ++i) {
    ret.push_back(*i);
  }
  return ret;
}


// [[Rcpp::export]]
CharacterVector SolveCountdownInt(IntegerVector x, int tgt,
                               bool findone, bool useup, bool positive) {
  TenSolver<int> obj(tgt);
  multiset< NumberWithExpr<int> > y;
  for (size_t i = 0; i < x.size(); i++) {
    int tmp = x[i];
    y.insert(NumberWithExpr<int>(tmp));
  }
  obj.solve(y, findone, useup, positive);

  CharacterVector ret;
  for (set<string>::iterator i=obj.best.second.begin();
       i != obj.best.second.end(); ++i) {
    ret.push_back(*i);
  }
  return ret;
}

