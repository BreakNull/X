# Copyright (C) 2009 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_X_ROOT := $(LOCAL_PATH)/../../XLib/jni
LOCAL_CFLAGS += -D_FOR_ANDROID_
LOCAL_C_INCLUDES += $(LOCAL_X_ROOT)/init $(LOCAL_X_ROOT)/page $(LOCAL_X_ROOT)/platform \
					$(LOCAL_X_ROOT)/util/datetime $(LOCAL_X_ROOT)/util/http \
					$(LOCAL_X_ROOT)/util/log $(LOCAL_X_ROOT)/util/schedule $(LOCAL_X_ROOT)/util/sqlite3 \
					$(LOCAL_X_ROOT)/util/thread $(LOCAL_X_ROOT)/util/timer $(LOCAL_X_ROOT)/util/oml \
					$(LOCAL_X_ROOT)/util/variant $(LOCAL_X_ROOT)/util/style $(LOCAL_X_ROOT)/widgets
					
LOCAL_LDFLAGS += -L../XLib/libs/armeabi
LOCAL_MODULE    := TestX
LOCAL_SRC_FILES := main.cpp HelloPage.cpp NiPage.cpp
LOCAL_LDLIBS    := -llog -lX

include $(BUILD_SHARED_LIBRARY)
