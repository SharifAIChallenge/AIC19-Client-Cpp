#!/bin/sh

set -e

mkdir -p "$TRAVIS_BUILD_DIR/build"
cd "$TRAVIS_BUILD_DIR/build"
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . -- -j3

