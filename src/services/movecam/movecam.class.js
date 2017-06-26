const exec = require('child_process').exec;
const logger = require('winston');
const pycmd = 'python ./python/viscactrl.py';

/* eslint-disable no-unused-vars */
class Service {
  constructor (options) {
    this.options = options || {};
  }

  get (id, params) {
    var cmd = pycmd + ' -' + id + ' ' + params.query.data;
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
