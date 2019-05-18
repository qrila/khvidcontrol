const assert = require('assert');
const app = require('../../src/app');

describe('\'positions\' service', () => {
  it('registered the service', () => {
    const service = app.service('positions');

    assert.ok(service, 'Registered the service');
  });
});
