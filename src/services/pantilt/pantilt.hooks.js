var exec = require('child_process').exec;
var path = './python/movecam.py';

module.exports = {
  before: {
    all: [],
    find: [],
    get: [
      function(hook){
        console.log("id: " + hook.id);
        var cmd = 'python ' + path + ' ' + hook.id;
        exec(cmd, function(err,stdout,stderr) {
          if( err ) console.log(err);
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
