const exec = require('child_process').exec;
const logger = require('winston');
const path = './python/movecam.py';

module.exports = {
  before: {
    all: [],
    find: [],
    get: [
      function(hook){
        var cmd = 'python ' + path + ' ' + hook.id;
        exec(cmd, function(err,stdout,stderr) {
          if( err ) { logger.debug(err); }
          if( stdout ) { logger.info(stdout); }
          if( stderr ) { logger.debug(stderr); }
        });
      }
    ],
    create: [],
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
