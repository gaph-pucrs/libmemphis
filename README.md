# libmemphis

Support library for applications targeting [Memphis-V](https://github.com/gaph-pucrs/Memphis-5) and [MA-Memphis](https://github.com/gaph-pucrs/MA-Memphis) platforms.

It includes several functions related to message-passing and newlib support.
Please check [memphis.h](src/include/memphis.h) for documentation.

## Installation

Currently, the library supports RISC-V cores.

### Pre-requisites

* riscv64-elf-gcc

### Building

Run `make`.
It should produce a `libmemphis.a`.
