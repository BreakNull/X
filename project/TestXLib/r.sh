#!/bin/bash
ndk-build
cp ../XLib/libs/armeabi/libX.so libs/armeabi
echo "cp libX.so ==> libs/armeabi/libX.so"
