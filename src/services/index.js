const movecam = require('./movecam/movecam.service.js');
const positions = require('./positions/positions.service.js');
module.exports = function () {
  const app = this; // eslint-disable-line no-unused-vars
  app.configure(movecam);
  app.configure(positions);
};
