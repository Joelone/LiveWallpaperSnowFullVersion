LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := LiveWallpaperNative
LOCAL_SRC_FILES := NDKParticle.cpp \
                   NDKLiveWallpaperRenderer.cpp \
                   NDKBackground.cpp \
                   WallpaperObject.cpp \
                   Background.cpp \
                   Particle.cpp \
                   Matrix.cpp   \
                   Config.cpp   \
                   GLCommon.cpp \

LOCAL_LDLIBS := -lGLESv1_CM -llog

include $(BUILD_SHARED_LIBRARY)