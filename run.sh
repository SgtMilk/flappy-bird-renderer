#!/bin/bash

rm -rf build
mkdir build

cmake --build .
./flappy-bird-renderer
