#!/bin/bash

SRC_H=../../XLib/jni

DIRS="init page platform platform/jni util util/datetime util/http util/log util/schedule util/sqlite3 util/thread util/timer util/tinyxml util/variant widgets"

for i in $DIRS; do
	mkdir $i
	cp $SRC_H/$i/*.h $i
done