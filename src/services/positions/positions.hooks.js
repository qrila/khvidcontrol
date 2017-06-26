const exec = require('child_process').exec;
const logger = require('winston');
const pycmd = 'python ./python/viscactrl.py -q saveposition';

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

            var cameraID = ("8" + hook.data.camera).toString('hex');
            var pantilt = JSON.parse(stdout)["pantilt"].slice(2,10).map(function(item){
              item = parseInt(item.replace(/^0x/, ''), 16);
              return (0 + item.toString(16)).substr(-2).toString('hex');
            });
            var zoom = JSON.parse(stdout)["zoom"].slice(2,6).map(function(item){
              item = parseInt(item.replace(/^0x/, ''), 16);
              return (0 + item.toString(16)).substr(-2).toString('hex');
            });
            hook.data.pantilt = pantilt.toString();
            hook.data.zoom = zoom.toString();

            console.log("camera id: " + hook.data.camera + "\npantilt: " + hook.data.pantilt + "\nzoom: " + hook.data.zoom);
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
