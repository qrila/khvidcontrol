const assert = require('assert');
const app = require('../../src/app');

describe('\'mixerinputs\' service', () => {
  it('registered the service', () => {
    const service = app.service('mixerinputs');

    assert.ok(service, 'Registered the service');
  });
});
