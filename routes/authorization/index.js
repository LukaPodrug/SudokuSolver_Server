const express = require('express')

const dataController = require('../../controllers/data')
const databaseController = require('../../controllers/database')
const authorizationController = require('../../controllers/authorization')

const { registrationSchema, loginSchema } = require('../../database/schemas')

const router = express.Router()

router.post('/registration', async (req, res) => {
    const registrationSchemaValidationResult = await registrationSchema.validateAsync(req.body)

    if(registrationSchemaValidationResult.error) {
        res.status(400).send('Faulty registration data')
        return
    }

    const [validRegistrationDataVerification, messageRegistrationDataVerification, registrationDataVerification, registrationData] = dataController.verifyRegistrationData(req.body.firstName, req.body.lastName, req.body.username, req.body.email, req.body.nationality, req.body.dateOfBirth, req.body.passwordPlaintext)

    console.log(messageRegistrationDataVerification)

    if(!validRegistrationDataVerification) {
        res.status(500).send('Error with verifying registration data')
        return
    }

    if(!registrationDataVerification) {
        res.status(400).send('Faulty registration data')
        return
    }

    const [validUsersTableExistance, messageUsersTableExistance, usersTableExistance] = await databaseController.verifyTableExistance('users')

    console.log(messageUsersTableExistance)

    if(!validUsersTableExistance) {
        res.status(500).send('Error with verifying users table existance')
        return
    }

    if(!usersTableExistance) {
        const [validCreateUsersTable, messageCreateUsersTable] = await databaseController.createUsersTable()

        console.log(messageCreateUsersTable)

        if(!validCreateUsersTable) {
            res.status(500).send('Error with creating users table')
            return
        }
    }

    const [validUserByUsername, messageUserByUsername, userByUsername] = await databaseController.getUserByUsername(registrationData.username)

    console.log(messageUserByUsername)

    if(!validUserByUsername) {
        res.status(500).send('Error with getting user by username')
        return
    }

    if(userByUsername) {
        res.status(400).send('User with enetered username found')
        return
    }

    const [validUserByEmail, messageUserByEmail, userByEmail] = await databaseController.getUserByEmail(registrationData.email)

    console.log(messageUserByEmail)

    if(!validUserByEmail) {
        res.status(500).send('Error with getting user by email')
        return
    }

    if(userByEmail) {
        res.status(400).send('User with enetered email found')
        return
    }

    const [validPasswordHash, messagePasswordHash, passwordHash] = await authorizationController.createPasswordHash(registrationData.passwordPlaintext)

    console.log(messagePasswordHash)

    if(!validPasswordHash) {
        res.status(500).send('Error with creating password hash')
        return
    }

    const [validNewUser, messageNewUser, newUser] = await databaseController.createNewUser(registrationData.firstName, registrationData.lastName, registrationData.username, registrationData.email, registrationData.nationality, registrationData.dateOfBirth, passwordHash)

    console.log(messageNewUser)

    if(!validNewUser) {
        res.status(500).send('Error with creating new user')
        return
    }

    const [validToken, messageToken, token] = authorizationController.createToken(newUser.id)

    console.log(messageToken)

    if(!validToken) {
        res.status(500).send('Error with creating token')
        return
    }

    if(!token) {
        res.status(500).send('Token not created')
        return
    }

    res.status(200).send(token)
})

router.post('/login', async (req, res) => {
    const loginSchemaValidationResult = await loginSchema.validateAsync(req.body)

    if(loginSchemaValidationResult.error) {
        res.status(400).send('Faulty login data')
        return
    }

    const [validUserByUsername, messageUserByUsername, userByUsername] = await databaseController.getUserByUsername(req.body.username)

    console.log(messageUserByUsername)

    if(!validUserByUsername) {
        res.status(500).send('Error with getting user by username')
        return
    }

    if(!userByUsername) {
        res.status(400).send('Wrong login data')
        return
    }

    if(!userByUsername.active) {
        res.status(400).send('User not active')
        return
    }

    const [validPasswordVerification, messagePasswordVerification, passwordVerification] = await authorizationController.verifyPassword(req.body.passwordPlaintext, userByUsername.password)

    console.log(messagePasswordVerification)

    if(!validPasswordVerification) {
        res.status(500).send('Error with verifying password')
        return
    }

    if(!passwordVerification) {
        res.status(400).send('Wrong login data')
        return
    }

    const [validToken, messageToken, token] = authorizationController.createToken(userByUsername.id)

    console.log(messageToken)

    if(!validToken) {
        res.status(500).send('Error with creating token')
        return
    }

    if(!token) {
        res.status(500).send('Token not created')
        return
    }

    res.status(200).send(token)
})

router.delete('/', async(req, res) => {
    const token = req.get('Authorization')
    
    if(!token) {
        res.status(400).send('Invalid token')
        return
    }

    const [validTokenVerification, messageTokenVerification, tokenVerification, tokenData] = authorizationController.verifyToken(token)

    console.log(messageTokenVerification)

    if(!validTokenVerification) {
        res.status(500).send('Error with verifying token')
        return
    }

    if(!tokenVerification) {
        res.status(400).send('Invalid token')
        return
    }

    const [validUserById, messageUserById, userById] = await databaseController.getUserById(tokenData.id)

    console.log(messageUserById)

    if(!validUserById) {
        res.status(500).send('Error with getting user by id')
        return
    }

    if(!userById) {
        res.status(400).send('User not found')
        return
    }

    if(!userById.active) {
        res.status(400).send('User not active')
        return
    }

    const [validDeleteUser, messageDeleteUser] = await databaseController.deleteUser(tokenData.id)

    console.log(messageDeleteUser)

    if(!validDeleteUser) {
        res.status(500).send('Error with deleteing user')
        return
    }

    res.status(200).send('User successfully deleted')
})

module.exports = router