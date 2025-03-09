// Initializes the `positions` service on path `/positions`
const createService = require("feathers-nedb");
const createModel = require("../../models/positions.model");
const hooks = require("./positions.hooks");

module.exports = function () {
  const app = this;
  const Model = createModel(app);
  const paginate = app.get("paginate");

  // Initialize our service with any options it requires
  app.use(
    "/positions",
    createService({
      Model,
      paginate,
    })
  );

  // Get our initialized service so that we can register hooks and filters
  const service = app.service("positions");

  service.hooks(hooks);
};
