#!/bin/sh

set -xe

clang -g3 -Wall -Wextra -Wpedantic -o example example.c
