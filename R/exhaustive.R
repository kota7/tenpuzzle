#' Solve Ten Puzzle by Brute Force
#'
#' @param x   an integer vector
#' @param tgt an integer of target
#'
#' @return a character vector of all possible answers
#'
#' @examples
#' \dontrun{
#' tenpuzzle_exhaustive(c(1, 1, 9, 9), 10)
#' }
#' @export
tenpuzzle_exhaustive <- function(x, tgt=10) {

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
  pos <- pos[, (dif > 1) & (dif < 4)]
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
  # now we only need open/close counts, and remove duplicates
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
  perms <- unique(combinat::permn(x))
  perms_dat <- as.data.frame(matrix(unlist(perms), ncol=4, byrow=TRUE))
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

  # remove redundant spaces,
  # and remove duplicates
  expr <- sub('^ +', '', expr)
  expr <- sub(' +$', '', expr)
  expr <- gsub(' {2,}', ' ', expr)
  expr <- unique(expr)

  # compute value, and
  # return the expressions sufficiently close to the target
  res <- lapply(expr, function(txt) eval(parse(text=txt))) %>% unlist()
  flg <- abs(res-tgt)/abs(tgt + 1e-6) < 1e-6
  expr[which(flg)]
}
