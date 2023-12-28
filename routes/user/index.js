const express = require('express')
const dateConverter = require('moment')

const dataController = require('../../controllers/data')
const databaseController = require('../../controllers/database')
const authorizationController = require('../../controllers/authorization')

const { getUserByIdSchema, editUserSchema } = require('../../database/schemas')

const router = express.Router()

router.get('/ownData', async(req, res) => {
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

    delete userById.id
    delete userById.password
    delete userById.active

    if(userById.dateOfBirth) {
        userById.dateOfBirth = dateConverter(new Date(userById.dateOfBirth)).format("YYYY-MM-DD")
    }

    const [validAttemptsTableExistance, messageAttemptsTableExistance, attemptsTableExistance] = await databaseController.verifyTableExistance('attempts')

    console.log(messageAttemptsTableExistance)

    if(!validAttemptsTableExistance) {
        res.status(500).send('Error with verifying attempts table existance')
        return
    }

    if(!attemptsTableExistance) {
        const [validCreateAttemptsTable, messageCreateAttemptsTable] = await databaseController.createAttemptsTable()

        console.log(messageCreateAttemptsTable)

        if(!validCreateAttemptsTable) {
            res.status(500).send('Error with creating attempts table')
            return
        }
    }

    const [validUserStatistics, messageUserStatistics, userStatistics] = await databaseController.getStatisticsByUserId(tokenData.id)

    console.log(messageUserStatistics)

    if(!validUserStatistics) {
        res.status(500).send('Error with getting user statistics')
        return
    }

    userById.successAttempts = userStatistics.successAttempts
    userById.failureAttempts = userStatistics.failureAttempts

    const [validPuzzlesTableExistance, messagePuzzlesTableExistance, puzzlesTableExistance] = await databaseController.verifyTableExistance('puzzles')

    console.log(messagePuzzlesTableExistance)

    if(!validPuzzlesTableExistance) {
        res.status(500).send('Error with verifying puzzles table existance')
        return
    }

    if(!puzzlesTableExistance) {
        const [validCreatePuzzlesTable, messageCreatePuzzlesTable] = await databaseController.createPuzzlesTable()

        console.log(messageCreatePuzzlesTable)

        if(!validCreatePuzzlesTable) {
            res.status(500).send('Error with creating puzzles table')
            return
        }
    }

    const [validUserRecords, messageUserRecords, userRecords] = await databaseController.getUserRecords(tokenData.id)

    console.log(messageUserRecords)

    if(!validUserRecords) {
        res.status(500).send('Error with getting user records')
        return
    }

    userById.numberOfRecords = userRecords.numberOfRecords

    res.status(200).send(userById)
})

