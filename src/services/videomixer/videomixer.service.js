// Initializes the `videomixer` service on path `/videomixer`
const createService = require('feathers-nedb');
const createModel = require('../../models/videomixer.model');
const hooks = require('./videomixer.hooks');

module.exports = function (app) {
  const Model = createModel(app);
  const paginate = app.get('paginate');

  const options = {
    Model,
    paginate
  };

  // Initialize our service with any options it requires
  app.use('/videomixer', createService(options));

  // Get our initialized service so that we can register hooks
  const service = app.service('videomixer');

  service.hooks(hooks);
};
