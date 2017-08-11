// Initializes the `mixerinputs` service on path `/mixerinputs`
const createService = require('./mixerinputs.class.js');
const hooks = require('./mixerinputs.hooks');
const filters = require('./mixerinputs.filters');

module.exports = function () {
  const app = this;
  const paginate = app.get('paginate');

  const options = {
    name: 'mixerinputs',
    paginate
  };

  // Initialize our service with any options it requires
  app.use('/mixerinputs', createService(options));

  // Get our initialized service so that we can register hooks and filters
  const service = app.service('mixerinputs');

  service.hooks(hooks);

  if (service.filter) {
    service.filter(filters);
  }
};
