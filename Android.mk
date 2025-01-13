#
# Copyright (C) 2018 The LineageOS Project
#
# SPDX-License-Identifier: Apache-2.0
#

LOCAL_PATH := $(call my-dir)

ifneq ($(filter jasmine_sprout jason lavender platina twolip wayne whyred,$(TARGET_DEVICE)),)

include $(CLEAR_VARS)

include $(call all-makefiles-under,$(LOCAL_PATH))
endif