router.get('/userData', async(req, res) => {
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

    const [validUserById1, messageUserById1, userById1] = await databaseController.getUserById(tokenData.id)

    console.log(messageUserById1)

    if(!validUserById1) {
        res.status(500).send('Error with getting user by id')
        return
    }

    if(!userById1) {
        res.status(400).send('User not found')
        return
    }

    if(!userById1.active) {
        res.status(400).send('User not active')
        return
    }

    const getUserByIdSchemaValidationResult = getUserByIdSchema.validate(req.query)

    if(getUserByIdSchemaValidationResult.error) {
        res.status(400).send('Faulty get user by id data')
        return
    }

    const [validUserById2, messageUserById2, userById2] = await databaseController.getUserById(req.query.id)

    console.log(messageUserById2)

    if(!validUserById2) {
        res.status(500).send('Error with getting user by id')
        return
    }

    if(!userById2) {
        res.status(400).send('User not found')
        return
    }

    if(!userById2.active) {
        res.status(400).send('User not active')
        return
    }

    delete userById2.id
    delete userById2.password
    delete userById2.active

    if(userById2.dateOfBirth) {
        userById2.dateOfBirth = dateConverter(new Date(userById2.dateOfBirth)).format("YYYY-MM-DD")
    }

    const [validAttemptsTableExistance, messageAttemptsTableExistance, attemptsTableExistance] = await databaseController.verifyTableExistance('attempts')

    console.log(messageAttemptsTableExistance)

    if(!validAttemptsTableExistance) {
        res.status(500).send('Error with verifying attempts table existance')
        return
    }

    if(!attemptsTableExistance) {
        const [validCreateAttemptsTable, messageCreateAttemptsTable] = await databaseController.createAttemptsTable()

        console.log(messageCreateAttemptsTable)

        if(!validCreateAttemptsTable) {
            res.status(500).send('Error with creating attempts table')
            return
        }
    }

    const [validUserStatistics, messageUserStatistics, userStatistics] = await databaseController.getStatisticsByUserId(req.query.id)

    console.log(messageUserStatistics)

    if(!validUserStatistics) {
        res.status(500).send('Error with getting user statistics')
        return
    }

    userById2.successAttempts = userStatistics.successAttempts
    userById2.failureAttempts = userStatistics.failureAttempts

    const [validPuzzlesTableExistance, messagePuzzlesTableExistance, puzzlesTableExistance] = await databaseController.verifyTableExistance('puzzles')

    console.log(messagePuzzlesTableExistance)

    if(!validPuzzlesTableExistance) {
        res.status(500).send('Error with verifying puzzles table existance')
        return
    }

    if(!puzzlesTableExistance) {
        const [validCreatePuzzlesTable, messageCreatePuzzlesTable] = await databaseController.createPuzzlesTable()

        console.log(messageCreatePuzzlesTable)

        if(!validCreatePuzzlesTable) {
            res.status(500).send('Error with creating puzzles table')
            return
        }
    }

    const [validUserRecords, messageUserRecords, userRecords] = await databaseController.getUserRecords(req.query.id)

    console.log(messageUserRecords)

    if(!validUserRecords) {
        res.status(500).send('Error with getting user records')
        return
    }

    userById2.numberOfRecords = userRecords.numberOfRecords

    res.status(200).send(userById2)
})

router.patch('/', async(req, res) => {
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

    const editUserSchemaValidationResult = editUserSchema.validate(req.body)

    if(editUserSchemaValidationResult.error) {
        res.status(400).send('Faulty edit user data')
        return
    }

    const [validEditUserDataVerification, messageEditUserDataVerification, editUserDataVerification, editUserData] = dataController.verifyEditUserData(tokenData.id, req.body.firstName, req.body.lastName, req.body.username, req.body.email, req.body.nationality, req.body.dateOfBirth)

    console.log(messageEditUserDataVerification)

    if(!validEditUserDataVerification) {
        res.status(500).send('Error with verifying edit user data')
        return
    }

    if(!editUserDataVerification) {
        res.status(400).send('Faulty edit user data')
        return
    }

    if(userById.username !== editUserData.username) {
        const [validUserByUsername, messageUserByUsername, userByUsername] = await databaseController.getUserByUsername(editUserData.username)

        console.log(messageUserByUsername)

        if(!validUserByUsername) {
            res.status(500).send('Error with getting user by username')
            return
        }

        if(userByUsername) {
            res.status(400).send('User with entered username already exists')
            return
        }
    }

    if(editUserData.email) {
        if(userById.email !== editUserData.email) {
            const [validUserByEmail, messageUserByEmail, userByEmail] = await databaseController.getUserByEmail(editUserData.email)

            console.log(messageUserByEmail)

            if(!validUserByEmail) {
                res.status(500).send('Error with getting user by email')
                return
            }

            if(userByEmail) {
                res.status(400).send('User with entered email already exists')
                return
            }
        }
    }

    if(userById.firstName === editUserData.firstName && userById.lastName === editUserData.lastName && userById.username === editUserData.username && userById.email === editUserData.email && userById.nationality === editUserData.nationality && userById.dateOfBirth === editUserData.dateOfBirth) {
        res.status(400).send('Edit user data same as old')
        return
    }

    const [validEditUser, messageEditUser] = await databaseController.editUser(editUserData.id, editUserData.firstName, editUserData.lastName, editUserData.username, editUserData.email, editUserData.nationality, editUserData.dateOfBirth)

    console.log(messageEditUser)

    if(!validEditUser) {
        res.status(500).send('Error with editing user')
        return
    }

    res.status(200).send('User successfully edited')
})

module.exports = router