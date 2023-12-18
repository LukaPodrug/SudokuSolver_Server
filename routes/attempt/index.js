const express = require('express')
const dateConverter = require('moment')

const databaseController = require('../../controllers/database')
const authorizationController = require('../../controllers/authorization')

const { newAttemptSchema } = require('../../database/schemas')

const router = express.Router()

router.post('/', async(req, res) => {
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

    const newAttemptSchemaValidationResult = await newAttemptSchema.validateAsync(req.body)

    if(newAttemptSchemaValidationResult.error) {
        res.status(400).send('Faulty new attempt data')
        return
    }

    const [validPuzzleById, messagePuzzleById, puzzleById] = await databaseController.getPuzzleById(req.body.puzzleId)

    console.log(messagePuzzleById)

    if(!validPuzzleById) {
        res.status(500).send('Error with getting puzzle by id')
        return
    }

    if(!puzzleById) {
        res.status(400).send('Puzzle not found')
        return
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

    const [validAttemptByUserIdAndPuzzleId, messageAttemptByUserIdAndPuzzleId, attemptByUserIdAndPuzzleId] = await databaseController.getAttemptsByUserIdAndPuzzleId(tokenData.id, req.body.puzzleId)

    console.log(messageAttemptByUserIdAndPuzzleId)

    if(!validAttemptByUserIdAndPuzzleId) {
        res.status(500).send('Error with getting attempt by user id and puzzle id')
        return
    }

    if(attemptByUserIdAndPuzzleId.completion) {
        res.status(400).send('User already solved puzzle')
        return
    }

    const attemptDate = dateConverter(new Date()).format("YYYY-MM-DD")

    if(req.body.completion) {
        if(!puzzleById.recordTime || req.body.time < puzzleById.recordTime) {
            if(!attemptByUserIdAndPuzzleId) {
                const [validEditPuzzleRecord, messageEditPuzzleRecord] = await databaseController.editPuzzleRecord(req.body.puzzleId, tokenData.id, req.body.time, attemptDate)

                console.log(messageEditPuzzleRecord)

                if(!validEditPuzzleRecord) {
                    res.status(500).send('Error with editing puzzle record')
                    return
                }
            }
        }
    }

    const [validNewAttempt, messageNewAttempt] = await databaseController.createNewAttempt(tokenData.id, req.body.puzzleId, attemptDate, req.body.completion, req.body.time)

    console.log(messageNewAttempt)

    if(!validNewAttempt) {
        res.status(500).send('Error with creating new attempt')
        return
    }

    res.status(200).send('New attempt succesfully created')
})

module.exports = router