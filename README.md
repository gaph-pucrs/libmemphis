# libmemphis

Support library for applications targeting [MA-Memphis](https://github.com/gaph-pucrs/MA-Memphis) platform.

It includes several functions related to message-passing and newlib support.
Please check [memphis.h](src/include/memphis.h) for documentation.

## Installation

Currently, MA-Memphis supports RISC-V cores simulated in Linux hosts.

### Pre-requisites

* riscv64-elf-gcc

### Building

Run `make`.
It should produce a `libmemphis.a`.
