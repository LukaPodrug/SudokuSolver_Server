const sql = require('../../database/connection')

async function verifyTableExistance(tableName) {
    try {
        const response = await sql`
            SELECT EXISTS (
                SELECT 1
                FROM "information_schema".tables
                WHERE "table_name" = ${tableName}
            ) AS "tableExistance"
        `
        
        if(!response[0].tableExistance) {
            return [true, `Table ${tableName} does not exist`, false]
        }

        return [true, `Table ${tableName} exists`, true]
    }
    catch(error) {
        return [false, error, null]
    }
}

async function createUsersTable() {
    try {
        await sql`
            CREATE TABLE "users" (
                "id" serial PRIMARY KEY,
                "firstName" varchar NOT NULL,
                "lastName" varchar NOT NULL,
                "username" varchar NOT NULL,
                "email" varchar,
                "nationality" varchar,
                "dateOfBirth" date,
                "password" varchar NOT NULL,
                "active" bool NOT NULL,
                "points" integer NOT NULL
            )
        `

        return [true, `Table users created successfully`]
    }
    catch(error) {
        return [false, error]
    }
}

async function getUserByEmail(email) {
    try {
        const response = await sql`
            SELECT *
            FROM "users"
            WHERE "email" = ${email}
        `
        
        if(response.length === 0) {
            return [true, 'User with entered email does not exist', null]
        }

        return [true, 'User with entered email found', response[0]]
    }
    catch(error) {
        return [false, error, null]
    }
}

async function createNewUser(firstName, lastName, username, email, nationality, dateOfBirth, passwordHash) {
    try {
        const response = await sql`
            INSERT INTO "users"("firstName", "lastName", "username", "email", "nationality", "dateOfBirth", "password", "active", "points")
            VALUES(${firstName}, ${lastName}, ${username}, ${email}, ${nationality}, ${dateOfBirth}, ${passwordHash}, ${true}, ${0})
            RETURNING id
        `

        return [true, 'New user successfully created', response[0]]
    }
    catch(error) {
        return [false, error, null]
    }
}

async function getUserByUsername(username) {
    try {
        const response = await sql`
            SELECT *
            FROM "users"
            WHERE "username" = ${username}
        `

        if(response.length === 0) {
            return [true, 'User with entered username does not exist', null]
        }

        return [true, 'User with entered username found', response[0]]
    }
    catch(error) {
        return [false, error, null]
    }
}

async function deleteUser(id) {
    try {
        await sql`
            UPDATE "users"
            SET "active" = ${false}
            WHERE "id" = ${id}
        `

        return [true, 'User successfully deleted']
    }
    catch(error) {
        return [false, error]
    }
}

async function getUserById(id) {
    try {
        const response = await sql`
            SELECT *
            FROM "users"
            WHERE "id" = ${id}
        `

        if(response.length === 0) {
            return [true, 'User with entered id does not exist', null]
        }

        return [true, 'User with entered id found', response[0]]
    }
    catch(error) {
        return [false, error, null]
    }
}

async function editUser(id, firstName, lastName, username, email, nationality, dateOfBirth) {
    try {
        await sql`
            UPDATE "users"
            SET "firstName" = ${firstName}, "lastName" = ${lastName}, "username" = ${username}, "email" = ${email}, "nationality" = ${nationality}, "dateOfBirth" = ${dateOfBirth},
            WHERE "id" = ${id}
        `

        return [true, 'User successfully edited']
    }
    catch(error) {
        return [false, error]
    }
}

async function getUserRecords(id) {
    try {
        const response = await sql`
            SELECT
                CAST(COUNT(*) FILTER (WHERE "recordUserId" = ${id}) AS INTEGER) AS "numberOfRecords"
            FROM "puzzles"
            GROUP BY "recordUserId"
        `

        if(response.length === 0) {
            return [true, 'User records found', {numberOfRecords: 0}]
        }

        return [true, 'User records found', response[0]]
    }
    catch(error) {
        return [false, error, null]
    }
}

async function editUserPoints(id, oldPoints, newPoints) {
    try {
        await sql`
            UPDATE "users"
            SET "points" = ${oldPoints + newPoints}
            WHERE "id" = ${id}
        `

        return [true, 'User points successfully edited']
    }
    catch(error) {
        return [false, error]
    }
}

async function createPuzzlesTable() {
    try {
        await sql`
            CREATE TABLE "puzzles" (
                "id" serial PRIMARY KEY,
                "string" varchar NOT NULL,
                "solvedString" varchar NOT NULL,
                "difficulty" integer NOT NULL,
                "creationDate" date NOT NULL,
                "creationUserId" integer NOT NULL,
                "recordUserId" integer,
                "recordTime" integer,
                "recordDate" date,
                CONSTRAINT "fkCreationUserId"
                    FOREIGN KEY ("creationUserId")
                    REFERENCES "users"("id"),
                CONSTRAINT "fkRecordUserId"
                    FOREIGN KEY ("recordUserId")
                    REFERENCES "users"("id")
            )
        `

        return [true, `Table puzzles created successfully`]
    }
    catch(error) {
        return [false, error]
    }
}

async function getPuzzleByString(string) {
    try {
        const response = await sql`
            SELECT *
            FROM "puzzles"
            WHERE "string" = ${string}
        `
        
        if(response.length === 0) {
            return [true, 'Puzzle with entered string does not exist', null]
        }

        return [true, 'Puzzle with entered string found', response[0]]
    }
    catch(error) {
        return [false, error, null]
    }
}

