// Initializes the `mixerinputs` service on path `/mixerinputs`
const createService = require("./mixerinputs.class.js");
const hooks = require("./mixerinputs.hooks");
const ATEM = require("applest-atem");

module.exports = function () {
  const app = this;
  const paginate = app.get("paginate");
  const atem = new ATEM();

  const options = {
    name: "mixerinputs",
    paginate,
    app,
    atem,
  };

  // Initialize our service with any options it requires
  app.use(
    "/mixerinputs",
    createService({ name: "mixerinputs", paginate, app, atem })
  );

  // Get our initialized service so that we can register hooks and filters
  const service = app.service("mixerinputs");

  service.hooks(hooks);
};
