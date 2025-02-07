
New firmware is released from time to time for all our modules. We
expect this to be true also for the module as it is an active
project. The process of updating the firmware of the module is a simple
one. Just follow the steps outlined in the [VSCP Works
documentation](https://grodansparadis.github.io/vscp-works-qt/#/bootload_window).

## Where is the firmware?

Firmware is available in the Github repository
<https://github.com/grodansparadis/can4vscp_paris/releases> and the [MDF of the module](https://github.com/grodansparadis/can4vscp_paris/tree/master/mdf) contains a list of available firmware files and a pointer to there location. This file is loaded by the firmware updating software of VSCP Works+ and you can select the file you need from there.

### Device firmware code
The standard registers of a module contains a register that holds the firmware code for the module. This is a 16-bit value that can be read by the VSCP firmware update software. The value is a code for the specific hardware the board uses. Typically hardware has been changed and processors have been updated to later versions as time goes. The VSCP firmware update software can use this code to find the correct firmware for the module. It is **VERY** important that the correct firmware is used for the module. If the wrong firmware is used the module will not work as expected and may even be damaged. So make sure this code is the same as the code in the firmware file you use.

Older firmware files may not have this code in the standard registers as it is a pretty late addition to the standard. In that case you should use the latest firmware file for the module for the type of processor you have.

## Where is the source for the firmware?

You can find the latest source for the firmware
[here](https://github.com/grodansparadis/can4vscp_paris).

## Replacing/updating the bootloader on the module

If you need to update the bootloader on this module you can find firmware files for it [here](https://github.com/grodansparadis/vscp-pic1-bootloader/releases). Select the hex files for your board and use the bootloader application to update the bootloader. When the bootloader is loaded you can use [VSCP Works+](https://grodansparadis.github.io/vscp-works-qt/#/bootload_window) to update the application firmware of the module.

You will need a PICkit3 or similar programmer to update the bootloader.

  
[filename](./bottom-copyright.md ':include')
