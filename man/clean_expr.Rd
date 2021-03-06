% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/clean-paren.R
\name{clean_expr}
\alias{clean_expr}
\title{Clean up mathematical expressions}
\usage{
clean_expr(expr)
}
\arguments{
\item{expr}{a character vector of mathematical expressions}
}
\value{
character vector of cleaned expresisons
}
\description{
This function removes unnecessary parentheses and spaces
}
\examples{
clean_expr(c("(4 - 11) + (3 * 5)", "(1 - ((2) * (x))) + 8"))
clean_expr("((((100))))")
clean_expr("(((1 + 2 + 3 + 4 + 5)))")
}
