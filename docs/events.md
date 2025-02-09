# Events

Here the events sent by the module is described.

 | Event | Description |
 | ------ | ----------- | 
 | [CLASS1.INFORMATION (20) Type=3, On](https://grodansparadis.github.io/vscp-doc-spec/#/./class1.information?id=type3)   | If enabled the event is sent when a relay goes to its active state. Index is 0 for relay 1, 1 for relay 2 and so on. Zone and sub-zone are set accordingly. Sub-zone for relay is used if it\'s not zero. <br /><br />**Data:**<br />**Byte 0:** Index. <br />**Byte 1:** Zone <br />**Byte 2:** Subzone. |
 | [CLASS1.INFORMATION (20) Type=4, Off](https://grodansparadis.github.io/vscp-doc-spec/#/./class1.information?id=type4)   |           If enabled the event is sent when a relay goes to its inactive state. Index is 0 for relay 1, 1 for relay 2 and so on. Zone and sub-zone set accordingly. Sub-zone for relay is used if it\'s not zero. <br /><br />**Data:**<br /> **Byte 0:** Index. <br />**Byte 1:** Zone <br />**Byte 2:** Subzone. | 
 | [CLASS1.INFORMATION (20) Type=24, Stop](https://grodansparadis.github.io/vscp-doc-spec/#/./class1.information?id=type24)  |        Index is 0 for relay 1, 1 for relay 2 and so on. Zone and sub-zone set accordingly. Sub-zone for relay is used if it\'s not zero. <br /><br />**Data:**<br />**Byte 0:** Index. <br />**Byte 1:** Zone <br />**Byte 2:** Subzone. | 
 | [CLASS1.INFORMATION (20) Type=25, Start](https://grodansparadis.github.io/vscp-doc-spec/#/./class1.information?id=type25)  |      Index is 0 for relay 1, 1 for relay 2 and so on. Zone and sub-zone set accordingly. Sub-zone for relay is used if it\'s not zero. <br /><br />**Data:** <br />**Byte 0:** Index. <br />**Byte 1:** Zone <br />**Byte 2:** Subzone. |
 | [CLASS1.ALARM (1) Type=2, Alarm occurred](https://grodansparadis.github.io/vscp-doc-spec/#/./class1.alarm?id=type2)  |   Index is 0 for relay 1, 1 for relay 2 and so on. <br /><br />**Data:** <br />**Byte 0:** Index. <br />**Byte 1:** Zone <br />**Byte 2:** Subzone.  | 

  
[filename](./bottom-copyright.md ':include')
