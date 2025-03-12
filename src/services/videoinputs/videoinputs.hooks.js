const logger = require('winston');

module.exports = {
  before: {
    all: [],
    find: [],
    get: [],
    create: [
      // function(hook) {
      //   logger.info(hook.data);
      // }
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
