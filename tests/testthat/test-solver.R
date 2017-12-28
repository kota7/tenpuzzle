library(testthat)
library(tenpuzzle)



test_that("solutions are correct", {
  # test automation helpers
  helper <- function(x, tgt) {
    inner <- function(x, tgt, findone, useup) {
      answers <- tenpuzzle(x, tgt, findone, useup)
      j <- 0
      for (a in answers) {
        j <- j + 1
        val <- eval(parse(text=a))
        msg <- sprintf("IN: ([%s], %d, %d, %d), OUT(%d): %s = 10 gets %f",
                       paste0(x, collapse=','), tgt, findone, useup, j, a, val)
        expect_equal(val, tgt, info=msg)
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

  #  edge cases
  helper(5, 5)
  helper(5, 7)


  # randomly generated cases
  set.seed(87)
  for (m in 1:20) {
    n <- sample(1:5)
  }

})
