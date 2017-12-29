// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <Rcpp.h>

using namespace Rcpp;

// SolveTenPuzzle
CharacterVector SolveTenPuzzle(IntegerVector x, int tgt, bool findone, bool useup);
RcppExport SEXP _tenpuzzle_SolveTenPuzzle(SEXP xSEXP, SEXP tgtSEXP, SEXP findoneSEXP, SEXP useupSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< IntegerVector >::type x(xSEXP);
    Rcpp::traits::input_parameter< int >::type tgt(tgtSEXP);
    Rcpp::traits::input_parameter< bool >::type findone(findoneSEXP);
    Rcpp::traits::input_parameter< bool >::type useup(useupSEXP);
    rcpp_result_gen = Rcpp::wrap(SolveTenPuzzle(x, tgt, findone, useup));
    return rcpp_result_gen;
END_RCPP
}
// SolveTenPuzzleInt
CharacterVector SolveTenPuzzleInt(IntegerVector x, int tgt, bool findone, bool useup);
RcppExport SEXP _tenpuzzle_SolveTenPuzzleInt(SEXP xSEXP, SEXP tgtSEXP, SEXP findoneSEXP, SEXP useupSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< IntegerVector >::type x(xSEXP);
    Rcpp::traits::input_parameter< int >::type tgt(tgtSEXP);
    Rcpp::traits::input_parameter< bool >::type findone(findoneSEXP);
    Rcpp::traits::input_parameter< bool >::type useup(useupSEXP);
    rcpp_result_gen = Rcpp::wrap(SolveTenPuzzleInt(x, tgt, findone, useup));
    return rcpp_result_gen;
END_RCPP
}
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
// test_utils
void test_utils();
RcppExport SEXP _tenpuzzle_test_utils() {
BEGIN_RCPP
    Rcpp::RNGScope rcpp_rngScope_gen;
    test_utils();
    return R_NilValue;
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
// test_reduction
void test_reduction();
RcppExport SEXP _tenpuzzle_test_reduction() {
BEGIN_RCPP
    Rcpp::RNGScope rcpp_rngScope_gen;
    test_reduction();
    return R_NilValue;
END_RCPP
}
// test_hash
void test_hash();
RcppExport SEXP _tenpuzzle_test_hash() {
BEGIN_RCPP
    Rcpp::RNGScope rcpp_rngScope_gen;
    test_hash();
    return R_NilValue;
END_RCPP
}

static const R_CallMethodDef CallEntries[] = {
    {"_tenpuzzle_SolveTenPuzzle", (DL_FUNC) &_tenpuzzle_SolveTenPuzzle, 4},
    {"_tenpuzzle_SolveTenPuzzleInt", (DL_FUNC) &_tenpuzzle_SolveTenPuzzleInt, 4},
    {"_tenpuzzle_CleanParen", (DL_FUNC) &_tenpuzzle_CleanParen, 1},
    {"_tenpuzzle_test_utils", (DL_FUNC) &_tenpuzzle_test_utils, 0},
    {"_tenpuzzle_test_rational", (DL_FUNC) &_tenpuzzle_test_rational, 0},
    {"_tenpuzzle_test_reduction", (DL_FUNC) &_tenpuzzle_test_reduction, 0},
    {"_tenpuzzle_test_hash", (DL_FUNC) &_tenpuzzle_test_hash, 0},
    {NULL, NULL, 0}
};

RcppExport void R_init_tenpuzzle(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
