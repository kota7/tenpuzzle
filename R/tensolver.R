#' Ten puzzle solver
#'
#' @param x   an integer vector
#' @param tgt an integer of target
#'
#' @return a character vector of answers
#' @export
#'
#' @examples
#' \dontrun{
#' tensolve(c(1, 1, 9, 9), 10)
#' }
tensolve <- function(x, tgt=10) {
  ret <- SolveTenPuzzle(x, tgt) %>% clean_expr() %>% unique()
  ret
}
