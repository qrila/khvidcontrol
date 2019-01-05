# khvidcontrol

> Control video setup

## About

Project is created to enable video feed control in permanent installation.

Main video feed is provided with HD video camera model V600 and ohter cameras and media content from PC is mixed using Blackmagicdesing [ATEM Television Studio HD](https://www.blackmagicdesign.com/products/atemtelevisionstudiohd). V600 PTZ is controlled via RS485 using VISCA control protocol. Video mixer is controlled via ethernet using [Skaarhoj](http://skaarhoj.com) open sourced [Open Engineering software](https://github.com/kasperskaarhoj/SKAARHOJ-Open-Engineering).

This control software consists web server delivering UI and persisting desired camera positionings. Web server is build using Node.js framework [Feathers.js](https://feathersjs.com/) Hardware is controlled with python scripts utilising freely available libraries.

Target hardware is RaspberryPi.

## Anything else

TBD

To enable starting forever.js after boot command is needed to add 'root' user's crontab and run as node.js user. Node and forever commands needs to be symlinked so 'root' user is able run those.

## Development todo

- Replace Skaarhoj code and wrapper with node package (e.g. [node-appletest-atem](https://github.com/applest/node-applest-atem) or similar)
- Add fade to black to hide camera movement when changing between positions on same camera
- Refactor arrow button implementation as bootstrap 3 solution is not good
- Create functionality to edit camera positions and order of buttons
- Build settings UI for adding information of mixer and camera(s)
- Refactor main control UI to follow proper practises so that data is not stored in frontend and build UI using frontend framework (react/vue)
- Create user profiles with desired button configuration and basic settings
- Replace serial call python implementation with node one

## Installing Atem control

Run commands found in `python/atempython/README.md`

## Installing webrtc-streamer for Embedded Video in Web Page

- Go to [releases page of webrtc-streamer](https://github.com/mpromonet/webrtc-streamer/releases). (Tested with v0.1.1)
- Get latest version of the Windows-AMD64-Release package.
- Extract it to a temporary location and find `webrtc-streamer.exe`
- Copy the `webrtc-streamer.exe` to `khvidcontrol/bin/webrtc-streamer.exe`
- When you start khvidcontrol using `npm start`, also webrtc-streamer is automatically started if the executable is in place

## License

Copyright (c) 2017 Kalle Kuurila

Licensed under the [MIT license](https://opensource.org/licenses/MIT).

### Excluding

Python wrapper copyright to ...

[Skaarhoj](http://skaarhoj.com) code is licensed under own [definition](http://skaarhoj.com/about/licenses/).
