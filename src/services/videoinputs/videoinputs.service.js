// Initializes the `videoinputs` service on path `/videoinputs`
const createService = require("feathers-nedb");
const createModel = require("../../models/videoinputs.model");
const hooks = require("./videoinputs.hooks");

module.exports = function () {
  const app = this;
  const Model = createModel(app);
  const paginate = app.get("paginate");

  // Initialize our service with any options it requires
  app.use(
    "/videoinputs",
    createService({ name: "videoinputs", Model, paginate })
  );

  // Get our initialized service so that we can register hooks and filters
  const service = app.service("videoinputs");

  service.hooks(hooks);
};
