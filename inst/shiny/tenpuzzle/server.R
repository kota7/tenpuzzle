library(shiny)
library(tenpuzzle)

generate_newquiz <- function(len=4, lb=1, ub=9) {
  while (TRUE) {
    x <- sample(lb:ub, size=len, replace=TRUE)
    if (length(tenpuzzle(x)) > 0) break
  }
  x
}


shinyServer(function(input, output, session) {
  RV <- reactiveValues(
    # current input numbers
    currentQuiz = c(1,2,3,4)

    # current result box
    ,resultMsg = ""
  )

  # when new button is clicked, make a new quiz randomly
  observeEvent(input$newBtn, {
    RV$currentQuiz <- generate_newquiz()
  })

  # when give up button is clicked, update the message to show in the result box
  observeEvent(input$giveupBtn, {
    x <- RV$currentQuiz
    if (!is.null(x)) {
      ans <- tenpuzzle(x)
      if (length(ans) == 0) {
        RV$resultMsg <- "no solution!"
      } else {
        RV$resultMsg <- sprintf("Possible answer:\n %s = 10", ans[1])
      }
    }
  })

  # when answer button is clicked,
  # evaluate the answer and update the result message
  observeEvent(input$answerBtn, {
    expr <- input$answer
    x <- RV$currentQuiz
    res <- validate_tenpuzzle(expr, x, tgt=10)[[1]]
    if (res) {
      RV$resultMsg <- sprintf("Yes, %s = 10!", expr)
    } else {
      RV$resultMsg <- sprintf("Hmm... %s", attr(res, "reason"))
    }
  })

  # show input numbers
  lapply(1:4, function(i) {
    oid <- paste0('inputNumber', i)
    output[[oid]] <- renderText({
      num <- RV$currentQuiz[i]
      if (is.null(num)) "" else num
    })
  })

  # result box message
  output$result <- renderText(RV$resultMsg)


  # show package version
  output$versionLabel <- renderText({
    # version equals the package version
    # this is useful to check the deployment
    paste('Version', packageVersion('tenpuzzle'))
  })
})

