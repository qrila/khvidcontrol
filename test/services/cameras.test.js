const assert = require('assert');
const app = require('../../src/app');

describe('\'cameras\' service', () => {
  it('registered the service', () => {
    const service = app.service('cameras');

    assert.ok(service, 'Registered the service');
  });
});
