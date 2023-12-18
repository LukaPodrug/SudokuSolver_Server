const bcrypt = require('bcrypt')
const jwt = require('jsonwebtoken')

async function createPasswordHash(passwordPlaintext) {
    try {
        const salt = await bcrypt.genSalt(10)

        const passwordHash = await bcrypt.hash(passwordPlaintext, salt)

        return [true, 'Password hash successfully created', passwordHash]
    }
    catch(error) {
        return [false, error, null]
    }
}

async function verifyPassword(passwordPlaintext, passwordHash) {
    try {
        const compareResult = await bcrypt.compare(passwordPlaintext, passwordHash)

        if(!compareResult) {
            return [true, 'Incorrect password', false]
        }

        return [true, 'Correct password', true]
    }
    catch(error) {
        return [false, error, null]
    }
}

function createToken(id) {
    try {
        const jwtSecretKey = process.env.JWT_SECRET_KEY

        if(!jwtSecretKey) {
            return [false, 'Error with getting token secret key', null]
        }
    
        const data = {
            id
        }
    
        const token = jwt.sign(data, jwtSecretKey)
    
        if(!token) {
            return [false, 'Error with creating token', null]
        }
    
        return [true, 'Token successfully created', token]
    }
    catch(error) {
        return [false, error, null]
    }
}

function verifyToken(token) {
    try {
        const jwtSecretKey = process.env.JWT_SECRET_KEY

        if(!jwtSecretKey) {
            return [false, 'Error with getting token secret key', null, null]
        }
    
        const tokenData = jwt.verify(token, jwtSecretKey)

        if(!tokenData) {
            return [true, 'Invalid token', false, null]
        }
    
        return [true, 'Valid token', true, tokenData]
    }
    catch(error) {
        return [false, error, null, null]
    }
}

module.exports = {
    createPasswordHash,
    verifyPassword,
    createToken,
    verifyToken
}