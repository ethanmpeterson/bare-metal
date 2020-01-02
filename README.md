# bare-metal
Repository for Bare Metal C MCU programming primarily on ARM Cortex Chips. This
repository will serve as a monolithic repository for my ARM Cortex MCU projects.

## Flashing Code
The repository contains two approaches to programming the STM chip.
the first of which uses a Makefile to compile C code for ARM with the peripheral
libraries specific to the chip in use. The second approach uses PlatformIO which
abstracts all of that away with their command line tool. PlatformIO does not
support programming all STM chips with the lower level CMSIS Framework. Thus, if
a given project intends to use CMSIS and PlatformIO does not have support for
the particular MCU then the Makefile can be used.
