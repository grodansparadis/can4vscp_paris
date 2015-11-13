<h1>Paris Relay module</h1>

<img src="http://www.grodansparadis.com/paris/manual/lib/exe/fetch.php?w=600&tok=8478ad&media=paris1_800.png" />

This is one of two reference modules for the VSCP project. It is a 
module that can control up to seven relays. 

Product page for the module is <a href="http://www.grodansparadis.com/paris/paris.html">here</a>. 

You can order the module from the <a href="http://www.frogshop.se/index.php?route=product/product&path=59&product_id=53">FrogShop</a>.

<hr>

<h3>Steps you should go through to adopt this file for your own VSCP project.</h3>

1.) The frequency for your system may be different. This will affect the CAN bit rate settings
which are defined in the biginning of the can18f.c file. Here you also find the filter/mask 
defines if you need to change these.

Timer0 is used as a 1 ms timer for the VSCP functionality. You should adopt the timer reload value 
in the main.h file to your system.

2.) The GUID (Glocal Unique ID) is defined in the beginning of vscp.c This number should be 
different for each piece of equiment you produce. Regard it is as the device serial number. It
can be moved to EEPROM if that is found more convinient. In that case the vscp_rcv_readreg 
procedure in vscp.c also has to be changed.

3.) The device URL is defined in the beginning of the vscp.c file. This is an URL without the
initial "http://" that should point to a XML file that give information about your piece of 
equipment.

4.) The manufacturer id is also defined in the beginning of the vscp.c file. You can use this
id in any way you like.

In addition to this you may use different pins for the INIT button (RC0 today) and the 
status LED (RC1) today. Changes affect the main interrupt vector.

VSCP (Very Simple Control Protocol) 
<a href="http://www.vscp.org">http://www.vscp.org</a>

<a mailto="akhe@grodansparadis.com">akhe@grodansparadis.com</a>

