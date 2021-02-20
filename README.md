# khvidcontrol

> Control video setup

## About

Project is created to enable live video feed control in permanent installation.

Main video feed is provided with HD video camera model V600 and ohter cameras and media content from PC is mixed using Blackmagicdesing [ATEM Television Studio HD](https://www.blackmagicdesign.com/products/atemtelevisionstudiohd). V600 PTZ is controlled via ethernet using VISCA control protocol with Node's *dgram* client. Video mixer is controlled via ethernet using *applest-atem* Node package.

This control software consists web server delivering UI and persisting desired camera positionings. Web server is build using [Node.js](https://nodejs.org/) framework [Feathers.js](https://feathersjs.com/). 

## Development todo

- Build settings UI for adding information of mixer and camera(s)
- Create user profiles with desired button configuration and basic settings
- Translation support

## Installing webrtc-streamer for Embedded Video in Web Page

- Go to [releases page of webrtc-streamer](https://github.com/mpromonet/webrtc-streamer/releases). (Tested with v0.1.1)
- Get latest version of the Windows-AMD64-Release package.
- Extract it to a temporary location and find `webrtc-streamer.exe`
- Copy the `webrtc-streamer.exe` to `khvidcontrol/bin/webrtc-streamer.exe`
- When you start khvidcontrol using `npm start`, also webrtc-streamer is automatically started if the executable is in place

## License

### Main application

Copyright (c) 2021 Kalle Kuurila

Licensed under the [MIT license](https://opensource.org/licenses/MIT).

### Webstreamer and polygon interface implementation

Jetro Lauha

