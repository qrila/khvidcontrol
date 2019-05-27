# khvidcontrol

> Control video setup

## About

Project is created to enable video feed control in permanent installation.

Main video feed is provided with HD video camera model V600 and ohter cameras and media content from PC is mixed using Blackmagicdesing [ATEM Television Studio HD](https://www.blackmagicdesign.com/products/atemtelevisionstudiohd). V600 PTZ is controlled via VISCA over IP control protocol. Video mixer is controlled via ethernet using [applest-atem](https://github.com/applest/node-applest-atem) library.

This control software consists web server delivering UI and persisting desired camera positionings. Web server is build using Node.js framework [Feathers.js](https://feathersjs.com/).

## Anything else

TBD

## Development todo

- Create functionality to edit camera positions and order of buttons
- Build settings UI for adding information of mixer and camera(s)
- Refactor main control UI using frontend framework (react)
- Create user profiles with desired button configuration and basic settings

## Installing webrtc-streamer for Embedded Video in Web Page

- Go to [releases page of webrtc-streamer](https://github.com/mpromonet/webrtc-streamer/releases). (Tested with v0.1.1)
- Get latest version of the Windows-AMD64-Release package.
- Extract it to a temporary location and find `webrtc-streamer.exe`
- Copy the `webrtc-streamer.exe` to `khvidcontrol/bin/webrtc-streamer.exe`
- When you start khvidcontrol using `npm start`, also webrtc-streamer is automatically started if the executable is in place

## License

Copyright (c) 2017 Kalle Kuurila

Licensed under the [MIT license](https://opensource.org/licenses/MIT).
