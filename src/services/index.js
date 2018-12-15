const movecam = require('./movecam/movecam.service.js');
const positions = require('./positions/positions.service.js');
const videoinputs = require('./videoinputs/videoinputs.service.js');
const mixerinputs = require('./mixerinputs/mixerinputs.service.js');
const videomixer = require('./videomixer/videomixer.service.js');
const cameras = require('./cameras/cameras.service.js');
module.exports = function () {
  const app = this; // eslint-disable-line no-unused-vars
  app.configure(movecam);
  app.configure(positions);
  app.configure(videoinputs);
  app.configure(mixerinputs);
  app.configure(videomixer);
  app.configure(cameras);
};
