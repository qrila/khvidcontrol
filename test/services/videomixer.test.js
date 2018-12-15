const assert = require('assert');
const app = require('../../src/app');

describe('\'videomixer\' service', () => {
  it('registered the service', () => {
    const service = app.service('videomixer');

    assert.ok(service, 'Registered the service');
  });
});
