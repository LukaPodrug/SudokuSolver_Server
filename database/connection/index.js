const postgres = require('postgres')

const pgHost = process.env.PG_HOST
const pgDatabase = process.env.PG_DATABASE
const pgUser = process.env.PG_USER
const pgPassword = process.env.PG_PASSWORD
const endpointId = process.env.ENDPOINT_ID

const connectionString = `postgres://${pgUser}:${pgPassword}@${pgHost}/${pgDatabase}?options=project%3D${endpointId}`

const sql = postgres(connectionString, {ssl: 'require'})

module.exports = sql