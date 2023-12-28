const express = require('express')
const dotenv = require('dotenv')
const cors = require('cors')
const bodyParser = require('body-parser')

dotenv.config()

const port = process.env.PORT

const authorizationRoute = require('./routes/authorization')
const userRoute = require('./routes/user')
const sudokuRoute = require('./routes/sudoku')
const attemptRoute = require('./routes/attempt')

const app = express()

app.use(cors({exposedHeaders: 'Authorization'}))
app.use(bodyParser.json({limit: '50mb'}))
app.use(bodyParser.urlencoded({limit: "50mb", extended: true, parameterLimit: 50000}))

app.use('/authorization', authorizationRoute)
app.use('/user', userRoute)
app.use('/sudoku', sudokuRoute)
app.use('/attempt', attemptRoute)

app.get('/', (req, res) => {
    res.status(200).send('App recieved get request')
})

app.listen(port, () => {
    console.log(`App listening on port ${port}`)
})