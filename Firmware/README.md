# ATMEGA328P-PU + ST7735 BlackTab + HC-05 Bluetooth Module

## Project Description
The purpose of this application is to demonstrate the use of a 
bluetooth module for communication between a microcontroller and
a Flutter mobile application.

## Details
1. ### Microcontroller
    For the microcontroller we are using an ATMEGA328P-PU. [Datasheet](https://ww1.microchip.com/downloads/en/DeviceDoc/ATmega48A-PA-88A-PA-168A-PA-328-P-DS-DS40002061B.pdf)
2. ### Programmer
    For programming we are using an Atmel AVRISPMKII programmer. For details about this programmer refer to the [AVRISPMKII User Guide](https://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-42093-AVR-ISP-mkII_UserGuide.pdf)
3. ### Programming Method
    Programming is being done using the avr-gcc compiler for compilation and avrdude for flashing and fusing the microcontroller. A Makefile is used to aid with issuing the programming commands to the microcontroller.

    There are a variety of ways to install the toolchain:
    
    ## For Macs
     users you could use [CrossPack](https://www.obdev.at/products/crosspack/index.html) for mac, you could install avr-gcc and avrdude using brew [as shown here](https://www.pololu.com/docs/0J61/6.3), or you could install qmk if you're on an M1 or M2 macbook pro or similar:

    `$>brew install qmk/qmk/qmk`<br/>
    `$>qmk setup`

    ## For Windows
    You can get the complete toolchain and AVR IDE for windows directly from Microchip [here](https://www.microchip.com/en-us/tools-resources/develop/microchip-studio#Downloads). This includes the compiler and the utilities for flashing the microcontrollers.

## Schematics

Schematics are available in the root of the repository in a directory named "kicad". You will also find PCB board layouts, kicad libraries for parts and additional instructions.

## Programming Details

The HC-05 bluetooth module uses a UART module for communication with the outside world. We will use a UART library to communicate with it from the ATMEGA328P-PU microcontroller to send and recieve AT commands to the HC-05 device. For a complete list of available AT commands for the HC-05 module, please refer to the [datasheet](https://components101.com/sites/default/files/component_datasheet/HC-05%20Datasheet.pdf) on page 5. 

The ST7735 black tab version of the 1.8" TFT LCD Screen uses the SPI interface to connect to the microcontroller. We will use an ST7735 library written by Marian Hrinko in 2020. This library includes the SPI connectivity functionality within, so no additional SPI library will be necessary.

## Possible Future Upgrades
The goal scenario is having an IoT device commissioning service
running on a web server or similar. Devices will make themselves available as soon as they recieve a wireless connection wether that's through the bluetooth protocol or through HTTP protocol over WiFi. The most basic idea is to use an ESP32 module or similar to give the microcontroller WiFi connectivity. This will allow the device to register itself with the commissioning service. Once IoT devices have been commissioned, they should appear on the Mobile application, and values should be able to be read and written to such devices. 


## Applciations

This technology has many applications in the Internet of Things realm, robotics, sensing and monitoring and many others. Primarily this system could be adapted to work in a variety of different applications.