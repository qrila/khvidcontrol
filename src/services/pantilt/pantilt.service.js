// Initializes the `pantilt` service on path `/pantilt`
const createService = require('./pantilt.class.js');
const hooks = require('./pantilt.hooks');
const filters = require('./pantilt.filters');

module.exports = function () {
  const app = this;
  const paginate = app.get('paginate');

  const options = {
    name: 'pantilt',
    paginate
  };

  // Initialize our service with any options it requires
  app.use('/pantilt', createService(options));

  // Get our initialized service so that we can register hooks and filters
  const service = app.service('pantilt');

  service.hooks(hooks);

  if (service.filter) {
    service.filter(filters);
  }
};
