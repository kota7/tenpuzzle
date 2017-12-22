#' Clean up mathematical expressions
#'
#' This function removes unnecessary parentheses and spaces
#'
#' @param expr a character vector of mathematical expressions
#' @return character vector of cleaned expresisons
#'
#' @export
#' @examples
#' clean_expr(c("(4 - 11) + (3 * 5)", "(1 - ((2) * (x))) + 8"))
#' clean_expr("((((100))))")
#' clean_expr("(((1 + 2 + 3 + 4 + 5)))")
clean_expr <- function(expr) {
  ret <- CleanParen(expr)
  ret <- gsub(' {2,}', ' ', ret)
  ret <- gsub('\\( ', '(', ret)
  ret <- gsub(' \\)', ')', ret)
  ret <- sub('^ +', '', ret)
  ret <- sub(' +$', '', ret)
  ret
}
