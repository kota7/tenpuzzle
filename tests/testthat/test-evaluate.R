library(testthat)
library(tenpuzzle)
library(magrittr)


test_that("eval_expr produces sane value as eval + parse", {

  # NOTE: there is a known case where eval_exor and eval+parse produce
  #       different results:
  #       "1 / (2 / 0)"
  #         eval_expr produces "divisioin by zero" error
  #         eval+parse produces 0

  helper <- function(expr) {
    val1 <- sapply(expr, function(a) eval(parse(text=a))) %>% unname()
    flg <- is.na(val1) | is.infinite(val1)

    # error cases
    if (any(flg)) {
      msg <- paste0(expr[flg], collapse='; ')
      expect_error(eval_expr(expr[flg]), info=msg)
    }

    # value cases
    if (!all(flg)) {
      msg <- paste0(expr[!flg], collapse='; ')
      val2 <- eval_expr(expr[!flg], valueonly=TRUE)
      expect_true(all(abs(val1[!flg] - val2) < 1e-5), info=msg)
    }
  }

  expr <- c("1 + 2 + 3",
            "(4 - 1)*(-3 + 7) / 5",
            "5 - (4/6 + 9)",
            "5 - (2 - 1 * (-3))",
            "0 / 0",
            "10 / 0",
            "-5 / 0",
            "(1 / 0) * (-4 / 0)",
            "(((6)))")
  helper(expr)

})



test_that("intonly, nonzero, nonnegtive", {

  res <- eval_expr("1 + 2 + 3")
  expect_true(res$nonzero)
  expect_true(res$nonnegative)
  expect_true(res$intonly)

  res <- eval_expr("1 - 2 + 3")
  expect_true(res$nonzero)
  expect_false(res$nonnegative)
  expect_true(res$intonly)

  res <- eval_expr("1 / 2 + 3")
  expect_true(res$nonzero)
  expect_true(res$nonnegative)
  expect_false(res$intonly)

  res <- eval_expr("1 + 2 - 3")
  expect_false(res$nonzero)
  expect_true(res$nonnegative)
  expect_true(res$intonly)

  res <- eval_expr("1 + 2 + (- 3)")
  expect_false(res$nonzero)
  expect_false(res$nonnegative)
  expect_true(res$intonly)

  res <- eval_expr("0")
  expect_false(res$nonzero)
  expect_true(res$nonnegative)
  expect_true(res$intonly)


  set.seed(123)
  n1 <- sample(-20:20, 1000, replace=TRUE)
  n2 <- sample(setdiff(-20:20, 0), 1000, replace=TRUE)
  s1 <- as.character(n1)
  s2 <- as.character(n2)
  s1[n1 < 0] <- sprintf("(%s)", s1[n1<0])
  s2[n2 < 0] <- sprintf("(%s)", s2[n2<0])

  # into only test
  expr <- paste(s1, s2, sep='/')
  msg <- sprintf("intonly w/ %s", paste0(expr, collapse='; '))
  res <- eval_expr(expr)
  mod0 <- (n1 %% n2 == 0)
  expect_equal(mod0, res$intonly, info=msg)


  # nonnegative test
  n1 <- sample(-20:20, 1000, replace=TRUE)
  n2 <- sample(-20:20, 1000, replace=TRUE)
  s1 <- as.character(n1)
  s2 <- as.character(n2)
  s1[n1 < 0] <- sprintf("(%s)", s1[n1<0])
  s2[n2 < 0] <- sprintf("(%s)", s2[n2<0])
  expr <- paste(s1, s2, sep='-')
  msg <- sprintf("nonegative w/ %s", paste0(expr, collapse='; '))
  res <- eval_expr(expr)
  nonneg <- (n1 >= n2) & (n1 >= 0) & (n2 >= 0)
  expect_equal(nonneg, res$nonnegative, info=msg)


  # nonzero test
  n1 <- sample(-20:20, 1000, replace=TRUE)
  n2 <- sample(-20:20, 1000, replace=TRUE)
  s1 <- as.character(n1)
  s2 <- as.character(n2)
  s1[n1 < 0] <- sprintf("(%s)", s1[n1<0])
  s2[n2 < 0] <- sprintf("(%s)", s2[n2<0])
  expr <- paste(s1, s2, sep='-')
  msg <- sprintf("nonzero w/ %s", paste0(expr, collapse='; '))
  res <- eval_expr(expr)
  nonzero <- (n1 != n2) & (n1 != 0) & (n2 != 0)
  expect_equal(nonzero, res$nonzero, info=msg)
})
