const exec = require('child_process').exec;
const logger = require('winston');
const pycmd = 'python ./python/querypos.py';

module.exports = {
  before: {
    all: [],
    find: [],
    get: [],
    create: [
      function(hook) {
        return new Promise((resolve, reject) => {
          var cmd = pycmd;
          exec(cmd, function(err,stdout,stderr) {
            if( err ) { return reject(err) }
            if( stderr ) { return reject(stderr); }

            hook.data.cameraPosition = JSON.parse(stdout);
            resolve(hook);
          });
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
