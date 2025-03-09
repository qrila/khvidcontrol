const NeDB = require('@seald-io/nedb')
const path = require('path');

module.exports = function (app) {
  const dbPath = app.get('nedb');
  const Model = new NeDB({
    filename: path.join(dbPath, 'overlay.db'),
    autoload: true
  });

  return Model;
};
