
You need

  * RJ-45 patch cables or similar.
  * A stable +9V - +28V DC power source.
  * A host computer with a serial or USB interface.

The Accra module is powered from the CAN4VSCP bus. [This
article](https://github.com/grodansparadis/vscp/wiki/Connecting-CAN4VSCP-devices-together)
have information on how the bus is powered and set up. Follow it for a
reliable setup. Don't forget the 120 ohm terminators at each end of the
bus. <span class="underline">They are important\!</span> You can
activate the on board terminator on the Accra module if it is located at
one end of your bus.

When you power the module by inserting the RJ-45 cable the red LED on
the board should light up to indicate it is powered. This is just a
power indicator LED. When you power the board for the first time the
green led starts to blink to indicate that the module search for a
nickname. During normal operation this LED should light steady.

Remember that there need to be <span class="underline">at least
two</span> CAN4VSCP (or other CAN device set to 125kbps) devices (one
additional) if you have the [Frankfurt
RS-232](https://grodansparadis.github.io/can4vscp-frankfurt-rs232)
or some other bus interface. A single device can't talk by
itself on a bus. It's an error.

  
[filename](./bottom-copyright.md ':include')
