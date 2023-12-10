#!/bin/bash
g++ Ultraword32.hpp Ultraword32.cpp -o uw32 -march=skylake-avx512
/home/max/Documents/Intel\ emulator/sde-external-9.24.0-2023-07-13-lin/sde -skx -- ./uw32
