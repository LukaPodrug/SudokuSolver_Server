const joi = require('joi')

const registrationSchema = joi.object({
    firstName: joi.string().required(),
    lastName: joi.string().required(),
    username: joi.string().required(),
    passwordPlaintext: joi.string().required(),
    email: joi.string().allow('').required(),
    nationality: joi.string().allow('').required(),
    dateOfBirth: joi.string().allow('').required()
})

const loginSchema = joi.object({
    username: joi.string().required(),
    passwordPlaintext: joi.string().required()
})

const uploadImageSchema = joi.object({
    imageBase64String: joi.string().required()
})

const newPuzzleSchema = joi.object({
    string: joi.string().required()
})

const getUserByIdSchema = joi.object({
    id: joi.number().required()
})

const editUserSchema = joi.object({
    firstName: joi.string().required(),
    lastName: joi.string().required(),
    username: joi.string().required(),
    email: joi.string().allow('').required(),
    nationality: joi.string().allow('').required(),
    dateOfBirth: joi.string().allow('').required()
})

const newAttemptSchema = joi.object({
    puzzleId: joi.number().required(),
    completion: joi.bool().required(),
    time: joi.number().required()
})

const getPuzzlesByDifficultyAndPage = joi.object({
    difficulty: joi.number().required(),
    page: joi.number().required()
})

const solvePuzzleStepByStepSchema = joi.object({
    id: joi.number().required(),
    puzzleString: joi.string().required(),
    userString: joi.string().required(),
    solutionString: joi.string().required()
})

module.exports = {
    registrationSchema,
    loginSchema,
    uploadImageSchema,
    newPuzzleSchema,
    getUserByIdSchema,
    editUserSchema,
    newAttemptSchema,
    getPuzzlesByDifficultyAndPage,
    solvePuzzleStepByStepSchema
}