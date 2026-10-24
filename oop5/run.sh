#!/usr/bin/env bash
set -e
cd "$(dirname "$0")"
g++ optimization.cpp -o optimization
./optimization
