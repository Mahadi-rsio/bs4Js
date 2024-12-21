const { BeautifulSoup } = require('./../build/Release/api.node')
const fs = require('fs')

const parser = BeautifulSoup()


parser.InitBs4('<title>BeautifulSoup</title><p>hello world<span></span><img></img><h1></h1><svg></svg> </p>')

//console.log(parser.Prettify())

//console.log(parser.GetTitle())

parser.Table()

console.log(parser)
