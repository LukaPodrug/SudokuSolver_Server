const express = require('express')
const dateConverter = require('moment')

const dataController = require('../../controllers/data')
const databaseController = require('../../controllers/database')
const authorizationController = require('../../controllers/authorization')
const helperController = require('../../controllers/helper')

const { uploadImageSchema, newPuzzleSchema, getPuzzlesByDifficultyAndPage, solvePuzzleStepByStepSchema } = require('../../database/schemas')

const router = express.Router()

router.post('/uploadImage', async (req, res) => {
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

    const uploadImageSchemaValidationResult = await uploadImageSchema.validateAsync(req.body)

    if(uploadImageSchemaValidationResult.error) {
        res.status(400).send('Faulty upload image data')
        return
    }

    const [validUploadImageDataVerification, messageUploadImageDataVerification, uploadImageDataVerification, uploadImageData] = dataController.verifyUploadImageData(req.body.imageBase64String)

    console.log(messageUploadImageDataVerification)

    if(!validUploadImageDataVerification) {
        res.status(500).send('Error with verifying upload image data')
        return
    }

    if(!uploadImageDataVerification) {
        res.status(400).send('Faulty upload image data')
        return
    }

    const [validBase64Image, messageBase64Image, base64Image] = helperController.getBase64Image(uploadImageData.imageBase64String)

    console.log(messageBase64Image)

    if(!validBase64Image) {
        res.status(500).send('Error with base64 image string')
        return
    }

    const [validImageFormat, messageImageFormat, imageFormat] = helperController.getImageFormat(uploadImageData.imageBase64String)

    console.log(messageImageFormat)

    if(!validImageFormat) {
        res.status(500).send('Error with image format')
        return
    }

    const [validImageName, messageImageName, imageName] = helperController.createImageName(base64Image)

    console.log(messageImageName)

    if(!validImageName) {
        res.status(500).send('Error with creating image name')
        return
    }

    const [validSaveImage, messageSaveImage] = helperController.saveImage(imageName, imageFormat, base64Image)

    console.log(messageSaveImage)

    if(!validSaveImage) {
        res.status(500).send('Error with uploading image')
        return
    }

    const [validExecuteGrabber, messageExecuteGrabber, dataExecuteGrabber] = await helperController.executeGrabber(imageName, imageFormat)

    console.log(messageExecuteGrabber)

    if(!validExecuteGrabber) {
        const [validDeleteImage, messageDeleteImage] = helperController.deleteImage(imageName, imageFormat)

        console.log(messageDeleteImage)

        if(!validDeleteImage) {
            res.status(500).send('Error with deleting image')
            return
        }

        if(dataExecuteGrabber) {
            res.status(400).send(dataExecuteGrabber)
            return
        }
        else {
            res.status(400).send('Error with executing grabber')
            return
        }
    }

    const [validDeleteImage, messageDeleteImage] = helperController.deleteImage(imageName, imageFormat)

    console.log(messageDeleteImage)
    
    if(!validDeleteImage) {
        res.status(500).send('Error with deleting image')
        return
    }
    
    res.status(200).send(dataExecuteGrabber)
})

router.post('/uploadPuzzle', async (req, res) => {
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

    const newPuzzleSchemaValidationResult = await newPuzzleSchema.validateAsync(req.body)

    if(newPuzzleSchemaValidationResult.error) {
        res.status(400).send('Faulty new puzzle data')
        return
    }

    const [validNewPuzzleDataVerification, messageNewPuzzleDataVerification, newPuzzleDataVerification, newPuzzleData] = dataController.verifyNewPuzzleData(req.body.string)

    console.log(messageNewPuzzleDataVerification)

    if(!validNewPuzzleDataVerification) {
        res.status(500).send('Error with verifying new puzzle data')
        return
    }

    if(!newPuzzleDataVerification) {
        res.status(400).send('Faulty new puzzle data')
        return
    }

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

    const [validPuzzleByString, messagePuzzleByString, puzzleByString] = await databaseController.getPuzzleByString(newPuzzleData.string)

    console.log(messagePuzzleByString)

    if(!validPuzzleByString) {
        res.status(500).send('Error with getting puzzle by string')
        return
    }

    if(puzzleByString) {
        res.status(400).send('Puzzle with entered string found')
        return
    }

    const [validExecuteHelper, messageExecuteHelper, dataExecuteHelper] = await helperController.executeHelperUploadPuzzle(newPuzzleData.string)

    console.log(messageExecuteHelper)

    if(!validExecuteHelper) {
        res.status(500).send('Error with executing helper')
        return
    }

    [newPuzzleData.difficulty, newPuzzleData.solvedString] = dataExecuteHelper.split('&')
    newPuzzleData.creationDate = dateConverter(new Date()).format("YYYY-MM-DD")
    newPuzzleData.creationUserId = tokenData.id

    const [validNewPuzzle, messageNewPuzzle] = await databaseController.createNewPuzzle(newPuzzleData.string, newPuzzleData.solvedString, newPuzzleData.difficulty, newPuzzleData.creationDate, newPuzzleData.creationUserId)

    console.log(messageNewPuzzle)

    if(!validNewPuzzle) {
        res.status(500).send('Error with creating new puzzle')
        return
    }

    res.status(200).send('New puzzle puzzle successfully created')
})

