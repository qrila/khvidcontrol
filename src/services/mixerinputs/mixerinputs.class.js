// const logger = require('winston');

/* eslint-disable no-unused-vars */
class Service {
  constructor (options) {
    this.options = options || {};
  }

  get (data) {
    return new Promise((resolve, reject) => {
      const app = this.options.app;
      const input = JSON.parse(data);
      const atem = this.options.atem;

      mixerIP(app).then( (mixerIP) => {
        if(atem.state.model) {
          atemCmd(input, atem);
        } else {
          atem.connect(mixerIP);
          atem.on('connect', () => {
            atemCmd(input, atem);
          });
        }

        resolve('200');
        reject('no mixer');
      });
    });
  }
}

async function mixerIP(app) {
  const mixer = await app.service('videomixer').find();
  return(mixer.data[0].videomixerIP);
}

async function atemCmd(input, atem) {
  if(input.mixerAUX) {
    // set aux to program output or input number 1
    const auxMode = input.mixerAUX === 'program' ? 10010 : 1;
    return atem.changeAuxInput(0, auxMode);
  } 
  else if (input.cut == true) {
	return atem.cutTransition(0);
  }
  else {
    // set program output to given input number
    return atem.changePreviewInput(input.mixerInput);
  }
}

module.exports = function (options) {
  return new Service(options);
};

module.exports.Service = Service;
