library(testthat)
library(tenpuzzle)
library(magrittr)

test_that("10 puzzle check function works as expected", {
  expect_true(
    validate_tenpuzzle_single("1+2+3+4", x=c(1,2,3,4), tgt=10)
  )

  # must use all numbers
  expect_false(
    validate_tenpuzzle_single("(1+4)*2", x=c(1,2,3,4), tgt=10)
  )
  # no need to use all numbers
  expect_true(
    validate_tenpuzzle_single("(1+4)*2", x=c(1,2,3,4), tgt=10, useall=FALSE)
  )
  # must not add number
  expect_false(
    validate_tenpuzzle_single("(1+1)*(2+3)", x=c(1,2,3), tgt=10)
  )
  expect_false(
    validate_tenpuzzle_single("1+1+2+3", x=c(1,2,3), tgt=7)
  )

  # wrong answer
  expect_false(
    validate_tenpuzzle_single("(3*4)-2+1", x=c(1,2,3,4), tgt=10)
  )

  # int only requirement
  expect_true(
    validate_tenpuzzle_single("4/2*3", x=c(2,3,4), tgt=6, intonly=TRUE)
  )
  expect_false(
    validate_tenpuzzle_single("3/2*4", x=c(2,3,4), tgt=6, intonly=TRUE)
  )
  expect_true(
    validate_tenpuzzle_single("3/2*4", x=c(2,3,4), tgt=6, intonly=FALSE)
  )
  expect_false(
    validate_tenpuzzle_single("(1/9+1)*9", x=c(1,1,9,9), tgt=10, intonly=TRUE)
  )
  expect_true(
    validate_tenpuzzle_single("(1/9+1)*9", x=c(1,1,9,9), tgt=10, intonly=FALSE)
  )

  # nonzero requirement
  expect_false(
    validate_tenpuzzle_single("1-1+2*5", x=c(1,2,1,5), tgt=10, nonzero=TRUE)
  )
  expect_true(
    validate_tenpuzzle_single("2*5+1-1", x=c(1,2,1,5), tgt=10, nonzero=TRUE)
  )
  expect_false(
    validate_tenpuzzle_single("2*5+(1-1)", x=c(1,2,1,5), tgt=10, nonzero=TRUE)
  )

  # nonnegative requirement
  expect_false(
    validate_tenpuzzle_single("9-(7-8)", x=c(7,8,9), tgt=10, nonnegative=TRUE)
  )
  expect_true(
    validate_tenpuzzle_single("9-(7-8)", x=c(7,8,9), tgt=10, nonnegative=FALSE)
  )

})
