// const logger = require('winston');
const dgram = require('dgram');

const commandList = {
  'powerON': [0x81, 0x01, 0x04, 0x00, 0x02, 0xFF],
  'powerOFF': [0x81, 0x01, 0x04, 0x00, 0x03, 0xFF],
  'moveStop': [0x81, 0x01, 0x06, 0x01, 0x18, 0x14, 0x03, 0x03, 0xFF],
  'moveUp': [0x81, 0x01, 0x06, 0x01, 0x01, 0x07, 0x03, 0x01, 0xFF],
  'moveLeft': [0x81, 0x01, 0x06, 0x01, 0x09, 0x01, 0x01, 0x03, 0xFF],
  'moveRight': [0x81, 0x01, 0x06, 0x01, 0x09, 0x01, 0x02, 0x03, 0xFF],
  'moveDown': [0x81, 0x01, 0x06, 0x01, 0x01, 0x07, 0x03, 0x02, 0xFF],
  'zoomStop': [0x81, 0x01, 0x04, 0x07, 0x00, 0xFF],
  'zoomTeleStd': [0x81, 0x01, 0x04, 0x07, 0x02, 0xFF],
  'zoomWideStd': [0x81, 0x01, 0x04, 0x07, 0x03, 0xFF],
  'menuToggle': [0x81, 0x01, 0x06, 0x06, 0x10, 0xFF],
  'menuOK': [0x81, 0x01, 0x7E, 0x01, 0x02, 0x00, 0x01, 0xFF],
  'menuBack': [0x81, 0x01, 0x06, 0x06, 0x03, 0xFF],
  'neutral': [0x81, 0x01, 0x06, 0x02, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF],
  'power': [0x81, 0x09, 0x04, 0x00, 0xFF], // query
  'pantilt': [0x81, 0x09, 0x06, 0x12, 0xFF], // query
  'zoom': [0x81, 0x09, 0x04, 0x47, 0xFF], // query
  'focus': [0x81, 0x04, 0x18, 0x01, 0xFF],
  'ptPreset': [0x81, 0x01, 0x06, 0x02, 0x18, 0x14],
  'zPreset': [0x81, 0x01, 0x04, 0x47]
};

function viscaCmd (command, cameraIP, preset) {
  return new Promise ((resolve, error) => {
    const client = dgram.createSocket('udp4');
    const bufferCommand = Buffer.from(preset ? command : commandList[command]);
    let returnHex = '';

    client.on('error', (err) => {
      client.close();
      error(err.stack);
    });
          
    client.on('message', (msg) => {
      const hexMsg = msg.toString('hex');
      
      if( !['9041ff', '9051ff', '9042ff', '9052ff'].includes(hexMsg) ) {
        client.close();
        returnHex = msg.toString('hex');
      } else if (msg.toString('hex').match(/905\d{1}ff/)) { // command acknowledged
        client.close();
      }
      resolve(returnHex);
    });

    client.send(bufferCommand, 0, bufferCommand.length, 1259, cameraIP);
  });
}

function moveCam(command, cameraIP) {
  viscaCmd(command, cameraIP, false);
}

function queryPosition(cameraIP) {
  return new Promise( (resolve) => {
    resolve(viscaCmd('pantilt', cameraIP, false));
  }).then((pantilt) => {
    const result = new Promise( (resolve) => {
      resolve(viscaCmd('zoom', cameraIP, false));
    }).then((zoom) => {
      return ({pantilt: pantilt, zoom: zoom});
    });
    return result;
  });
}

function preset(cameraIP, pantilt, zoom) {
  return new Promise( (resolve) => {
    const ptPreset = commandList['ptPreset'].concat(pantilt).concat([0xff]);
    resolve(viscaCmd(ptPreset, cameraIP, true));
  }).then(() => {
    return new Promise ((resolve) => {
      const zPreset = commandList['zPreset'].concat(zoom).concat([0xff]);
      resolve(viscaCmd(zPreset, cameraIP, true));
    });
  });
}

module.exports = {
  moveCam: moveCam,
  queryPosition: queryPosition,
  preset: preset,
};

