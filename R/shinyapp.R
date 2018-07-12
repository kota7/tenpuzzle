#' Ten Puzzle Game on Shiny
#'
#' @param ... Arguments passed to \code{\link[shiny]{runApp}}
#' @examples
#' \dontrun{
#' tenpuzzle_app()
#' }
#' @export
tenpuzzle_app <- function(...) {
  shiny::runApp(system.file("shiny/tenpuzzle/", package='tenpuzzle'), ...)
}