router.get('/', async(req, res) => {
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

    const getPuzzlesByDifficultyAndPageSchemaValidationResult = await getPuzzlesByDifficultyAndPage.validateAsync(req.query)

    if(getPuzzlesByDifficultyAndPageSchemaValidationResult.error) {
        res.status(400).send('Faulty new puzzle data')
        return
    }

    const [validPuzzlesByDifficultyAndPage, messagePuzzlesByDifficultyAndPage, puzzlesByDifficultyAndPage] = await databaseController.getPuzzlesByDifficultyAndPage(req.query.difficulty, req.query.page)

    console.log(messagePuzzlesByDifficultyAndPage)

    if(!validPuzzlesByDifficultyAndPage) {
        res.status(500).send('Error with getting puzzles by difficulty and page')
        return
    }

    const puzzleIds = []

    puzzlesByDifficultyAndPage.forEach(puzzle => {
        puzzle.totalSuccessAttempts = 0
        puzzle.totalFailureAttempts = 0

        puzzle.userSuccessAttempts = 0
        puzzle.userFailureAttempts = 0

        puzzle.creationDate = dateConverter(new Date(puzzle.creationDate)).format("YYYY-MM-DD")

        if(puzzle.recordDate) {
            puzzle.recordDate = dateConverter(new Date(puzzle.recordDate)).format("YYYY-MM-DD")
        }

        puzzleIds.push(puzzle.id)
    })

    const [validStatisticsByPuzzleIds, messageStatisticsByPuzzleIds, statisticsByPuzzleIds] = await databaseController.getStatisticsByPuzzleIds(puzzleIds)

    console.log(messageStatisticsByPuzzleIds)

    if(!validStatisticsByPuzzleIds) {
        res.status(500).send('Error with getting statistics by puzzle ids')
        return
    }

    puzzlesByDifficultyAndPage.forEach(puzzle => {
        statisticsByPuzzleIds.forEach(statistic => {
            if(puzzle.id === statistic.puzzleId) {
                puzzle.totalSuccessAttempts = statistic.totalSuccessAttempts
                puzzle.totalFailureAttempts = statistic.totalFailureAttempts
            }
        })
    })

    const [validStatisticsByUserIdAndPuzzleIds, messageStatisticsByUserIdAndPuzzleIds, statisticsByUserIdAndPuzzleIds] = await databaseController.getStatisticsByUserIdAndPuzzleIds(tokenData.id, puzzleIds)

    console.log(messageStatisticsByUserIdAndPuzzleIds)

    if(!validStatisticsByUserIdAndPuzzleIds) {
        res.status(500).send('Error with getting statistics by user id and puzzle ids')
        return
    }

    puzzlesByDifficultyAndPage.forEach(puzzle => {
        statisticsByUserIdAndPuzzleIds.forEach(statistic => {
            if(puzzle.id === statistic.puzzleId) {
                puzzle.userSuccessAttempts = statistic.userSuccessAttempts
                puzzle.userFailureAttempts = statistic.userFailureAttempts
            }
        })
    })

    res.status(200).send(puzzlesByDifficultyAndPage)
})

router.post('/solveStepByStep', async(req, res) => {
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

    const solvePuzzleStepByStepSchemaValidationResult = await solvePuzzleStepByStepSchema.validateAsync(req.body)

    if(solvePuzzleStepByStepSchemaValidationResult.error) {
        res.status(400).send('Faulty solve puzzle step by step data')
        return
    }

    const [validPuzzleById, messagePuzzleById, puzzleById] = await databaseController.getPuzzleById(req.body.id)

    console.log(messagePuzzleById)

    if(!validPuzzleById) {
        res.status(500).send('Error with getting puzzle by id')
        return
    }

    if(!puzzleById) {
        res.status(400).send('Puzzle not found')
        return
    }

    const [validExecuteHelper, messageExecuteHelper, dataExecuteHelper] = await helperController.executeHelperSolveStepByStep(req.body.puzzleString, req.body.userString, req.body.solutionString)

    console.log(messageExecuteHelper)

    if(!validExecuteHelper) {
        res.status(500).send('Error with executing helper')
        return
    }

    res.status(200).send(dataExecuteHelper)
})

module.exports = router