const logger = require('winston');
const exec = require('child_process').exec;
const atemi = require('applest-atem');

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
        
      
      var atem = new atemi();
	  atem.connect(mixerIP);
      atem.on('connect', function() {
      	atem.changeProgramInput('mixerAUX' in input ? input.mixerAUX : input.mixerInput); // ME1(0)
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
