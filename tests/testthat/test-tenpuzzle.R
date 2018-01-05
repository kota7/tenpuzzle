library(testthat)
library(tenpuzzle)
library(magrittr)


test_that("tenpuzzle solver is correct", {
  # test automation helpers
  helper <- function(x, tgt) {
    inner <- function(x, tgt, findone, useall, intonly, nonnegative, nonzero) {

      # illegal input should cause error
      if (nonnegative && any(x < 0)) {
        expect_error(tenpuzzle(x, tgt, findone, useall, intonly, nonnegative, nonzero))
        return()
      }
      if (nonzero && any(x == 0)) {
        expect_error(tenpuzzle(x, tgt, findone, useall, intonly, nonnegative, nonzero))
        return()
      }

      answers <- tenpuzzle(x, tgt, findone, useall, intonly, nonnegative, nonzero)
      if (length(answers) > 0) {
        values  <- sapply(answers, function(a) eval(parse(text=a))) %>% unname()
        msg <- sprintf("IN: ([%s], %d, %d, %d, %d, %d, %d)",
                       paste0(x, collapse=','), tgt,
                       findone, useall, intonly, nonnegative, nonzero)
        expect_equal(values, rep(tgt, length(answers)), info=msg)
      }
      # test for options
      msg <- sprintf("IN: ([%s], %d, %d, %d, %d, %d, %d)",
                     paste0(x, collapse=','), tgt,
                     findone, useall, intonly, nonnegative, nonzero)
      res <- eval_expr(answers)
      if (intonly)     expect_true(all(res$intonly),     info=msg)
      if (nonnegative) expect_true(all(res$nonnegative), info=msg)
      if (nonzero)     expect_true(all(res$nonzero),     info=msg)
    }

    for (a1 in c(TRUE)) {  # findone is tested in another test
      for (a2 in c(TRUE, FALSE)) {
        for (a3 in c(TRUE, FALSE)) {
          for (a4 in c(TRUE, FALSE)) {
            for (a5 in c(TRUE, FALSE)) {
              inner(x, tgt, a1, a2, a3, a4, a5)
            }
          }
        }
      }
    }
  }

  # basic cases
  helper(c(1, 1, 9, 9), 10)
  helper(c(1, 1, 5, 8), 10)
  helper(c(8, 8, 8, 9), 10)

  helper(c(2, 6), 3)
  helper(c(3, 1, 5), 8)
  helper(c(1, 1, 5, 9), 4)
  helper(c(8, 1, 5, 4, 7), 100)

  # edge cases
  helper(5, 5)
  helper(5, 7)


  # randomly generated cases
  set.seed(123)
  for (m in 1:20) {
    n <- sample(1:4, 1)
    x <- sample((-20):20, n, replace=TRUE)
    tgt <- sample((-20):20, 1)
    helper(x, tgt)
  }
  for (m in 1:3) {
    x <- sample(1:9, 5, replace=TRUE)
    tgt <- sample(1:20, 1)
    helper(x, tgt)
  }

})



test_that("brute force produces same results as findone=FALSE, useall=TRUE", {

  helper <- function(x, tgt) {
    a1 <- tenpuzzle(x, tgt, findone=FALSE, useall=TRUE)
    a2 <- tenpuzzle_bf(x, tgt)
    # normalize the strings for comparison
    a1 <- sort(gsub(' ', '', a1))
    a2 <- sort(gsub(' ', '', a2))
    d <- setdiff(a2, a1)
    msg <- sprintf("IN: ([%s], %d): diff {%s}",
                   paste0(x, collapse=','), tgt, paste0(d, collapse="; "))
    expect_equal(a1, a2, info=msg)
  }

  helper(c(1, 1, 9, 9), 10)
  helper(c(4, 4, -4, 1), 5)
  helper(c(-6, 2, 9), -3)

  # randomly generated cases
  # note: input with 5 numbers takes too long time for brute force solver
  set.seed(123)
  for (m in 1:20) {
    n <- sample(1:3, 1)
    x <- sample((-20):20, n, replace=TRUE)
    tgt <- sample((-20):20, 1)
    helper(x, tgt)
  }
  for (m in 1:3) {
    n <- 4
    x <- sample((-20):20, n, replace=TRUE)
    tgt <- sample((-20):20, 1)
    helper(x, tgt)
  }

})
