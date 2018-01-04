#' Solve Countdown's Number Quiz
#'
#' @param x   an integer vector
#' @param tgt an integer of target
#' @param findone  if \code{TRUE}, search for an answer;
#'                 otherwise search exhaustively
#' @param useup    if \code{TRUE}, requires all numbers are used;
#'                 otherwise some number may remain unused
#' @param intonly  if \code{TRUE}, requires all numbers are integers in
#'                 every step of calculation; otherwise fractions may appear
#'                 in interim steps
#' @param nonnegative if \code{TRUE}, requires all numbers are nonnegative in
#'                    every step of calculation
#' @param nonzero     if \code{TRUE}, requires all numbers are not zero in
#'                    every step of calculation
#'
#' @return a list of character vector of best possible answers and the values.
#'         if \code{findone} is selected and an exact match is found, then
#'         only one answer is returned.  If no exact match is found, then
#'         all closest possible solutions are returned.
#' @export
#' @examples
#' countdown(c(75, 50, 2, 3, 8, 7), 812)
#' countdown(c(10, 5, 1, 7, 12, 62), 130)
#' countdown(c(8, 4, 3, 8, 87, 12), 724)
countdown <- function(x, tgt, findone=TRUE, useup=FALSE,
                      intonly=TRUE, nonnegative=TRUE, nonzero=TRUE) {
  expr <- if (intonly) {
    SolveCountdownInt(x, tgt, findone, useup, nonnegative, nonzero) %>%
      clean_expr() %>% unique()
  } else {
    SolveCountdown(x, tgt, findone, useup, nonnegative, nonzero) %>%
      clean_expr() %>% unique()
  }

  values <- sapply(expr, function(a) eval(parse(text=a))) %>% unname()
  list(formula=expr, value=values)
}
