#' Ten Puzzle Game on Shiny
#'
#' @param ... Arguments passed to \code{\link[shiny]{runApp}}
#' @examples
#' tenpuzzle_app()
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

  tagList(
    # input numbers
    fluidRow(
      lapply(1:4, function(i) {
        column(2, textOutput(ns(paste0('in', i))))
      })
      ,column(1), column(2, textOutput(ns('target')))
    )
    ,textInput(ns('answer'), 'Your answer')
    ,actionButton(ns('submit'), 'Submit')
    ,actionButton(ns('impossible'), 'Impossible')
    ,actionButton(ns('giveup'), 'Give up')
    ,textOutput(ns('msgBox'))
  )
}

#' @rdname tenpuzzle_app
#' @export
tenpuzzle_app_srv <- function(input, output, session) {

  RV <- reactiveValues(
    input = NULL
    ,tgt  = NULL
    ,msg  = NULL
  )

  setQuestion <- function() {
    RV$input <- sample(1:9, 4, replace=TRUE)
    RV$tgt   <- 10
  }
  setQuestion()

  # submit button
  observeEvent(input$submit, {
    # check the answer
    ans <- input$answer
    res <- try(eval_expr(ans))
    err <- inherits(res, 'try-error')
    correct <- if (err) FALSE else (abs(res$value-RV$tgt) < 1e-5)

    ret <- if (err) sprintf('ERROR: %s could not be calculated', ans) else
           if (correct) sprintf('CORRECT!\n  %s = %d', ans, res$value) else
           sprintf('WRONG ANSER\n  %s = %.2f', ans, res$value)
    RV$msg <- ret
  })


  # show questions
  output$target <- renderText(RV$tgt)
  lapply(1:4, function(i) {
    output[[paste0('in', i)]] <- renderText(RV$input[i])
  })

  # show message
  output$msgBox <- renderText(RV$msg)
}
