# Decision Matrix

The full functionality of the decision matrix is explained [in the
specification](https://grodansparadis.github.io/vscp-doc-spec/#/./vscp_decision_matrix).

Paris have a decision matrix consisting of eight entries. This matrix
can be used to control the relays. Possible actions are listed in the
table below.

| Action | Action code | Parameter | Description |
| ------ | ----------- | --------- | ----------- |
| **NOOP**         | 0 (0x00) | Not used   |                              No operation. Will do absolutely nothing.| 
| **ACTIVATE**     | 1 (0x01) | Relays to activate (bit array) | Activate relay(s) given by argument. The argument is a bit array where bit 0 is relay 1 and so on. That is a position with a set bit will activate the corresponding relay. Byte 1 is Zone and byte 2 is sub-zone and must be equal to register content to trigger action. | 
| **DEACTICATE**   | 2 (0x02) | Relays to deactivate (bit array) | Deactivate relay(s) given by argument. The argument is a bit array where bit 0 is relay 1 and so on. That is a position with a set bit will inactivate the corresponding relay. Byte 1 is Zone and byte 2 is sub-zone and must be equal to register content to trigger action.| 
| **PULSEON**      | 3 (0x03) | Relays to pulse (bit array) | Pulse relay(s) given by argument. The argument is a bit array where bit 0 is relay 1 and so on. That is a position with a set bit will toggle the corresponding relay. Byte 1 is Zone and byte 2 is sub-zone and must be equal to register content to trigger action.| 
|               |  4 (0x04)      |    |                                    Reserved.| 
|               | 5 (0x05)       |    |                                    Reserved.| 
|               |  6 (0x06)      |    |                                    Reserved.| 
|               | 7 (0x07)       |    |                                    Reserved.| 
|               | 8 (0x08)       |    |                                    Reserved.| 
|              | 9 (0x09)        |    |                                    Reserved.| 
| **STATUS**    | 10 (0x0a)      | Relays to send status for (bit array) |  Send relay status. The argument is a bit array where bit 0 is relay 1 and so on. That is a position with a set bit will have a status event sent for the corresponding relay.| 
|                | 11 (0x0b)     |    |                                   Reserved.| 
|                | 12 (0x0c)     |    |                                   Reserved.| 
|                | 13 (0x0d)     |    |                                   Reserved.| 
|                | 14 (0x0e)     |    |                                   Reserved.| 
|                | 15 (0x0f)     |    |                                   Reserved.| 
| **DISABLE**      | 16 (0x10)  | Relays to disable (bit array) | Disable relay(s) given by argument. The argument is a bit array where bit 0 is relay 1 and so on. That is a position with a set bit will disable the corresponding relay. Byte 1 is Zone and byte 2 is zone page and must be equal to register content to trigger action. | 



  
[filename](./bottom-copyright.md ':include')
