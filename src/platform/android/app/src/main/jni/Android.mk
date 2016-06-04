LOCAL_PATH := $(call my-dir)
PROJECT_ROOT_PATH := $(LOCAL_PATH)/../../../../../../
CORE_RELATIVE_PATH := ../../../../../../core/



include $(CLEAR_VARS)
LOCAL_MODULE := curl-prebuilt
LOCAL_SRC_FILES := $(PROJECT_ROOT_PATH)/3rdparty/prebuilt-with-ssl/android/$(TARGET_ARCH_ABI)/libcurl.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)

LOCAL_MODULE    := mapsport
//LOCAL_CFLAGS    := -Wall -Wextra
LOCAL_SRC_FILES := platform_asset_utils.c \
                   platform_log.c \
                   renderer_wrapper.cpp \
                   $(CORE_RELATIVE_PATH)/mapview.cpp \
                   $(CORE_RELATIVE_PATH)/tile.cpp \
                   $(CORE_RELATIVE_PATH)/camera.cpp \
                   $(CORE_RELATIVE_PATH)/vertex.cpp \
				   $(CORE_RELATIVE_PATH)/asset_utils.c \
				   $(CORE_RELATIVE_PATH)/buffer.c \
                   $(CORE_RELATIVE_PATH)/image.c \
                   $(CORE_RELATIVE_PATH)/shader.c \
                   $(CORE_RELATIVE_PATH)/texture.c \
                   $(CORE_RELATIVE_PATH)/tilelayer.cpp \
                   $(CORE_RELATIVE_PATH)/file_system_tile_loader.cpp \
                   $(CORE_RELATIVE_PATH)/rect.cpp \
                   $(CORE_RELATIVE_PATH)/position.cpp \
                   $(CORE_RELATIVE_PATH)/file_loader.cpp \
                   $(CORE_RELATIVE_PATH)/file_data.cpp \
                   $(CORE_RELATIVE_PATH)/raw_image.cpp \
                   $(CORE_RELATIVE_PATH)/network_tile_reader.cpp \
                   $(CORE_RELATIVE_PATH)/filesystem_tile_reader.cpp \
                   $(CORE_RELATIVE_PATH)/tile_reader_base.cpp \
                   $(CORE_RELATIVE_PATH)/tile_writer_base.cpp \
                   PlatformFileSystemTileWriter.cpp \
                   HttpPlatform.cpp \
                   FileLoaderPlatform.cpp \
                  
LOCAL_C_INCLUDES := $(PROJECT_ROOT_PATH)/platform/common/
LOCAL_C_INCLUDES += $(PROJECT_ROOT_PATH)/core/
LOCAL_C_INCLUDES += $(PROJECT_ROOT_PATH)/3rdparty/linmath/
LOCAL_C_INCLUDES += $(PROJECT_ROOT_PATH)/3rdparty/prebuilt-with-ssl/android/include
LOCAL_C_INCLUDES += $(CORE_RELATIVE_PATH)/
LOCAL_STATIC_LIBRARIES := libpng
LOCAL_STATIC_LIBRARIES += curl-prebuilt
LOCAL_LDLIBS := -lGLESv2 -llog -landroid -lz
//LOCAL_CFLAGS += -x c++
include $(BUILD_SHARED_LIBRARY)

$(call import-add-path,$(PROJECT_ROOT_PATH)3rdparty)
$(call import-module,libpng)