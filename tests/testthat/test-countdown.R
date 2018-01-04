library(testthat)
library(tenpuzzle)
library(magrittr)


test_that("countdown solvers are correct", {
  helper <- function(x, tgt) {
    inner <- function(x, tgt, findone, useup, intonly, nonnegative, nonzero) {
      a1 <- countdown(x, tgt, findone, useup, intonly, nonnegative, nonzero)
      a2 <- tenpuzzle(x, tgt, findone, useup, intonly, nonnegative, nonzero)

      # if a2 is non-empty, then a1's value matches target exactly
      # if a2 is empty, then a1's values does not match the target exactly
      msg <- sprintf("IN: [%s], %f, %d, %d, %d, %d, %d | matched: %d",
                     paste0(x, collapse=','), tgt,
                     findone, useup, intonly, nonnegative, nonzero, length(a2)>0)
      if (length(a2) == 0) {
        expect_true(all(a1$value != tgt), info=msg)
      } else {
        expect_true(all(a1$value == tgt), info=msg)
      }
    }

    for (a1 in c(TRUE)) {
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

  helper(c(1, 1, 9, 9), 10)
  helper(c(4, 3, 7, 15, 4), 80)
  helper(c(75, 50, 2, 3, 8, 7), 812)

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
