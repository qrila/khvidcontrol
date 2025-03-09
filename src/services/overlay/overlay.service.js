// Initializes the `positions` service on path `/positions`
const createService = require("feathers-nedb");
const createModel = require("../../models/overlay.model");
const hooks = require("./overlay.hooks");

module.exports = function () {
  const app = this;
  const Model = createModel(app);
  const paginate = app.get("paginate");

  // Initialize our service with any options it requires
  app.use(
    "/overlay",
    createService({
      name: "overlay",
      Model,
      paginate,
    })
  );

  // Get our initialized service so that we can register hooks and filters
  const service = app.service("overlay");

  service.hooks(hooks);
};
