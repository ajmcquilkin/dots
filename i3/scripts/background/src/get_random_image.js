const createApi = require('./create_api.js')

createApi().then(unsplash => {
	unsplash.photos.getRandom().then(({ response, errors }) => {
		if (errors) throw new Error("background fetching failed")
		console.log(response.urls.full)
	})
})
