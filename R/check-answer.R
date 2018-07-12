#' Check if an answer is a valid solution to a ten puzzle
#'
#' @param expr character of mathematical expression
#' @param x   input integers
#' @param tgt target number
#' @param useall   if \code{TRUE}, requires all numbers are used;
#'                 otherwise some number may remain unused
#' @param intonly  if \code{TRUE}, requires all numbers are integers in
#'                 every step of calculation
#' @param nonnegative if \code{TRUE}, requires all numbers are nonnegative in
#'                    every step of calculation
#' @param nonzero     if \code{TRUE}, requires all numbers are not zero in
#'                    every step of calculation
#'
#' @return A list of logical, with "reason" attribute for FALSE case
#' @export
#'
#' @examples
#' validate_tenpuzzle("1+2+3+4", x=c(1,2,3,4))
#' validate_tenpuzzle(c("2*4+3-1", "3*4+1-2"), x=c(1,2,3,4))
#' validate_tenpuzzle(c("3*4-2", '(3-1)*2+4+2'), x=c(1,2,3,4))
#' validate_tenpuzzle(c("4/2*3", '3/2*4'), x=c(2,3,4), tgt=6, intonly=TRUE)
validate_tenpuzzle <- function(expr, x, tgt = 10,
                            useall = TRUE, intonly = FALSE,
                            nonnegative = FALSE, nonzero = FALSE) {
  lapply(expr, validate_tenpuzzle_single, x=x, tgt=tgt,
         useall=useall, intonly=intonly,
         nonnegative=nonnegative, nonzero=nonzero)
}


#' @rdname validate_tenpuzzle
#' @export
validate_tenpuzzle_single <- function(expr, x, tgt = 10,
                                   useall = TRUE, intonly = FALSE,
                                   nonnegative = FALSE, nonzero = FALSE) {

  stopifnot(length(expr) == 1)

  # number usage check
  numbers <- stringr::str_extract_all(expr, "[0-9]+") %>%
    unlist() %>% as.integer()
  if (useall) {
    # requires that used numbers match exactly
    tbl1 <- table(x)
    tbl2 <- table(numbers)
    if (length(tbl1) != length(tbl2) ||
        any(tbl1 != tbl2) ||
        any(names(tbl1) != names(tbl2))) {
      ret <- FALSE
      attr(ret, "reason") <- "numbers mismatch"
      return(ret)
    }
  } else {
    # requires that numbers are subset of x
    tbl1 <- as.data.frame(table(x)) %>% setNames(c("n", "input"))
    tbl2 <- as.data.frame(table(numbers)) %>% setNames(c("n", "ans"))
    tbl <- merge(tbl1, tbl2, all.y=TRUE, by="n")
    tbl$input[is.na(tbl$input)] <- 0
    tbl$diff <- tbl$ans - tbl$input
    if (any(tbl$diff < 0)) {
      ret <- FALSE
      attr(ret, "reason") <- "numbers not subset"
      return(ret)
    }
  }

  # evaluate
  res <- tryCatch(eval_expr(expr), error=function(err) err)
  if (inherits(res, "error")) {
    ret <- FALSE
    attr(ret, "reason") <- sprintf("invalid expr: %s", res$message)
    return(ret)
  }


  # check the result
  if (res$value != tgt) {
    return(structure(
      FALSE, reason=sprintf("value mismatch: %s", res$value)
    ))
  }

  if (intonly && !res$intonly) {
    return(structure(
      FALSE, reason="violate int-only requirement"
    ))
  }

  if (nonnegative && !res$nonnegative) {
    return(structure(
      FALSE, reason="violate nonnegative requirement"
    ))
  }

  if (nonzero && !res$nonzero) {
    return(structure(
      FALSE, reason="violate nonzero requirement"
    ))
  }

  return(TRUE)
}






