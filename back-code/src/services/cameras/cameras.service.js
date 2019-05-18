// Initializes the `cameras` service on path `/cameras`
const createService = require('feathers-nedb');
const createModel = require('../../models/cameras.model');
const hooks = require('./cameras.hooks');

module.exports = function (app) {
  const Model = createModel(app);
  const paginate = app.get('paginate');

  const options = {
    Model,
    paginate
  };

  // Initialize our service with any options it requires
  app.use('/cameras', createService(options));

  // Get our initialized service so that we can register hooks
  const service = app.service('cameras');

  service.hooks(hooks);
};
