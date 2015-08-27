LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := lshtest
LOCAL_SRC_FILES := com_rgb0101_lsh_test_MainActivity.c lsh160_generic.c hmac_sha1.c sha1.c
LOCAL_LDLIBS := -llog

include $(BUILD_SHARED_LIBRARY)