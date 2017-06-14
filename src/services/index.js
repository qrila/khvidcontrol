const pantilt = require('./pantilt/pantilt.service.js');
module.exports = function () {
  const app = this; // eslint-disable-line no-unused-vars
  app.configure(pantilt);
};
