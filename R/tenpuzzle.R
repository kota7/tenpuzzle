#' Ten puzzle solver
#'
#' @param x   an integer vector
#' @param tgt an integer of target
#' @param findone  if \code{TRUE}, search for an answer;
#'                 otherwise search exhaustively
#' @param useall   if \code{TRUE}, requires all numbers are used;
#'                 otherwise some number may remain unused
#' @param intonly  if \code{TRUE}, requires all numbers are integers in
#'                 every step of calculation
#' @param nonnegative if \code{TRUE}, requires all numbers are nonnegative in
#'                    every step of calculation
#' @param nonzero     if \code{TRUE}, requires all numbers are not zero in
#'                    every step of calculation
#'
#' @return a character vector of answers
#' @export
#'
#' @examples
#' tenpuzzle(c(1, 1, 9, 9), 10)
#' tenpuzzle(c(1, 1, 9, 9), 10, findone=FALSE)
#' tenpuzzle(c(1, 1, 9, 9), 10, useall=FALSE)
#'
#' # integer only
#' tenpuzzle(c(2, 6, 3), 9, findone=FALSE, intonly=FALSE)
#' tenpuzzle(c(2, 6, 3), 9, findone=FALSE, intonly=TRUE)
tenpuzzle <- function(x, tgt=10, findone=TRUE, useall=TRUE,
                      intonly=FALSE, nonnegative=FALSE, nonzero=FALSE) {
  if (length(x) == 0) stop("empty input")

  ans <- SolveTenPuzzle(x, tgt, findone, useall,
                        intonly, nonnegative, nonzero) %>%
    clean_expr() %>% unique()
  # solver returns the `best` possible answer, hence must not be empty
  stopifnot(length(ans) > 0)
  # check the value and if the result is close enough to the target,
  # then return it; otherwise there is no answer
  v <- EvaluateExpr(ans[1])$value
  if (abs(v - tgt) < 1e-5) ans else character(0)
}




#' Solve Ten Puzzle by Brute Force
#'
#' @param x   an integer vector
#' @param tgt an integer of target
#'
#' @return a character vector of all possible answers
#'
#' @examples
#' tenpuzzle_bf(c(1, 1, 9, 9), 10)
#' @export
tenpuzzle_bf <- function(x, tgt=10) {

  # number of input integers
  n <- length(x)

  # edge cases
  if (n < 1) stop('no input')
  if (n == 1) {
    if (x == tgt) return(as.character(tgt))
    else return(character(0))
  }


  # possible operations
  #   there are n-1 operations
  #   each is either +, -, *, or /
  ops <- lapply(1:(n-1), function(i) c('+', '-', '*', '/'))
  names(ops) <- paste0('op', 1:(n-1))
  ops_dat <- do.call('expand.grid', ops)

  # possible parentheses
  #   there are n+1 positions for parentheses
  #   we consider all combinations such that
  #   the difference is larger than one and less than n
  pos <- combinat::combn(n+1, 2)-1
  dif <- pos[2,] - pos[1,]
  pos <- pos[, (dif > 1) & (dif < n)]
  pos <- apply(pos, 2, paste0, collapse=',')
  pos <- paste0('paren', pos)
  paren <- lapply(pos, function(p) c(TRUE, FALSE))
  names(paren) <- pos
  paren_dat <- do.call('expand.grid', paren)
  # then, compute the number of parentheses by positions
  for (i in 0:n) {
    open_ct <- {
      cols <- grep(sprintf('paren%d,', i), names(paren_dat))
      rowSums(paren_dat[, cols, drop=FALSE])
    }
    close_ct <- {
      cols <- grep(sprintf('paren[0-9]+,%d', i), names(paren_dat))
      rowSums(paren_dat[, cols, drop=FALSE])
    }

    paren_dat[[paste0('open', i)]]  <- open_ct
    paren_dat[[paste0('close', i)]] <- close_ct
  }
  # now we only need open/close counts
  paren_dat <- dplyr::select(paren_dat,
                             dplyr::starts_with('open'),
                             dplyr::starts_with('close'))
  # remove redundant parentheses
  # having both open_i and close_{i+1} are redundant
  for (i in 1:n) {
    r <- pmin(paren_dat[[paste0('open', i-1)]],
              paren_dat[[paste0('close', i)]])
    paren_dat[[paste0('open', i-1)]] <- paren_dat[[paste0('open', i-1)]] - r
    paren_dat[[paste0('close', i)]] <- paren_dat[[paste0('close', i)]] - r
  }
  # can be more parentheses removal
  # remove duplicates
  paren_dat <- dplyr::distinct(paren_dat)


  # possible permutations
  # surround numbers by parenthesis to make it robust to negative numbers
  perms <- unique(combinat::permn(paste0('(', x, ')')))
  perms_dat <- as.data.frame(matrix(unlist(perms), ncol=n, byrow=TRUE))
  names(perms_dat) <- paste0('num', 1:n)



  # combine them all and make sure all rows are distinct
  perms_dat$tmp <- 1
  ops_dat$tmp   <- 1
  paren_dat$tmp <- 1
  dat <- dplyr::inner_join(perms_dat, ops_dat, by='tmp') %>%
    dplyr::inner_join(paren_dat, by='tmp') %>%
    dplyr::select_(~ -tmp) %>%
    dplyr::distinct()


  # make expression
  makeParen <- function(char, counts) {
    lapply(counts, function(m) paste0(rep(char, m), collapse='')) %>%
      unlist()
  }
  expr <- paste(
    makeParen('(', dat$open0),
    dat$num1,
    makeParen(')', dat$close1)
  )

  for (i in 2:n) {
    expr <- paste(
      expr,
      dat[[paste0('op', i-1)]],
      makeParen('(', dat[[paste0('open', i-1)]]),
      dat[[paste0('num', i)]],
      makeParen(')', dat[[paste0('close', i)]])
    )
  }

  # remove redundant parentheses and spaces
  # and remove duplicates
  expr <- clean_expr(expr)
  expr <- unique(expr)

  # compute value of expression, then
  # return the expressions sufficiently close to the target
  res <- lapply(expr, function(txt) eval(parse(text=txt))) %>% unlist()
  flg <- abs(res-tgt)/abs(tgt + 1e-6) < 1e-6
  expr[which(flg)]
}
