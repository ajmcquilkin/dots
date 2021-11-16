const { promises: fs } = require('fs')
const nodeFetch = require('node-fetch')
const { createApi } = require('unsplash-js')

const DEFAULT_ACCESS_KEY_LOCATION = '/home/ajmcquilkin/.config/i3/scripts/background/src/ACCESS_KEY'
const DEFAULT_SECRET_KEY_LOCATION = '/home/ajmcquilkin/.config/i3/scripts/background/src/SECRET_KEY'

module.exports = async function(ak = DEFAULT_ACCESS_KEY_LOCATION, sk = DEFAULT_SECRET_KEY_LOCATION) {
	const accessKey = (await fs.readFile(ak, "utf8")).replace(/[\n]/g, '')
	const secretKey = (await fs.readFile(sk, "utf8")).replace(/[\n]/g, '')

	if (!accessKey || !secretKey) throw new Error("key loading failed")

	const api = createApi({ accessKey, fetch: nodeFetch })
	return api
}
