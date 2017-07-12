// Initializes the `videoinputs` service on path `/videoinputs`
const createService = require('feathers-nedb');
const createModel = require('../../models/videoinputs.model');
const hooks = require('./videoinputs.hooks');
const filters = require('./videoinputs.filters');

module.exports = function () {
  const app = this;
  const Model = createModel(app);
  const paginate = app.get('paginate');

  const options = {
    name: 'videoinputs',
    Model,
    paginate
  };

  // Initialize our service with any options it requires
  app.use('/videoinputs', createService(options));

  // Get our initialized service so that we can register hooks and filters
  const service = app.service('videoinputs');

  service.hooks(hooks);

  if (service.filter) {
    service.filter(filters);
  }
};
