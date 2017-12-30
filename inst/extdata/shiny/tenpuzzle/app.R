library(shiny)
library(tenpuzzle)


appid <- 'tenpuzzle'

ui <- fluidPage(tenpuzzle_app_ui(appid))


server <- function(input, output, session) {
  callModule(tenpuzzle_app_srv, appid)
}


shinyApp(ui, server)
