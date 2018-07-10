
<!-- README.md is generated from README.Rmd. Please edit that file -->
tenpuzzle
=========

`tenpuzzle` provides a solver for ten puzzle quiz, a game that makes 10 from given numbers by arithmetic calculation. Target numbers other than 10 are supported.

Installation
------------

You can install `tenpuzzle` from github with:

``` r
# install.packages("devtools")
devtools::install_github("kota7/tenpuzzle")
```

Example
-------

The function `tenpuzzle` solves the quiz. The return value is string expression that makes the target number. An empty vector is returned if no such expression exists.

``` r
library(tenpuzzle)
tenpuzzle(c(1, 1, 9, 9), 10)
#> [1] "(1 / 9 + 1) * 9"
```

The function `countdown` solves the "Number Quiz" from the TV show "Countdown". The return value is a pair of formulas and values that makes the closest number to the target.

``` r
countdown(c(75, 50, 2, 3, 8, 7), 812)
#> $formula
#> [1] "50 * (7 + 75) / (2 + 3) - 8"
#> 
#> $value
#> [1] 812
```

Note on the Complexity
----------------------

The solver algorithm is not efficient.
It may not finish in reasonable time for input of length six or longer.
