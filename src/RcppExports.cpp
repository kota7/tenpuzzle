// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <Rcpp.h>

using namespace Rcpp;

// CleanParen
CharacterVector CleanParen(CharacterVector expr);
RcppExport SEXP _tenpuzzle_CleanParen(SEXP exprSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< CharacterVector >::type expr(exprSEXP);
    rcpp_result_gen = Rcpp::wrap(CleanParen(expr));
    return rcpp_result_gen;
END_RCPP
}
// test_rational
void test_rational();
RcppExport SEXP _tenpuzzle_test_rational() {
BEGIN_RCPP
    Rcpp::RNGScope rcpp_rngScope_gen;
    test_rational();
    return R_NilValue;
END_RCPP
}
// SolveTenPuzzle
CharacterVector SolveTenPuzzle(IntegerVector x, int tgt);
RcppExport SEXP _tenpuzzle_SolveTenPuzzle(SEXP xSEXP, SEXP tgtSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< IntegerVector >::type x(xSEXP);
    Rcpp::traits::input_parameter< int >::type tgt(tgtSEXP);
    rcpp_result_gen = Rcpp::wrap(SolveTenPuzzle(x, tgt));
    return rcpp_result_gen;
END_RCPP
}
// test_utils
void test_utils();
RcppExport SEXP _tenpuzzle_test_utils() {
BEGIN_RCPP
    Rcpp::RNGScope rcpp_rngScope_gen;
    test_utils();
    return R_NilValue;
END_RCPP
}

static const R_CallMethodDef CallEntries[] = {
    {"_tenpuzzle_CleanParen", (DL_FUNC) &_tenpuzzle_CleanParen, 1},
    {"_tenpuzzle_test_rational", (DL_FUNC) &_tenpuzzle_test_rational, 0},
    {"_tenpuzzle_SolveTenPuzzle", (DL_FUNC) &_tenpuzzle_SolveTenPuzzle, 2},
    {"_tenpuzzle_test_utils", (DL_FUNC) &_tenpuzzle_test_utils, 0},
    {NULL, NULL, 0}
};

RcppExport void R_init_tenpuzzle(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}