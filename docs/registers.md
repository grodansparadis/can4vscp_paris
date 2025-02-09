# Registers

All VSCP modules have a set of 8-bit registers defined. Some of them
(register 128-255) are predefined and the information in them are the
same for all VSCP modules. See the [VSCP
specification](https://grodansparadis.github.io/vscp-doc-spec/#/./vscp_register_abstraction_model)
for a description of their content.

The lower 128 register positions are used for module specific registers.
It is normally here you find registers with which you configure your
module. You can also find registers where you typically can read status
information such as measurement data from the module.

Furthermore the lower register space can be paged on 65536 pages.

Below is a description of the registers on the Paris smart relay
controller.

## Zone registers

  | Register | Page | Description |
  | -------- | -- - | ----- ----- | 
  | 0 (0x00) | 0    | Zone for module. Read/write. |
  | 1 (0x01) | 0    | Sub zone for module. |

## Relay status registers

  | Register   | Page |  Description |
  | ---------- | ---- | ------------ |
  | 2 (0x02)   | 0      | Relay 1 Status register. Read/Write.| 
  | 3 (0x03)   | 0      | Relay 2 Status register. Read/Write.| 
  | 4 (0x04)   | 0      | Relay 3 Status register. Read/Write.| 
  | 5 (0x05)   | 0      | Relay 4 Status register. Read/Write.| 
  | 6 (0x06)   | 0      | Relay 5 Status register. Read/Write.| 
  | 7 (0x07)   | 0      | Relay 6 Status register. Read/Write.| 
  | 8 (0x08)   | 0      | Relay 7 Status register. Read/Write.| 
  | 9 (0x09)   | 0      | Reserved| 

Writing a value to the relay control register will activate/deactivate
the relay output.

   * 0 - The relay is inactivated.
   *  1 - The relay is activated.

Reading a value from the relay control register is read as a one if the
relay is activated and a 0 if the relay is deactivated.

## Relay control registers

  | Register    | Page   | Description| 
  | ----------- | ------ | -----------|
  | 10 (0x0a)   | 0      | Relay 1 Control Register. Read/Write.| 
  | 11 (0x0b)   | 0      | Relay 2 Control Register. Read/Write.| 
  | 12 (0x0c)   | 0      | Relay 3 Control Register. Read/Write.| 
  | 13 (0x0d)   | 0      | Relay 4 Control Register. Read/Write.| 
  | 14 (0x0e)   | 0      | Relay 5 Control Register. Read/Write.| 
  | 15 (0x0f)   | 0      | Relay 6 Control Register. Read/Write.| 
  | 16 (0x10)   | 0      | Relay 7 Control Register. Read/Write.| 
  | 17 (0x11)   | 0      | Reserved.| 

The relay control bits enable/disable intelligent relay functionality:

  * **Bit 0** - Enable pulsed output if set to one.
  * **Bit 1** - Alarm sent when protection timer triggers (if set).
  * **Bit 2** - Protection timer enable if set to one.
  * **Bit 3** - Send On event (CLASS=20, TYPE=3) when relay goes to
    active state.
  * **Bit 4** - Send Off event (CLASS=20, TYPE=4) when relay goes to
    inactive state.
  * **Bit 5** - Send Started event (CLASS=20, TYPE=25) when relay goes
    to active state.
  * **Bit 6** - Send Stopped event (CLASS=20, TYPE=24 )when relay goes
    to inactive state.
  * **Bit 7** - If set to one the relay is enabled. If set to zero it is
    inactivated.

## Relay pulse time registers

  | Register    | Page   | Description| 
  | ----------- | ------ | -----------|
  | 18 (0x12)   | 0      | On/off pulse time Relay 1 (seconds) MSB. Read/Write.| 
  | 19 (0x13)   | 0      | On/off pulse time Relay 1 (seconds) LSB. Read/Write.| 
  | 20 (0x14)   | 0      | On/off pulse time Relay 2 (seconds) MSB. Read/Write.| 
  | 21 (0x15)   | 0      | On/off pulse time Relay 2 (seconds) LSB. Read/Write.| 
  | 22 (0x16)   | 0      | On/off pulse time Relay 3 (seconds) MSB. Read/Write.| 
  | 23 (0x17)   | 0      | On/off pulse time Relay 3 (seconds) LSB. Read/Write.| 
  | 24 (0x18)   | 0      | On/off pulse time Relay 4 (seconds) MSB. Read/Write.| 
  | 25 (0x19)   | 0      | On/off pulse time Relay 4 (seconds) LSB. Read/Write.| 
  | 26 (0x1A)   | 0      | On/off pulse time Relay 5 (seconds) MSB. Read/Write.| 
  | 27 (0x1B)   | 0      | On/off pulse time Relay 5 (seconds) LSB. Read/Write.| 
  | 28 (0x1C)   | 0      | On/off pulse time Relay 6 (seconds) MSB. Read/Write.| 
  | 29 (0x1D)   | 0      | On/off pulse time Relay 6 (seconds) LSB. Read/Write.| 
  | 30 (0x1E)   | 0      | On/off pulse time Relay 7 (seconds) MSB. Read/Write.| 
  | 31 (0x1F)   | 0      | On/off pulse time Relay 7 (seconds) LSB. Read/Write.| 
  | 32 (0x20)   | 0      | Reserved.| 
  | 33 (0x21)   | 0      | Reserved.| 

This is the pulse time for the each relay expressed in seconds. This can
be used to have a relay turn on and off with a certain preset interval.
The minimum pulse time is 1 second and the maximum time is 65535 seconds
which is about 18 hours.

Set to zero (default) for no pulse time i.e. the relay will be steady
on/off.To start a pulse sequence bit 0 for the corresponding relay
should be set to one.

## Relay protection time registers

  | Register   |  Page   | Description| 
  | ---------- | ------- | -----------|
  | 34 (0x22)    | 0       | Protection time Relay 1 (seconds) MSB. Read/Write. | 
  | 35 (0x23)    | 0       | Protection time Relay 1 (seconds) LSB. Read/Write. | 
  | 36 (0x22)    | 0       | Protection time Relay 2 (seconds) MSB. Read/Write. | 
  | 37 (0x23)    | 0       | Protection time Relay 2 (seconds) LSB. Read/Write. | 
  | 38 (0x22)    | 0       | Protection time Relay 3 (seconds) MSB. Read/Write. | 
  | 39 (0x23)    | 0       | Protection time Relay 3 (seconds) LSB. Read/Write. | 
  | 40 (0x22)    | 0       | Protection time Relay 4 (seconds) MSB. Read/Write. | 
  | 41 (0x23)    | 0       | Protection time Relay 4 (seconds) LSB. Read/Write. | 
  | 42 (0x22)    | 0       | Protection time Relay 5 (seconds) MSB. Read/Write. | 
  | 43 (0x23)    | 0       | Protection time Relay 5 (seconds) LSB. Read/Write. | 
  | 44 (0x22)    | 0       | Protection time Relay 6 (seconds) MSB. Read/Write. | 
  | 45 (0x23)    | 0       | Protection time Relay 6 (seconds) LSB. Read/Write. | 
  | 46 (0x22)    | 0       | Protection time Relay 7 (seconds) MSB. Read/Write. | 
  | 47 (0x23)    | 0       | Protection time Relay 7 (seconds) LSB. Read/Write. | 
  | 48 (0x22)    | 0       | Reserved. | 
  | 49 (0x23)    | 0       | Reserved. | 

This is the relay protection time. A relay will be inactivated if not
written to before this time has elapsed. Set to zero to disable
(default). The max time is 65535 seconds which is about 18 hours.

The registers can for example be used as a security feature to ensure
that an output is deactivated after a preset time even if the
controlling device failed to deactivate the relay.

## Relay zone information

   | Register     | Page    | Description | 
   | ------------ | ------- | ----------- |
   | 50 (0x32)    | 0       | Relay 1 Zone. Read/Write. | 
   | 51 (0x33)    | 0       | Relay 1 Sub Zone. Read/Write. | 
   | 52 (0x34)    | 0       | Relay 2 Zone. Read/Write. | 
   | 53 (0x35)    | 0       | Relay 2 Sub Zone. Read/Write. | 
   | 54 (0x36)    | 0       | Relay 3 Zone. Read/Write. | 
   | 55 (0x37)    | 0       | Relay 3 Sub Zone. Read/Write. | 
   | 56 (0x38)    | 0       | Relay 4 Zone. Read/Write. | 
   | 57 (0x39)    | 0       | Relay 4 Sub Zone. Read/Write. | 
   | 58 (0x3a)    | 0       | Relay 5 Zone. Read/Write. | 
   | 59 (0x3b)    | 0       | Relay 5 Sub Zone. Read/Write. | 
   | 60 (0x3c)    | 0       | Relay 6 Zone. Read/Write. | 
   | 61 (0x3d)    | 0       | Relay 6 Sub Zone. Read/Write. | 
   | 62 (0x3e)    | 0       | Relay 7 Zone. Read/Write. | 
   | 63 (0x3f)    | 0       | Relay 7 Sub Zone. Read/Write. | 
   | 64 (0x40)    | 0       | Reserved. | 
   | 65 (0x41)    | 0       | Reserved. | 

This is the zone and sub-zone value related to a specific relay. If zero
the the module Zone/sub-zone will be used.

## Registers for decision matrix

 | Register                  | Page    | Description | 
 | ------------------------- | ------- | ----------- |
 | 72 (0x48) - 127 (0x7f)    | 0       | Decision matrix. | 

See [decision matrix](./decisionmatrix.md) for the description of the decision matrix for the module.

A general description of the decision matrix is available in the [VSCP
specification](https://grodansparadis.github.io/vscp-doc-spec/#/./vscp_decision_matrix).

  
[filename](./bottom-copyright.md ':include')
