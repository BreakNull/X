#!/bin/bash
OLDDIR=$(pwd)
SHPATH=$(cd $(dirname $0);pwd)
cd $SHPATH/..

echo "===================clean native code=========================="
ndk-build clean

cd $OLDDIR
