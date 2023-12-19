const express = require('express')
const dotenv = require('dotenv')
const cors = require('cors')
const bodyParser = require('body-parser')
const { family, GLIBC, MUSL } = require('detect-libc')
const { version } = require('detect-libc')
const { exec } = require("child_process")

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

app.get('/libplusplus', (req, res) => {
    exec('/sbin/ldconfig -p | grep stdc++', (error, stdout, stderr) => {
        if(error) {
            console.log(`error: ${error.message}`)
            res.status(500).send(error.message)
            return
        }

        if(stderr) {
            console.log(`stderr: ${stderr}`)
            res.status(400).send(stderr)
            return
        }

        console.log(`stdout: ${stdout}`)
        res.status(200).send(stdout)
    })
})

app.get('/version', async (req, res) => {
    const version2 = await version()
    if (version2) {
        const [major, minor, patch] = version2.split('.')
        console.log(major)
        console.log(minor)
        console.log(patch)
        res.status(200).send(version2)
    }
    else {
        console.log("version not found")
        res.status(500).send('version not found')
    }
})

app.get('/versionplusplus', (req, res) => {
    exec('strings /usr/lib/libstdc++.so.6 | grep LIBCXX', (error, stdout, stderr) => {
        if(error) {
            console.log(`error: ${error.message}`)
            res.status(500).send(error.message)
            return
        }

        if(stderr) {
            console.log(`stderr: ${stderr}`)
            res.status(400).send(stderr)
            return
        }

        console.log(`stdout: ${stdout}`)
        res.status(200).send(stdout)
    })
})

app.listen(port, () => {
    console.log(`App listening on port ${port}`)
})