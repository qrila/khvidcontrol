// const logger = require('winston');
const visca = require('../../camctrl/visca');

/* eslint-disable no-unused-vars */
class Service {
  constructor(options) {
    this.options = options || {};
  }

  get(data) {
    return new Promise((resolve, reject) => {
      const app = this.options.app;
      const camData = JSON.parse(data);

      if (camData.command === 'preset') {
        setPosition(app, camData.positionID).then((presetPosition) => {
          camera(app, presetPosition.cameraID).then((cameraIP) => {
            visca.preset(cameraIP, presetPosition.pantilt, presetPosition.zoom);
          });
        }).then(() => {
          resolve('200');
          reject('preset error');
        });
      } else if (camData.command === 'save') {
        camera(app, camData.cameraID).then(cameraIP => {
          visca.queryPosition(cameraIP).then((result) => {
            savePosition(
              app,
              camData.cameraID,
              camData.subjectName,
              result.pantilt,
              result.zoom
            );
          });
        }).then(() => {
          resolve('200');
          reject('save position error');
        });
      } else if (camData.command === 'edit') {
        editPositionArguments(
          app,
          camData.positionID,
          camData.visibilityMode,
          camData.subjectName,
          camData.sortdir,
          camData.cameraID
        ).then(
          () => {
            resolve('200');
            reject('edit position error');
          }
        );
      } else if (camData.command === 'cmd') {
        camera(app, camData.cameraID).then(cameraIP => {
          visca.moveCam(camData.action, cameraIP);
        }).then(() => {
          resolve('200');
          reject('move error');
        });
      } else if (camData.command === 'remove') {
        removePosition(app, camData.positionID).then((success) => {
          if (success) resolve('200');
          else reject('position delete error');
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
  const buttons = await app.service('positions').find({
    query: {
      visibilityMode: 'button'
    }
  });
  const biggest = Math.max(...buttons.data.map(button => button.sortNumber));
  const position = await app.service('positions').create({
    sortNumber: biggest + 1,
    cameraID: cameraID,
    subjectName: subjectName,
    visibilityMode: 'button',
    pantilt: pantilt.slice(4, 20).match(/.{1,2}/g).map(y => { return ('0x' + y); }),
    zoom: zoom.slice(4, 12).match(/.{1,2}/g).map(y => { return ('0x' + y); })
  });
  return position;
}

async function setPosition(app, id) {
  const position = await app.service('positions').get(id);
  return ({ cameraID: position.cameraID, pantilt: position.pantilt, zoom: position.zoom });
}

async function editPositionArguments(app, positionID, visibilityMode, subjectName, sortdir, cameraID) {
  if (visibilityMode !== undefined) {
    const buttons = await app.service('positions').find({
      query: {
        visibilityMode: visibilityMode
      }
    });
    const biggest = Math.max(...buttons.data.map(button => button.sortNumber));
    app.service('positions').patch(positionID, {
      visibilityMode: visibilityMode,
      sortNumber: biggest + 1
    });
  } else if (subjectName !== undefined) {
    app.service('positions').patch(positionID, {
      subjectName: subjectName
    });
  } else if (sortdir !== undefined) {
    const buttons = await app.service('positions').find({
      query: {
        visibilityMode: 'button'
      }
    });

    const sorted = buttons.data.sort((a, b) => parseInt(a.sortNumber) - parseInt(b.sortNumber));
    const positionSort = sorted.find(button => button._id === positionID);
    const modifiedSort = await modifySorting(sorted, positionSort, sortdir);

    modifiedSort.forEach(position => {
      if (position.sortNumber !== sorted.find(s => s._id === position._id).sortNumber) {
        app.service('positions').patch(position._id, {
          sortNumber: position.sortNumber
        });
      }
    });
  } else if (cameraID !== undefined) {
    camera(app, cameraID).then(cameraIP => {
      visca.queryPosition(cameraIP).then((result) => {
        app.service('positions').patch(positionID, {
          pantilt: result.pantilt.slice(4, 20).match(/.{1,2}/g).map(y => { return ('0x' + y); }),
          zoom: result.zoom.slice(4, 12).match(/.{1,2}/g).map(y => { return ('0x' + y); })
        });
      });
    });
  }
}

async function modifySorting(buttons, position, sortdir) {
  const swapPositions = (array, a, b) => {
    [array[a], array[b]] = [array[b], array[a]];
  };
  const positionIdx = buttons.findIndex(b => b._id === position._id);

  if (sortdir === 'up') {
    swapPositions(buttons, positionIdx - 1, positionIdx);
  } else if (sortdir === 'down') {
    swapPositions(buttons, positionIdx, positionIdx + 1);
  }

  const modifyButtons = checkOrderNumbering(buttons);

  return modifyButtons;
}

function checkOrderNumbering(buttons) {
  let checkedOrder = [];
  buttons.forEach((b, id) => {
    if (id > 0) {
      checkedOrder.push({ 'sortNumber': id, '_id': b._id });
    }
  });

  return checkedOrder;
}

async function removePosition(app, id) {
  await app.service('positions').remove(id);
  const buttons = await app.service('positions').find({
    query: {
      visibilityMode: 'button'
    }
  });
  patchButtonOrder(app, buttons.data);

  return true;
}

async function patchButtonOrder(app, buttons) {
  const sorted = buttons.sort((a, b) => parseInt(a.sortNumber) - parseInt(b.sortNumber));
  sorted.forEach((button, id) => {
    if (button.sortNumber !== id) {
      app.service('positions').patch(button._id, {
        sortNumber: id
      });
    }
  });
}

module.exports = function (options) {
  return new Service(options);
};

module.exports.Service = Service;
