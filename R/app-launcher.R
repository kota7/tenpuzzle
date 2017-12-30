#' Ten Puzzle Game on Shiny
#'
#' @param ... Arguments passed to \code{\link[shiny]{runApp}}
#' @export
tenpuzzle_app <- function(...) {
  shiny::runApp(system.file("extdata/shiny/tenpuzzle/", package='tenpuzzle'),
                ...)
}


#' @import shiny
#' @rdname tenpuzzle_app
#' @export
tenpuzzle_app_ui <- function(id) {
  ns <- NS(id)

  textOutput(ns('msgBox'))
}

#' @rdname tenpuzzle_app
#' @export
tenpuzzle_app_srv <- function(input, output, session) {
  output$msgBox <- renderText({
    "hoge"
  })
}
