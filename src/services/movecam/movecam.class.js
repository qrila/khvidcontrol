const logger = require('winston');
const visca = require('../../camctrl/visca');

/* eslint-disable no-unused-vars */
class Service {
  constructor (options) {
    this.options = options || {};
  }

  get (data) {
    return new Promise((resolve, reject) => {
      const app = this.options.app;
      const camData = JSON.parse(data);

      if(camData.command === 'preset') {
        setPosition(app, camData.positionID).then( (presetPosition) => {
          camera(app, presetPosition.cameraID).then( (cameraIP) => {
            visca.preset(cameraIP, presetPosition.pantilt, presetPosition.zoom);
          });
        }).then( () => {
          resolve('200');
          reject('preset error');
        });
      } else if(camData.command === 'save') {
        camera(app, camData.cameraID).then( cameraIP => {
          visca.queryPosition(cameraIP).then( (result) => {
            savePosition(app, camData.cameraID, camData.subjectName, result.pantilt, result.zoom);
          });
        }).then( () => {
          resolve('200');
          reject('save position error');
        });
      } else {
        camera(app, camData.cameraID).then( cameraIP => {
          visca.moveCam(camData.action, cameraIP);
        }).then( () => {
          resolve('200');
          reject('move error');
        });
      }
    });
  }
}

async function camera(app, id) {
  const camera = await app.service('cameras').get(id);
  return camera.cameraIP;
}

async function savePosition(app, cameraID, subjectName, pantilt, zoom) {
  const sortNumber = await app.service('positions').find();
  const position = await app.service('positions').create({
    sortNumber: sortNumber.total,
    cameraID: cameraID,
    subjectName: subjectName,
    pantilt: pantilt.slice(4,20).match(/.{1,2}/g).map(y => { return('0x' + y); }),
    zoom: zoom.slice(4,12).match(/.{1,2}/g).map(y => { return('0x' + y); })
  });
  return position;
}

async function setPosition(app, id) {
  const position = await app.service('positions').get(id);
  return ({cameraID: position.cameraID, pantilt: position.pantilt, zoom: position.zoom});
}

module.exports = function (options) {
  return new Service(options);
};

module.exports.Service = Service;
