const fs = require('fs')
const crypto = require('crypto')

const execFile = require('child_process').execFile

function getBase64Image(base64String) {
    const base64Image = base64String.split(';base64,').pop()

    if(!base64Image) {
        return [false, 'Base64 image string not found', null]
    }

    if(base64Image.length === 0) {
        return [false, 'Base64 image string too short', null]
    }
    
    return [true, 'Valid base64 image string', base64Image]
}

function getImageFormat(base64String) {
    const imageFormat = base64String.split(';')[0].split('/')[1]

    if(!imageFormat) {
        return [false, 'Image format not found', null]
    }

    if(imageFormat.length < 3) {
        return [false, 'Image format too short', null]
    }

    return [true, 'Valid image format', imageFormat]
}

function createImageName(base64Image) {
    const imageName = crypto.createHash('md5').update(base64Image).digest('hex')

    if(!imageName) {
        return [false, 'Error with creating image name', null]
    }

    return [true, 'Image name created successfully', imageName]
}

function saveImage(imageName, imageFormat, base64Image) {
    fs.writeFile(`./images/${imageName}.${imageFormat}`, base64Image, {encoding: 'base64'}, function(error) {
        if(error) {
            return [false, error]
        }
    })

    return [true, 'Image successfully uploaded']
}

function executeGrabber(imageName, imageFormat) {
    return new Promise(resolve => {
        execFile('./sudokuGrabber', [`${imageName}.${imageFormat}`], function(error, data) {
            if(error && data) {
                resolve([false, error, data])
            }
            else if (error) {
                resolve([false, error, null])
            }
            else {
                resolve([true, 'Grabber successfully executed', data])
            }
        })
    })
}

function deleteImage(imageName, imageFormat) {
    fs.unlink(`./images/${imageName}.${imageFormat}`, function(error) {
        if(error) {
            return [false, error]
        }
    })

    return [true, 'Image successfully deleted']
}

function executeHelperUploadPuzzle(puzzleString) {
    return new Promise(resolve => {
        execFile('./sudokuHelper', [1, `${puzzleString}`], function(error, data) {
            if(error && data) {
                resolve([false, error, data])
            }
            else if (error) {
                resolve([false, error, null])
            }
            else {
                resolve([true, 'Helper successfully executed', data])
            }
        })
    })
}

function executeHelperSolveStepByStep(puzzleString, userString, solutionString) {
    return new Promise(resolve => {
        execFile('./sudokuHelper', [2, `${puzzleString}`, `${userString}`, `${solutionString}`], function(error, data) {
            if(error && data) {
                resolve([false, error, data])
            }
            else if (error) {
                resolve([false, error, null])
            }
            else {
                resolve([true, 'Helper successfully executed', data])
            }
        })
    })
}

module.exports = {
    getBase64Image,
    getImageFormat,
    createImageName,
    saveImage,
    executeGrabber,
    deleteImage,
    executeHelperUploadPuzzle,
    executeHelperSolveStepByStep
}