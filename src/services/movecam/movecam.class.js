const logger = require('winston');
const moveCam = require('../../camctrl/visca').moveCam;

/* eslint-disable no-unused-vars */
class Service {
  constructor (options) {
    this.options = options || {};
  }

  get (id, params) {
    logger.info(`${id} :: ${params.query.data}`);
    moveCam(id, params.query.data);
    return Promise.resolve({});
  }
}

module.exports = function (options) {
  return new Service(options);
};

module.exports.Service = Service;
