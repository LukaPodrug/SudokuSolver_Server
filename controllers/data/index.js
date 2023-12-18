const emailValidator = require('email-validator')
const nationalityValidator = require('country-code-lookup')
const dateValidator = require('moment')
const imageValidator = require('is-base64')

function verifyRegistrationData(firstName, lastName, username, email, nationality, dateOfBirth, passwordPlaintext) {
    const registrationData = {
        firstName: firstName,
        lastName: lastName,
        username: username,
        email: email,
        nationality: nationality,
        dateOfBirth: dateOfBirth,
        passwordPlaintext: passwordPlaintext,
    }

    try {
        if(email.length > 0) {
            if(!emailValidator.validate(email)) {
                return [true, "Faulty new user email data", false, null]
            }
        }

        if(nationality.length > 0) {
            if(!nationalityValidator.byIso(nationality)) {
                return [true, "Faulty new user nationality data", false, null]
            }
        }

        if(dateOfBirth.length > 0) {
            if(!dateValidator(dateOfBirth, 'YYYY-MM-DD', true).isValid()) {
                return [true, "Faulty new user date of birth data", false, null]
            }
        }

        return [true, "Lawful new user data", true, registrationData]
    }
    catch(error) {
        return [false, error, null, null]
    }
}

function verifyUploadImageData(imageBase64String) {
    const uploadImageData = {
        imageBase64String: imageBase64String
    }

    try {
        const uploadImageDataVerification = imageValidator(imageBase64String, {mimeRequired: true})

        if(!uploadImageDataVerification) {
            return [true, "Faulty upload image vase64 image string data", false, null]
        }

        return [true, "Lawful upload image data", true, uploadImageData]
    }
    catch(error) {
        return [false, error, null, null]
    }
}

function verifyNewPuzzleData(string) {
    const newPuzzleData = {
        string: string
    }

    try {
        if(string.length !== 81) {
            return [true, "Faulty new puzzle string data", false, null]
        }

        return [true, "Lawful new puzzle data", true, newPuzzleData]
    }
    catch(error) {
        return [false, error, null, null]
    }
}

function verifyEditUserData(id, firstName, lastName, username, email, nationality, dateOfBirth) {
    const editUserData = {
        id: id,
        firstName: firstName,
        lastName: lastName,
        username: username,
        email: email,
        nationality: nationality,
        dateOfBirth: dateOfBirth,
        passwordPlaintext: passwordPlaintext,
    }

    try {
        if(email.length > 0) {
            if(!emailValidator.validate(email)) {
                return [true, "Faulty edit user email data", false, null]
            }
        }

        if(nationality.length > 0) {
            if(!nationalityValidator.byIso(nationality)) {
                return [true, "Faulty edit user nationality data", false, null]
            }
        }

        if(dateOfBirth.length > 0) {
            if(!dateValidator(dateOfBirth, 'YYYY-MM-DD', true).isValid()) {
                return [true, "Faulty edit user date of birth data", false, null]
            }
        }

        return [true, "Lawful edit user data", true, editUserData]
    }
    catch(error) {
        return [false, error, null, null]
    }
}

module.exports = {
    verifyRegistrationData,
    verifyUploadImageData,
    verifyNewPuzzleData,
    verifyEditUserData
}