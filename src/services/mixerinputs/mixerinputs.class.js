const logger = require('winston');

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
        if(input.mixerAUX) {
          // set aux to program output or input number 1
          logger.info(mixerIP, `aux setting: ${input.mixerAUX}`);
        } else {
          // set program output to given input number
          logger.info(mixerIP, `input setting: ${input.mixerInput}`);
        }

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
