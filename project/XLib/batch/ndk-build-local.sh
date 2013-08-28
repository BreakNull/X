#!/bin/bash
OLDDIR=$(pwd)
SHPATH=$(cd $(dirname $0);pwd)
cd $SHPATH

cd ..

echo ndk build on bash
NDK_VER=$(cat $ANDROID_NDK_ROOT/RELEASE.TXT)
echo "using ndk version: $NDK_VER"
echo "===================build native code=========================="
ndk-build -j4
RETURN_PARAM=$?

if test $RETURN_PARAM = 0
then
	echo "NDK Build SUCCESSFUL"
else
	echo "NDK Build Error"
	exit 1
fi
