const assert = require('assert');
const app = require('../../src/app');

describe('\'movecam\' service', () => {
  it('registered the service', () => {
    const service = app.service('movecam');

    assert.ok(service, 'Registered the service');
  });
});
