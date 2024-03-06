#!/bin/sh

pushd src/Test
  make test
popd
build/test
