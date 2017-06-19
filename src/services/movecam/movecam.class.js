const exec = require('child_process').exec;
const logger = require('winston');
const path = './python/movecam.py';

/* eslint-disable no-unused-vars */
class Service {
  constructor (options) {
    this.options = options || {};
  }

  get (id, params) {
    logger.info("id: " + id);
    var cmd = 'python ' + path + ' ' + id;
    exec(cmd, function(err,stdout,stderr) {
      if( err ) { logger.debug(err); }
      if( stdout ) { logger.info(stdout); }
      if( stderr ) { logger.debug(stderr); }
    });

    return Promise.resolve({

    });
  }
}

module.exports = function (options) {
  return new Service(options);
};

module.exports.Service = Service;
