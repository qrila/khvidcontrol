const logger = require('winston');
const queryPosition = require('../../camctrl/visca').queryPosition;

module.exports = {
  before: {
    all: [],
    find: [],
    get: [],
    create: [
      function(hook) {
        return new Promise((resolve, reject) => {
          const newHook = new Promise((resolve, reject) => {
           resolve(queryPosition());
           reject('no new position');
          }).then((newPosition) => {
            logger.info('Got new position: ', newPosition);
            hook.data.pantilt = newPosition[0];
            hook.data.zoom = newPosition[1];
            return hook;
          });
          resolve(newHook);
          reject('error');
        });
      }
    ],
    update: [],
    patch: [],
    remove: []
  },

  after: {
    all: [],
    find: [],
    get: [],
    create: [],
    update: [],
    patch: [],
    remove: []
  },

  error: {
    all: [],
    find: [],
    get: [],
    create: [],
    update: [],
    patch: [],
    remove: []
  }
};
