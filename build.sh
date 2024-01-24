#!/usr/bin/env bash

set -xe

mkdir -p target

g++ -Wall -Wextra -Wconversion -pedantic -g -Isrc/ src/*.cpp -o target/tic-tac-toe-minimax -lraylib
