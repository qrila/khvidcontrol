const movecam = require('./movecam/movecam.service.js');
module.exports = function () {
  const app = this; // eslint-disable-line no-unused-vars
  app.configure(movecam);
};
