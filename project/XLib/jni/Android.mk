LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

#TARGET_ARCH_ABI :=armeabi-v7a

ifeq ($(TARGET_ARCH_ABI),armeabi-v7a)
	TARGET_LIB_PATH=/armv7-a/thumb
endif
ifeq ($(TARGET_ARCH_ABI),armeabi)
	TARGET_LIB_PATH=/thumb
endif

ifeq ($(TARGET_ARCH),arm)
	LOCAL_ABI_INSTALL=arm-linux-androideabi
	LOCAL_ABI_CONFIGURE=arm-linux-androideabi
endif
ifeq ($(TARGET_ARCH),x86)
	LOCAL_ABI_INSTALL=x86
	LOCAL_ABI_CONFIGURE=i686-android-linux
endif
ifeq ($(TARGET_ARCH),mips)
	LOCAL_ABI_INSTALL=mipsel-linux-androideabi
	LOCAL_ABI_CONFIGURE=mipsel-linux-androideabi
endif


# ----Module generation name----
LOCAL_MODULE := libX


#---------------------------------------------------Source file folder define------------------------------------------------------------#SRCEXTS = .c .C .cc .cpp .CPP .c++ .cxx .cp
#SRCDIRS = $(LOCAL_PATH)/datetime $(LOCAL_PATH)/timer $(LOCAL_PATH)/log $(LOCAL_PATH)/thread $(LOCAL_PATH)/variant $(LOCAL_PATH)/sqlite3 \
		$(LOCAL_PATH)/tinyxml $(LOCAL_PATH)/init
		
#				---page---		
LOCAL_SRC_FILES:=	$(subst ./, ./page/, $(shell cd $(LOCAL_PATH)/page; find . -name '*.cpp'))

#				---platform---
LOCAL_SRC_FILES+=	$(subst ./, ./platform/, $(shell cd $(LOCAL_PATH)/platform; find . -name '*.cpp'))

#				---widgets---
LOCAL_SRC_FILES+=	$(subst ./, ./widgets/, $(shell cd $(LOCAL_PATH)/widgets; find . -name '*.cpp'))

#				---init---
LOCAL_SRC_FILES+=	$(subst ./, ./init/, $(shell cd $(LOCAL_PATH)/init; find . -name '*.cpp'))

#				---util---
LOCAL_SRC_FILES+=	$(subst ./, ./util/datetime/, $(shell cd $(LOCAL_PATH)/util/datetime; find . -name '*.cpp'))
LOCAL_SRC_FILES+=	$(subst ./, ./util/http/, $(shell cd $(LOCAL_PATH)/util/http; find . -name '*.cpp'))
LOCAL_SRC_FILES+=	$(subst ./, ./util/log/, $(shell cd $(LOCAL_PATH)/util/log; find . -name '*.cpp'))
LOCAL_SRC_FILES+=	$(subst ./, ./util/schedule/, $(shell cd $(LOCAL_PATH)/util/schedule; find . -name '*.cpp'))
LOCAL_SRC_FILES+=	$(subst ./, ./util/sqlite3/, $(shell cd $(LOCAL_PATH)/util/sqlite3; find . -name '*.cpp'))
LOCAL_SRC_FILES+=	$(subst ./, ./util/sqlite3/, $(shell cd $(LOCAL_PATH)/util/sqlite3; find . -name '*.c'))
LOCAL_SRC_FILES+=	$(subst ./, ./util/thread/, $(shell cd $(LOCAL_PATH)/util/thread; find . -name '*.cpp'))
LOCAL_SRC_FILES+=	$(subst ./, ./util/timer/, $(shell cd $(LOCAL_PATH)/util/timer; find . -name '*.cpp'))
LOCAL_SRC_FILES+=	$(subst ./, ./util/oml/, $(shell cd $(LOCAL_PATH)/util/oml; find . -name '*.cpp'))
LOCAL_SRC_FILES+=	$(subst ./, ./util/variant/, $(shell cd $(LOCAL_PATH)/util/variant; find . -name '*.cpp'))
LOCAL_SRC_FILES+=	$(subst ./, ./util/style/, $(shell cd $(LOCAL_PATH)/util/style; find . -name '*.cpp'))
LOCAL_SRC_FILES+=	$(subst ./, ./util/file/, $(shell cd $(LOCAL_PATH)/util/file; find . -name '*.cpp'))


#---------------------------------------------------Source file folder define------------------------------------------------------------


# ----Macro Define----
PROJECT_C_FLAGS:=	--exceptions \
					-msoft-float \
					-fsigned-char \
					-Wno-psabi \
					-O2 \
					-D_FOR_ANDROID_ \
					-DANDROID
					
LOCAL_CFLAGS:=		$(PROJECT_C_FLAGS) 

# ----Include path Define----					
PROJECT_INCLUDE:=	$(ANDROID_NDK_ROOT)/sources/cxx-stl/gnu-libstdc++/include \
					$(ANDROID_NDK_ROOT)/sources/cxx-stl/gnu-libstdc++/libs/$(TARGET_ARCH_ABI)/include \
					$(LOCAL_PATH)/page \
					$(LOCAL_PATH)/platform \
					$(LOCAL_PATH)/platform/jni \
					$(LOCAL_PATH)/widgets \
					$(LOCAL_PATH)/init \
					$(LOCAL_PATH)/util/datetime \
					$(LOCAL_PATH)/util/http \
					$(LOCAL_PATH)/util/log \
					$(LOCAL_PATH)/util/schedule \
					$(LOCAL_PATH)/util/sqlite3 \
					$(LOCAL_PATH)/util/thread \
					$(LOCAL_PATH)/util/timer \
					$(LOCAL_PATH)/util/oml \
					$(LOCAL_PATH)/util/variant  \
					$(LOCAL_PATH)/util/style  \
					$(LOCAL_PATH)/util/file
					
LOCAL_C_INCLUDES :=	$(PROJECT_INCLUDE) 


# ----Src file to build Define----					

#LOCAL_SRC_FILES := $(foreach d,$(SRCDIRS),$(wildcard $(addprefix $(d)/*,$(SRCEXTS))))



# ----Lib path Define----
PROJECT_LD_FLAGS:=	-Wl,-rpath-link=build/platforms/$(APP_PLATFORM)/arch-$(TARGET_ARCH)/usr/lib \
					-L$(call host-path,$(ANDROID_NDK_ROOT)/sources/cxx-stl/gnu-libstdc++/libs/$(TARGET_ARCH_ABI)) \
					-L$(call host-path,$(ANDROID_NDK_ROOT)/toolchains/$(LOCAL_ABI_INSTALL)-$(GCC_VER_SET)/prebuilt/$(HOST_TAG)/lib/gcc/$(LOCAL_ABI_CONFIGURE)/$(GCC_VER_SET)$(TARGET_LIB_PATH)) \
					-L$(call host-path,$(ANDROID_NDK_ROOT)/platforms/$(APP_PLATFORM)/arch-$(TARGET_ARCH)/usr/lib) \
					-L$(call host-path,$(TOP_PATH)/../obj/local/$(TARGET_ARCH_ABI)) \
					-llog \
					-lm \
					-lgcc

LOCAL_LDFLAGS:=		$(PROJECT_LD_FLAGS)


LOCAL_ARM_NEON:= 	$(NEON_MODE)

include $(BUILD_SHARED_LIBRARY)
