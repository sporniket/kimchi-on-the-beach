# Kimchi on the beach

> [WARNING] Please read carefully this note before using this project. It contains important facts.

Content

1. What is **Kimchi on the beach**, and when to use it ?
2. What should you know before using **Kimchi on the beach** ?
3. How to use **Kimchi on the beach** ?
4. Known issues
5. Miscellanous

## 1. What is **Kimchi on the beach**, and when to use it ?
**Kimchi on the beach** is a firmware for the ESP32 micro-controller that aims to convert the so-called "Intelligent KeyBoarD" (IKBD) of the vintage computer known as "Atari ST" into a bluetooth HID device.

The IKBD is a subdevice from this family of computers, that consists in a keyboard and 2 male DE-9 ports to connect one serial mouse (port 0) and 2 game controllers (port 0 and 1). A dedicated microcontroller receives the physical inputs from the keyboard, mouse and game controllers, and transmit logical events to the main unit through a serial connexion.

**Kimchi on the beach** converts the logical event into USB HID reports that are transmitted over bluetooth (BLE HID). 

`Keyboard, Mouse, Game controllers over BLE HID` &rArr; `K M G / B H` &rArr; **Kimchi on the beach**

### Roadmap

* POC : a firmware that advertises as a BLE HID device. Once connected, it can send keyboard, mouse and game controllers events triggered by push-buttons.
* v0.1 : Like the POC, connected to the IKBD, recognises keyboard events and convert them to keyboard reports.
* v0.2 : Like v0.1, recognises and convert mouse events.
* v0.3 : Like v0.2, recognises and convert game controller events.
* v0.4 : supports additionnal keypad for missing keys compared to modern keyboard (fn, alt gr, f11, f12,...)
* v0.5 : supports an Oled display and a GUI to perform some setup (keyboard layouts, ...)
* ...
* v1.0 : reference version


### Licence
 **Kimchi on the beach** is free software: you can redistribute it and/or modify it under the terms of the
 GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your
 option) any later version.

 **Kimchi on the beach** is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without
 even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 more details.

 You should have received a copy of the GNU General Public License along with **Kimchi on the beach**.
 If not, see http://www.gnu.org/licenses/ .


## 2. What should you know before using **Kimchi on the beach** ?

**Kimchi on the beach** is developped using : 

* a development board compatible with az-delivery devkit-c
* Platform-IO extension on VSCode
* the IDF toolchain from Espressif.

**Kimchi on the beach** reuse code taken from :

* https://github.com/nkolban/esp32-snippets 



> Do not use **Kimchi on the beach** if this project is not suitable for your project

## 3. How to use **Kimchi on the beach** ?

### From source
To get the latest available code, one must clone the git repository.

	git clone https://github.com/sporniket/kimchi-on-the-beach.git

Then use VSCode with Platform-IO, install the IDF kit, select your development board.

If you have a different board, you will have to run `pio run -t menuconfig`. 

* Activate Bluetooth (BLE).
* Check the pins mapping in the section _BLE HID COMBO Configuration_
* Compare with the file `sdkconfig.az-delivery-devkit-v4` if the build fails because of missing components.

Try to build (the latest commit on main builds on my computer), solves the problems one by one.

Finally, upload on your development board.

### Hardware setup

To be done. In short, one will needs 5 leds, 5 push buttons, one 4-channel bidirectionnal level translator, one IKBD unit, some batteries holder, and voltage regulator to get 5V. A perfboard, breadboard and a bunch of wires.

## 4. Known issues
See the [project issues](https://github.com/sporniket/core/issues) page.

## 5. Miscellanous

### Report issues
Use the [project issues](https://github.com/sporniket/core/issues) page.
