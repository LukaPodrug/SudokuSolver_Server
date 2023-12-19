const express = require('express')
const dotenv = require('dotenv')
const cors = require('cors')
const bodyParser = require('body-parser')
const { family, GLIBC, MUSL } = require('detect-libc')
const { version } = require('detect-libc')

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

app.get('/lib', async (req, res) => {
    switch (await family()) {
        case GLIBC: 
            console.log("glibc")
            res.status(200).send('glibc')
            break
        case MUSL:
            console.log("musl")
            res.status(200).send('musl')
            break
        case null:
            console.log("lib not found")
            res.status(200).send('lib not found')
            break
    }
})

app.get('/version', async (req, res) => {
    const version2 = await version()
    if (version2) {
        const [major, minor, patch] = version2.split('.')
        console.log(major)
        console.log(minor)
        console.log(patch)
        res.status(200).send(version)
    }
    else {
        console.log("version not found")
        res.status(500).send('version not found')
    }
})

app.listen(port, () => {
    console.log(`App listening on port ${port}`)
})