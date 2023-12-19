const express = require('express')
const dotenv = require('dotenv')
const cors = require('cors')
const bodyParser = require('body-parser')
const fs = require('fs')
const os = require('os')

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

app.get('/architecture', (req, res) => {
    switch(os.arch()){ 
        case 'x32': 
            console.log("32-bit extended system"); 
            break; 
           
        case 'x64': 
            console.log("64-bit extended system"); 
            break; 
       
        case 'arm': 
            console.log("32-bit  Advanced RISC Machine"); 
            break; 
       
        case 'arm64': 
            console.log("64-bit  Advanced RISC Machine"); 
            break; 
       
        case 's390': 
            console.log("31-bit The IBM System/390, the"
                    + " third generation of the System/360"
                    + " instruction set architecture"); 
            break; 
       
        case 's390x': 
            console.log("64-bit The IBM System/390, the"
                    + " third generation of the System/360"
                    + " instruction set architecture"); 
            break; 
       
        case 'mipsel': 
            console.log("64-bit Microprocessor without"
                    + " Interlocked Pipelined Stages"); 
            break; 
       
        case 'mips': 
            console.log("32-bit Microprocessor without"
                    + " Interlocked Pipelined Stages"); 
            break; 
       
        case 'ia32': 
            console.log("32-bit Intel Architecture"); 
            break; 
       
        case 'ppc': 
            console.log("PowerPC Architecture."); 
            break; 
       
        case 'ppc64': 
            console.log("64-bit PowerPC Architecture."); 
            break; 
       
        default: 
            console.log(" unknown processor"); 
    }

    res.status(200).send('Arch success')
})

app.listen(port, () => {
    console.log(`App listening on port ${port}`)
})