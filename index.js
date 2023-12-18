const express = require('express')
const dotenv = require('dotenv')
const cors = require('cors')
const bodyParser = require('body-parser')
const fs = require('fs')

dotenv.config()

const port = process.env.PORT

const authorizationRoute = require('./routes/authorization')
const userRoute = require('./routes/user')
const sudokuRoute = require('./routes/sudoku')
const attemptRoute = require('./routes/attempt')

const app = express()

app.use(cors({exposedHeaders: 'Authorization'}))
app.use(bodyParser.json())

app.use('/authorization', authorizationRoute)
app.use('/user', userRoute)
app.use('/sudoku', sudokuRoute)
app.use('/attempt', attemptRoute)

app.get('/', (req, res) => {
    res.status(200).send('App recieved get request')
})

app.get('/files', (req, res) => {
    fs.readdir('./', (err, files) => {
        files.forEach(file => {
            console.log(file);
        })
    })

    res.status(200).send('App recieved get reuqest on files')
})

app.listen(port, () => {
    console.log(`App listening on port ${port}`)
})