const logger = require('winston');
const exec = require('child_process').exec;
const pycmd = 'python ./python/atemctrl.py';

/* eslint-disable no-unused-vars */
class Service {
  constructor (options) {
    this.options = options || {};
  }

  get (data) {
    return new Promise((resolve, reject) => {
      const app = this.options.app;
      const input = JSON.parse(data);

      mixerIP(app).then( (mixerIP) => {
        const cmd = pycmd + ' ' + mixerIP + ' ' + ('mixerAUX' in input ? input.mixerAUX : input.mixerInput);
        // logger.info(cmd);
        exec(cmd, function(err,stdout,stderr) {
          if( err ) { logger.debug(err); }
          if( stdout ) { logger.info(stdout); }
          if( stderr ) { logger.debug(stderr); }
        });

        resolve();
        reject('no mixer');
      });
    });
  }
}

async function mixerIP(app) {
  const mixer = await app.service('videomixer').find();
  return(mixer.data[0].videomixerIP);
}

module.exports = function (options) {
  return new Service(options);
};

module.exports.Service = Service;
