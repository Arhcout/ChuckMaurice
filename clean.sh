#!/bin/sh

pushd src/Engine
  make clean
popd
pushd src/Test
  make clean
popd
