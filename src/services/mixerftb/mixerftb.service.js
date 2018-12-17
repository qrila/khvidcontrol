// Initializes the `mixerinputs` service on path `/mixerinputs`
const createService = require('./mixerftb.class.js');
const hooks = require('./mixerftb.hooks');

module.exports = function () {
  const app = this;
  const paginate = app.get('paginate');

  const options = {
    name: 'mixerftb',
    paginate
  };

  // Initialize our service with any options it requires
  app.use('/mixerftb', createService(options));

  // Get our initialized service so that we can register hooks and filters
  const service = app.service('mixerinputs');

  service.hooks(hooks);
};