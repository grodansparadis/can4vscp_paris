# Functional Description 

## Configure the module

You configure a VSCP module by writing content into the modules
registers. You can do this manually or with the wizard available in
[VSCP Works+](https://grodansparadis.github.io/vscp-works-qt/#/).
Using the wizard is absolutely the easiest way to set up functionality.

## Zone/sub-zone

You should always plan your overall structure. The zone and the sub-zone registers found in the first two register positions can help you here. Think of a zone as a (logical) house,floor plan or similar and sub-zone as a room or a location.

Note that this is not an address. It\'s a way to group functionality together.

Each relay can belong to it\'s own sub-zone or to a common sub-zone. Set it in register 50-56.

## Functionality for the relays

As you may expect the main functionality for the Paris relay module is the possibility to turn a relay on or off. Even if this is the main functionality there is some extra functionality available. Each relay have a control byte with flag (bits) which control different functionality for each relay. The bits have the following meaning

  * **bit 7** - Must be set to one to make it possible to control the
    relay. Both register writes, pulse and actions are ignored when the
    bit is set to zero.
  * **bit 6** - If set a [STOP event,CLASS=20,
    TYPE=24](https://grodansparadis.github.io/vscp-doc-spec/#/./class1.information?id=type24)
    will be sent when the relay goes to it\'s inactive state.
  * **bit 5** - If set a [START event, CLASS=20,
    TYPE=25](https://grodansparadis.github.io/vscp-doc-spec/#/./class1.information?id=type25)
    will be sent when the relay goes to it\'s active state.
  * **bit 4** - If set an [OFF event,CLASS=20,
    TYPE=4](https://grodansparadis.github.io/vscp-doc-spec/#/./class1.information?id=type4)
    will be sent when the relay goes to it\'s inactive state.
  * **bit 3** - If set an [ON event, CLASS=20,
    TYPE=3](https://grodansparadis.github.io/vscp-doc-spec/#/./class1.information?id=type3)
    will be sent when the relay goes to it\'s active state.
  * **bit 2** - Enables the protection timer if set to one.
  * **bit 1** - Alarm is sent if the protection timer elapses if this
    bit is set to one.
  * **bit 0** - Pulse output enabled if set to one.

## Set/get relay state with register read/writes

A relay can be active (on) or inactive(off). In registers 2-8 you can read or write the status for an individual relay. A zero mean the relay is off, and a one that it is on. So writing a one to register 2 of a Paris relay module will turn relay 1 on. A better way however is to use the [decsision matrix](./decisionmatrix) of the module to accomplish this.

## Set/get relay state using the decision matrix

Normally the [decision matrix](./decisionmatrix) of the module is the best way to to handle relay state changes. This much more flexible then to use the register writes directly. This is also why the zone/sub-zone registers should be initialized with meaningful values. The decision matrix of this module can have eight entries. Each entry is a line that look for a specified event on the bus and perform a specific action if this event is found. Typically this can be a ON-event sent to a specific zone/sub-zone.

A row in the decision matrix can be setup to turn on/off one or more relays if this event is detected and if the zone/sub-zone is the one expected. At first the setup of the decision matrix can be hard to grasp. You can read all about it in the [VSCP Specification](https://grodansparadis.github.io/vscp-doc-spec/#/./vscp_decision_matrix).

Here we will just at a simple example.

The decision matrix consist of eight bytes. The first byte is the originating address. You can set a nickname here for the node that is allowed to trigger (perform) a selected action. The control byte have configuration bits(flags) for how the information should be interpreted.

One bit (bit 6) tells if the originating address should be checked or not. That is if bit 6 is set then the originating address must be the same as the byte stored in the first byte of the decision matrix to trigger the action. Bit 7 must always be set for the row to be compared
to an incoming event. Bit four and five, if set, check if byte 1 and 2 of the incoming event is the same as the zone/sub-zone stored in register3 0/1 of the module.

Byte 2/3 together with bits 0/1 of the control register is the class mask and filter. A ninth bit is needed as a VSCP class consist of nine bits.

Byte 4/5 is the type mask and filter. This is something most newcomers to VSCP have problems with. But is is actually really simple. The following table illustrates how this works

| Mask bit n | Filter bit n | Incoming event class bit n | Accept or reject bit n |
|------------|--------------|----------------------------|------------------------|
| 0          | x            | x                          | Accept | 
| 1          | 0            | 0                          | Accept | 
| 1          | 0            | 1                          | Reject | 
| 1          | 1            | 0                          | Reject | 
| 1          | 1            | 1                          | Accept | 

Think of the mask as having ones at positions that are of interest and the filter telling what the value should be for those bit positions that are of interest.

So the most common case, 

  * to only accept one class, set all mask bits to one and enter the class in the filter.
  * To accept all classes set the class mask to 0. In this case the filter value does not care.
  * To accept everything set both masks to zero and the filter to any value you like.

### Common cases are

#### You want to trigger on a specific event.

  1.  Set all bits of the class mask to ones (255 plus bit 1 of the control register set to one) and all bits of the type mask to one (255).
  2.  Write the class that should trigger the event into the class filter (remember that bit nine goes to bit 0 of the control byte) and the type to the type filter. So if you want to trigger on a [TurnOn event](https://grodansparadis.github.io/vscp-doc-spec/#/./class1.control?id=type5) which have CLASS=30, TYPE=5 you set the class filter = 30 (class bit i control byte to zero) and the type filter = 5.
  3.  Now if the originating address bit is not set and the row is enabled (bit 7 of the control register).

#### You want to trigger on any event you get from a specific module.

  1.  Enter the nickname of the module in the first byte of the decision matrix.
  2.  Set the control byte to 192 (bit 6 (check originating address) and bit 7 (enable decision matrix row) set).
  3.  Set byte 2-5 (masks and filters) to zero. Actually class and type filters can have any value as long as the masks are zero.
  4.  Set the appropriate action/action parameter values. For example action=1 and action parameter = 3 (0b00000011) to activate relay 0 and 1 when any event is received from the node.

The decision matrix makes it very easy to set up systems where one event triggers actions on several modules. It is also easy to adopt your system to new demands. You can add and replace modules without affecting the system functionality.

#### Pulsing outputs

If you want your relay output to be turned on/off with a certain interval the Paris relay module automatically can handle this for you. First set the time the relay should be on/off in register 18-33. There are two registers for each relay and the time is given in seconds. The
lower byte holds the most significant byte and the higher byte holds the least significant byte.

As and example: If you want relay 0 to have an output that is on for five minutes and then off for five minutes and so on you first calculate how many seconds the pulse time is. In this case 5 \* 60 = 300 seconds. This is what should go into register 18 and 19. 300/256 = 1 which is what should go into register 18 and the rest (300 - 1\*256 = 44 ) 44 forms the least significant byte and should go to register 19. To start the pulse output you also have to set bit 0 in the corresponding relay control register to one.

#### Protection timer

A protection timer can be convenient to use to protect a system form malfunctions in some of it\'s components. Suppose you have a relay that controls a pump that fills a tank with some liquid. The pump should then be turned off when a the tanks is full which is indicated by an event
from a sensor on the tank. If this sensor is broken or the cable to the module is broken this event will never be received. With the protection timer activated the pump will be turned of anyway before things get to bad. It is also possible to send an alarm when this happens to inform
the rest of the system.

The protection timers are in registers 34-47 and comes, like the pulse registers, in pairs. The first byte in a pair holds the most significant byte of the timer and the second the least significant byte. Also as for the pulse time the time set is given in seconds. A maximum of 65535
seconds can thus be stored. So the range is one seconds up to around eighteen hours.

The protection timer, if activated, is started when you activate the protected relay. If the relay is active when the timer elapse it will be turned off. If you activate the relay again before the timer has elapsed the protection timer will be resettled and start to count down from the preset value again. If you turn of the relay the timer will be inactivated until the relay is activated again. Both relay control through actions and register writes affects the timer.

#### Alarm

The module can send alarm events if the protection timer elapses. When an alarm occurs a bit is set in the alarm register which is located in register position 128. You can always read this register to see if the module have sent out and alarm events. When you read the register the alarm bits will be cleared.

  
[filename](./bottom-copyright.md ':include')
