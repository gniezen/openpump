# Openpump: the open source hardware syringe pump

[Openpump](http://www.openpump.org) is an open-source syringe pump that dispenses fluids over a set period of time. Syringe pumps are used to administer medication in hospitals, but also in laboratory environments performing chemical or biomedical research. Maybe you'd like to use syringe pump to extruding paste (e.g. chocolate) during 3D printing, or as part of a bioprinter when printing with biological materials?

Openpump is a collaboratively designed general-purpose syringe pump platform that can be customised for different domains. Making the hardware design available under an open source license allows anyone to improve and contribute to the device design. It also enables the design to be modified for very specific use cases and makes the devices easy to repair.

## Setup

### Rendering the 3D parts
The 3D-printed parts were designed in [OpenSCAD](http://www.openscad.org/). (To learn how to use OpenSCAD, see [the Openpump blog](http://blog.openpump.org:8080/how-to-design-a-3d-printed-enclosure-for-your-product/)). To render the different 3D parts in `linear_actuator_v0.scad`:
* Install the [MOST SCAD libraries](https://github.com/mtu-most/most-scad-libraries) by downloading them as a zip file and adding to OpenSCAD path using `export OPENSCADPATH=`<*your local path*> (in `~/.profile` on Ubuntu), or using `File->Show Library Folder` to add them to your OpenSCAD library.
* Change `render_part()` to the 3D part you want to render. You need `end_motor` (1), `end_idler` (2), `carriage_syringe_pump` (4), `clamp_syringe_pump` (5) and `syringe_plunger_retainer` (7) at a minimum.
* Before printing the syringe holder (part 5, `clamp_syringe_pump`), set the variable `d_syringe` to the be the same as the diameter of the syringe body you're using.
* Before printing the motor end (part 1, `end_motor`) set the `motor` variable to the size of stepper motor you're using, e.g. `NEMA17`
* I had best results printing the idler end (part 2, `end_idler`) with support material.

### Building the mechanical design
The step-by-step build instructions with pictures are in the [Building the syringe pump guide](http://openpump.dozuki.com/c/Build_instructions).

### Building the electronics
To build the electronics, you need the following components:
* [Arduino Mega 2560](http://arduino.cc/en/Main/ArduinoBoardMega2560) (You can also use another Arduino, but you'll need something like the Sparkfun [ProtoScrewShield](https://www.sparkfun.com/products/9729) to connect the other components as the Gameduino 2 shield covers all the pins of the regular Arduino)
* [Gameduino 2](http://excamera.com/sphinx/gameduino2/), an open source hardware touchscreen (480x272 pixels) with embedded GPU
* [Pololu DRV8834](http://www.pololu.com/product/2134) Low Voltage Stepper Motor Driver Board (You're welcome to replace this with another board if you know what you're doing)
* [ELMA E37](http://www.leobodnar.com/shop/index.php?main_page=product_info&cPath=75&products_id=196) dual concentric rotary encoder (kinda optional, used for number entry)

Because the Mega2560 has its SPI pins in a different place, you need to make 3 wire hookups. Connect:
- pin 11 to pin 51 (MOSI)
- pin 12 to pin 50 (MISO)
- pin 13 to pin 52 (SCK)

You can solder these three wires directly to the pins underneath the Mega.

To view the circuit schematic (with breadboard views), use the awesome open source hardware design tool [Fritzing](http://fritzing.org/).

## Installing the firmware

To get the firmware running on your Arduino, have a look at the [documentation](firmware/README.md) in the `firmware` folder. 

## Licenses

### Software and firmware
The software and firmware of this project is *Copyright (C) 2014 Swansea University* and made available under the GNU Affero General Public License (AGPL 3.0). See LICENSE.txt in the firmware folder for more information.

### Mechanical design
The CAD design file (linear_actuator_v0.scad) is *Copyright 2013 Michigan Technological University* and licensed under the [CC-BY-SA](Creative Commons Attribution-ShareAlike 4.0 International License) by Jerry Anzalone, developed as part of a project with the [Michigan Tech Open Sustainability Technology Research Group](http://www.appropedia.org/Category:MOST).

### Circuit schematics
The circuit schematics of this project are made available under the [CERN Open Hardware License](http://www.ohwr.org/projects/cernohl/wiki). See LICENSE.PDF in the schematics folder for more information.