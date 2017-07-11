# khvidcontrol

> Control video setup

## About

Project is created to enable video feed control in permanent installation.

Main video feed is provided with HD video camera model V600 and ohter cameras and media content from PC is mixed using Blackmagicdesing [ATEM Television Studio HD](https://www.blackmagicdesign.com/products/atemtelevisionstudiohd). V600 PTZ is controlled via RS485 using VISCA control protocol. Video mixer is controlled via ethernet using [Skaarhoj](http://skaarhoj.com) open sourced [Open Engineering software](https://github.com/kasperskaarhoj/SKAARHOJ-Open-Engineering).

This control software consists web server delivering UI and persisting desired camera positionings. Web server is build using Node.js framework [Feathers.js](https://feathersjs.com/) Hardware is controlled with python scripts utilising freely available libraries.

Target hardware is RaspberryPi.

## Anything else

TBD

## Installing Atem control

Run commands found in `python/atempython/README.md`

## License

Copyright (c) 2017 Kalle Kuurila

Licensed under the [MIT license](https://opensource.org/licenses/MIT).

### Excluding

Python wrapper copyright to ...

[Skaarhoj](http://skaarhoj.com) code is licensed under own [definition](http://skaarhoj.com/about/licenses/).
