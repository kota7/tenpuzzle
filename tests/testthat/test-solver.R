library(testthat)
library(tenpuzzle)
library(magrittr)


test_that("solutions are correct", {
  # test automation helpers
  helper <- function(x, tgt) {
    inner <- function(x, tgt, findone, useup) {
      answers <- tenpuzzle(x, tgt, findone, useup)
      if (length(answers) > 0) {
        values  <- sapply(answers, function(a) eval(parse(text=a))) %>% unname()
        msg <- sprintf("IN: ([%s], %d, %d, %d)",
                       paste0(x, collapse=','), tgt, findone, useup)
        expect_equal(values, rep(tgt, length(answers)), info=msg)
      }
    }

    inner(x, tgt, TRUE, TRUE)
    inner(x, tgt, TRUE, FALSE)
    inner(x, tgt, FALSE, TRUE)
    inner(x, tgt, FALSE, FALSE)
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
  set.seed(87)
  for (m in 1:20) {
    n <- sample(1:4, 1)
    x <- sample((-9):9, n, replace=TRUE)
    tgt <- sample((-20):20, 1)
    helper(x, tgt)
  }
  for (m in 1:3) {
    x <- sample(1:9, 5, replace=TRUE)
    tgt <- sample(1:20, 1)
    helper(x, tgt)
  }

})



test_that("brute force produces same results as findone=FALSE, useup=TRUE", {

  helper <- function(x, tgt) {
    a1 <- tenpuzzle(x, tgt, findone=FALSE, useup=TRUE)
    a2 <- tenpuzzle_bf(x, tgt)
    # normalize the strings for comparison
    a1 <- sort(gsub(' ', '', a1))
    a2 <- sort(gsub(' ', '', a2))
    msg <- sprintf("IN: ([%s], %d)", paste0(x, collapse=','), tgt)
    expect_equal(a1, a2, info=msg)
  }

  helper(c(1, 1, 9, 9), 10)
  helper(c(4, 4, -4, 1), 5)
  helper(c(-5, 7, 9), -10)
})
