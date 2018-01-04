#' Convert mathematical expression into reverse polish notation
#'
#' @param x character vector of mathematical expression
#' @param valueonly if \code{TRUE} only values are returned; otherwise
#' more information is returned
#' @return if \code{valueonly} is set, then a numeric vector of
#' calculation outcomes; otherwise, a list of four vectors of
#' the same size as the input:
#' \itemize{
#' \item{\code{value}: numeric vector of calculation outcomes}
#' \item{\code{intonly}: logical vector that
#' indicates that only integers appear in the intermediate steps}
#' \item{\code{nonzero}: logical vector that indicates that
#' zero does not appear in the intemediate steps}
#' \item{\code{nonnegative}: logical vector that indicates that
#' negative numbers do not appear in the intemediate steps}
#' }
#' @examples
#' eval_expr(c("1 + 2 + 3", "(4 - 1)*(-3 + 7) / 5", "(2*3 - 6)*(4 + 1/5)"))
#' @export
eval_expr <- function(expr, valueonly=FALSE) {
  ret <- EvaluateExpr(expr)
  if (valueonly) ret$value else ret
}
