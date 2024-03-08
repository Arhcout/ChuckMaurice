#!/bin/sh
pushd src/Engine
  make engine
popd

rm -f build/test
