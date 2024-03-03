In this we define 8bit. 8bit-slow, 16bit, and 32bit communication port classes.

Why are we doing this?
Because in order for us to communicate with the Keyboard or any other peripheral devices, we have to send data to the PIC.

In order to use a port, you need to know portnumber and its bandwidth.
But with outb you send a single byte, outw 2 bytes (16bits) and outd 4by(32bit).

The object oriented design would be to have a port object, which knows its bandwidth and portnumber.
And have two methods for R/W.