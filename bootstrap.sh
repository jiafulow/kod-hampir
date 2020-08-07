#!/bin/bash

DEST="$1"

ORIG="my-hls-test-11"

mkdir -p $DEST
mkdir -p $DEST/firmware
mkdir -p $DEST/firmware/weights
mkdir -p $DEST/tb_data
cp $ORIG/.gitignore $DEST
cp $ORIG/build_prj.tcl $DEST
> $DEST/firmware/myproject.h
> $DEST/firmware/myproject.cpp
> $DEST/firmware/weights/.gitkeep
> $DEST/myproject_test.cpp
> $DEST/tb_data/.gitkeep

pushd $DEST/firmware
ln -s ../../external/hls/2019.08-bcolbf/include/ ap_types
popd
