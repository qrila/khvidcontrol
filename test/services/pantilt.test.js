const assert = require('assert');
const app = require('../../src/app');

describe('\'pantilt\' service', () => {
  it('registered the service', () => {
    const service = app.service('pantilt');

    assert.ok(service, 'Registered the service');
  });
});
