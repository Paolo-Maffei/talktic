# Introduction #

This page describe how to build talktic binary which can be written in Atmel Atmega128 on Mac OS X 10.5.3(Leopard).
The current source of svn head shold be built under Win32 with Cygwin but, I forgot which toolchain are needed after I switched to Mac.

# Tools #

Ar first you should install the next tools into Mac OS X.

  1. Developer Tools (you can get it as iPhone SDK from developer.apple.com)
  1. AVR Mac Pack from http://www.obdev.at/products/avrmacpack/index.html

# Steps #

At first, getting the code from svn repository like:

```
 % svn co http://talktic.googlecode.com/svn/trunk talktic
```

and prep. for building:

```
 % avr-gcc-select 4
 % cd talktic
 % cd jsc
 % ant jar
 % cd ../src
 % touch bytecode.h
```

Then, build talktic:

```
 % cd ../build/proto1-moxa-avr-gcc
 % make
```

You may get a talktic binary named: talktic.hex