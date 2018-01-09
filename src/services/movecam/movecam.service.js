// Initializes the `movecam` service on path `/movecam`
const createService = require('./movecam.class.js');
const hooks = require('./movecam.hooks');

module.exports = function () {
  const app = this;
  const paginate = app.get('paginate');

  const options = {
    name: 'movecam',
    paginate
  };

  // Initialize our service with any options it requires
  app.use('/movecam', createService(options));

  // Get our initialized service so that we can register hooks and filters
  const service = app.service('movecam');

  service.hooks(hooks);
};
