const assert = require('assert');
const app = require('../../src/app');

describe('\'videoinputs\' service', () => {
  it('registered the service', () => {
    const service = app.service('videoinputs');

    assert.ok(service, 'Registered the service');
  });
});
