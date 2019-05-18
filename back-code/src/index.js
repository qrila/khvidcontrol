/* eslint-disable no-console */
const logger = require('winston');
const app = require('./app');
const port = app.get('port');
const server = app.listen(port);

const fs = require('fs');
const { spawn } = require('child_process');

// start webrtc-streamer if the executable exists
const webrtc_path = './bin/webrtc-streamer.exe'; // TODO: mac/linux binary support
if (fs.existsSync(webrtc_path))
{
  const webrtc_silent = true; // set to false if you want to see webrtc-streamer stdout,err

  const webrtc_port = 3038; // TODO: take from settings
  const opts = {};
  // Not sure if this worked properly:
  //if (webrtc_silent) {
  //    opts.stdio = 'ignore';
  //}

  const webrtc_host_port = `${app.get('host')}:${webrtc_port}`;
  logger.info(`Starting webrtc-streamer on ${webrtc_host_port}`);
  const webrtc = spawn(webrtc_path, ['-H', webrtc_host_port], opts);

  webrtc.stdout.on('data', (data) => {
    if (!webrtc_silent)
      logger.info(`webrtc-streamer: ${data}`);
  });
  webrtc.stderr.on('data', (data) => {
    if (!webrtc_silent)
      logger.error(`webrtc-streamer: ${data}`);
  });

  webrtc.on('close', (code) => {
    logger.info(`webrtc-streamer process exited with code ${code}`);
  });
}
else
{
  logger.info('Not starting webrtc-streamer (binary not found)');
}

process.on('unhandledRejection', (reason, p) =>
  logger.error('Unhandled Rejection at: Promise ', p, reason)
);

server.on('listening', () =>
  logger.info(`Feathers application started on ${app.get('host')}:${port}`)
);