async function createNewPuzzle(string, solvedString, difficulty, creationDate, creationUserId) {
    try {
        await sql`
            INSERT INTO "puzzles"("string", "solvedString", "difficulty", "creationDate", "creationUserId", "recordUserId", "recordTime", "recordDate")
            VALUES(${string}, ${solvedString}, ${difficulty}, ${creationDate}, ${creationUserId}, ${null}, ${null}, ${null})
        `

        return [true, 'New puzzle successfully created']
    }
    catch(error) {
        return [false, error]
    }
}

async function getPuzzleById(id) {
    try {
        const response = await sql`
            SELECT *
            FROM "puzzles"
            WHERE "id" = ${id}
        `

        if(response.length === 0) {
            return [true, 'Puzzle with entered id does not exist', null]
        }

        return [true, 'Puzzle with entered id found', response[0]]
    }
    catch(error) {
        return [false, error, null]
    }
}

async function editPuzzleRecord(id, recordUserId, recordTime, recordDate) {
    try {
        await sql`
            UPDATE "puzzles"
            SET "recordUserId" = ${recordUserId}, "recordTime" = ${recordTime}, "recordDate" = ${recordDate}
            WHERE "id" = ${id}
        `

        return [true, 'Puzzle record successfully edited']
    }
    catch(error) {
        return [false, error]
    }
}

async function getPuzzlesByDifficultyAndPage(difficulty, page) {
    try {
        const response = await sql`
            SELECT *
            FROM "puzzles"
            WHERE "difficulty" = ${difficulty}
            ORDER BY "creationDate" DESC
            LIMIT 10
            OFFSET ${(page - 1) * 10}
        `

        return [true, 'Puzzles by difficulty and page found', response]
    }
    catch(error) {
        return [false, error, null]
    }
}

async function createAttemptsTable() {
    try {
        await sql`
            CREATE TABLE "attempts" (
                "id" serial PRIMARY KEY,
                "userId" integer NOT NULL,
                "puzzleId" integer NOT NULL,
                "date" date NOT NULL,
                "completion" boolean NOT NULL,
                "time" integer NOT NULL,
                CONSTRAINT "fkUserId"
                    FOREIGN KEY ("userId")
                    REFERENCES "users"("id"),
                CONSTRAINT "fkPuzzleId"
                    FOREIGN KEY ("puzzleId")
                    REFERENCES "puzzles"("id")
            )
        `

        return [true, `Table attempts created successfully`]
    }
    catch(error) {
        return [false, error]
    }
}

async function createNewAttempt(userId, puzzleId, date, completion, time) {
    try {
        await sql`
            INSERT INTO "attempts"("userId", "puzzleId", "date", "completion", "time")
            VALUES(${userId}, ${puzzleId}, ${date}, ${completion}, ${time})
        `

        return [true, 'New attempt successfully created']
    }
    catch(error) {
        return [false, error]
    }
}

async function getAttemptsByUserIdAndPuzzleId(userId, puzzleId) {
    try {
        const response = await sql`
            SELECT *
            FROM "attempts"
            WHERE "userId" = ${userId} AND "puzzleId" = ${puzzleId}
        `

        return [true, 'Attempts with entered user id and puzzle id found', response]
    }
    catch(error) {
        return [false, error, null]
    }
}

async function getStatisticsByPuzzleIds(puzzleIds) {
    try {
        const response = await sql`
            SELECT
                "puzzleId",
                CAST(COUNT(*) FILTER (WHERE "completion" = ${true}) AS INTEGER) AS "totalSuccessAttempts",
                CAST(COUNT(*) FILTER (WHERE "completion" = ${false}) AS INTEGER) AS "totalFailureAttempts"
            FROM "attempts"
            WHERE "puzzleId" = ANY(${puzzleIds})
            GROUP BY "puzzleId"
        `

        return [true, 'Puzzle statistics found', response]
    }
    catch(error) {
        return [false, error, null]
    }
}

async function getStatisticsByUserId(userId) {
    try {
        const response = await sql`
            SELECT
                CAST(COUNT(*) FILTER (WHERE "completion" = ${true}) AS INTEGER) AS "successAttempts",
                CAST(COUNT(*) FILTER (WHERE "completion" = ${false}) AS INTEGER) AS "failureAttempts"
            FROM "attempts"
            WHERE "userId" = ${userId}
            GROUP BY "userId"
        `

        if(response.length === 0) {
            return [true, 'User statistics found', {successAttempts: 0, failureAttempts: 0}]
        }

        return [true, 'User statistics found', response[0]]
    }
    catch(error) {
        return [false, error, null]
    }
}

async function getStatisticsByUserIdAndPuzzleIds(userId, puzzleIds) {
    try {
        const response = await sql`
            SELECT
                "puzzleId",
                CAST(COUNT(*) FILTER (WHERE "completion" = ${true}) AS INTEGER) AS "userSuccessAttempts",
                CAST(COUNT(*) FILTER (WHERE "completion" = ${false}) AS INTEGER) AS "userFailureAttempts"
            FROM "attempts"
            WHERE "userId" = ${userId} AND "puzzleId" = ANY(${puzzleIds})
            GROUP BY "puzzleId"
        `

        return [true, 'Statistics by user id and puzzle ids found', response]
    }
    catch(error) {
        return [false, error, null]
    }
}

module.exports = {
    verifyTableExistance,
    createUsersTable,
    getUserByEmail,
    createNewUser,
    getUserByUsername,
    deleteUser,
    getUserById,
    editUser,
    getUserRecords,
    editUserPoints,
    createPuzzlesTable,
    getPuzzleByString,
    createNewPuzzle,
    getPuzzleById,
    editPuzzleRecord,
    getPuzzlesByDifficultyAndPage,
    createAttemptsTable,
    createNewAttempt,
    getAttemptsByUserIdAndPuzzleId,
    getStatisticsByPuzzleIds,
    getStatisticsByUserId,
    getStatisticsByUserIdAndPuzzleIds
}