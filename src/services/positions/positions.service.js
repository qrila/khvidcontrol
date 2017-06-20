// Initializes the `positions` service on path `/positions`
const createService = require('feathers-nedb');
const createModel = require('../../models/positions.model');
const hooks = require('./positions.hooks');
const filters = require('./positions.filters');

module.exports = function () {
  const app = this;
  const Model = createModel(app);
  const paginate = app.get('paginate');

  const options = {
    name: 'positions',
    Model,
    paginate
  };

  // Initialize our service with any options it requires
  app.use('/positions', createService(options));

  // Get our initialized service so that we can register hooks and filters
  const service = app.service('positions');

  service.hooks(hooks);

  if (service.filter) {
    service.filter(filters);
  }
};
