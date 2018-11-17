const exec = require('child_process').exec;
const logger = require('winston');
const pycmd = 'python ./python/atemctrl.py';

/* eslint-disable no-unused-vars */
class Service {
  constructor (options) {
    this.options = options || {};
  }

  get (params) {

    const mixerip = params.split('::')[0];
    const param_2 = params.split('::')[1];
    // param_2 is either progmam input or selection of AUX output source selection.

    var cmd = pycmd + ' ' + mixerip + ' ' + param_2;
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
