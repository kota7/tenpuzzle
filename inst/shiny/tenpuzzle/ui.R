library(shiny)

shinyUI(fluidPage(

  tags$head(
    tags$link(rel="stylesheet", type="text/css", href="tenpuzzle.css")
  )

  ,titlePanel("10 PUZZLE")
  ,sidebarLayout(
    sidebarPanel(
      p("Make 10 using the four given numbers with arithmetic calculation!")
    )

    ,mainPanel(
      # show numbers
      fluidRow(
        lapply(1:4, function(i) {
          column(
            tagAppendAttributes(textOutput(paste0('inputNumber', i)),
                                class='inputNumber'), width=2
          )
        })
      )

      ,textInput('answer', 'Answer', placeholder='Ex. 1 + 2 + 3 + 4')

      ,fluidRow(
        column(actionButton('answerBtn', 'Go!'), width=3)
        ,column(actionButton('giveupBtn', 'Give Up'), width=3)
        ,column(actionButton('newBtn', 'New'), width=3)
      )
      ,verbatimTextOutput('result')
    )
  )
))
