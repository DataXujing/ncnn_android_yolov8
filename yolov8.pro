QT       += core gui multimedia multimediawidgets
QT += androidextras testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    myqlabel.cpp \
    myvideosurface.cpp \
    widget.cpp \
    yolo.cpp

HEADERS += \
    myqlabel.h \
    myvideosurface.h \
    widget.h \
    yolo.h

FORMS += \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

QMAKE_CXXFLAGS += -fopenmp -static-openmp
QMAKE_LFLAGS += -fopenmp -static-openmp
LIBS += -fopenmp -static-openmp

android {
ANDROID_OPENCV = F:/andriod_env/OpenCV-android-sdk/sdk/native
#ANDROID_OPENCV = D:/NCNN/opencv-mobile-4.5.1-android/sdk/native
INCLUDEPATH += \
$$ANDROID_OPENCV/jni/include/opencv2 \
$$ANDROID_OPENCV/jni/include \
F:/andriod_env/ncnn/ncnn-20220729-android/armeabi-v7a/include \
F:/andriod_env/ncnn/ncnn-20220729-android/armeabi-v7a/include/ncnn


LIBS += \
$$ANDROID_OPENCV/staticlibs/armeabi-v7a/libopencv_ml.a \
$$ANDROID_OPENCV/staticlibs/armeabi-v7a/libopencv_objdetect.a \
$$ANDROID_OPENCV/staticlibs/armeabi-v7a/libopencv_calib3d.a \
$$ANDROID_OPENCV/staticlibs/armeabi-v7a/libopencv_video.a \
$$ANDROID_OPENCV/staticlibs/armeabi-v7a/libopencv_features2d.a \
$$ANDROID_OPENCV/staticlibs/armeabi-v7a/libopencv_highgui.a \
$$ANDROID_OPENCV/staticlibs/armeabi-v7a/libopencv_flann.a \
$$ANDROID_OPENCV/staticlibs/armeabi-v7a/libopencv_imgproc.a \
$$ANDROID_OPENCV/staticlibs/armeabi-v7a/libopencv_dnn.a \
$$ANDROID_OPENCV/staticlibs/armeabi-v7a/libopencv_core.a \
$$ANDROID_OPENCV/3rdparty/libs/armeabi-v7a/libcpufeatures.a \
$$ANDROID_OPENCV/3rdparty/libs/armeabi-v7a/libIlmImf.a \
#$$ANDROID_OPENCV/3rdparty/libs/armeabi-v7a/liblibjasper.a \
$$ANDROID_OPENCV/3rdparty/libs/armeabi-v7a/liblibjpeg-turbo.a \
$$ANDROID_OPENCV/3rdparty/libs/armeabi-v7a/liblibpng.a \
$$ANDROID_OPENCV/3rdparty/libs/armeabi-v7a/liblibprotobuf.a \
$$ANDROID_OPENCV/3rdparty/libs/armeabi-v7a/liblibtiff.a \
$$ANDROID_OPENCV/3rdparty/libs/armeabi-v7a/liblibwebp.a \
$$ANDROID_OPENCV/3rdparty/libs/armeabi-v7a/libquirc.a \
$$ANDROID_OPENCV/3rdparty/libs/armeabi-v7a/libtbb.a \
$$ANDROID_OPENCV/3rdparty/libs/armeabi-v7a/libtegra_hal.a \
$$ANDROID_OPENCV/libs/armeabi-v7a/libopencv_java4.so \
F:/andriod_env/ncnn/ncnn-20220729-android/armeabi-v7a/lib/libncnn.a \
F:/andriod_env/qtforandroid/android-ndk-r21/platforms/android-28/arch-arm/usr/lib/libandroid.so \
F:/andriod_env/qtforandroid/android-ndk-r21/toolchains/llvm/prebuilt/windows-x86_64/lib64/clang/9.0.8/lib/linux/arm/libomp.a \
F:/andriod_env/qtforandroid/android-ndk-r21/toolchains/llvm/prebuilt/windows-x86_64/lib64/clang/9.0.8/lib/linux/arm/libomp.so

# opencv-mobile配置 已废弃
#$$ANDROID_OPENCV/staticlibs/armeabi-v7a/libopencv_core.a \
#$$ANDROID_OPENCV/staticlibs/armeabi-v7a/libopencv_features2d.a \
#$$ANDROID_OPENCV/staticlibs/armeabi-v7a/libopencv_highgui.a \
#$$ANDROID_OPENCV/staticlibs/armeabi-v7a/libopencv_imgproc.a \
#$$ANDROID_OPENCV/staticlibs/armeabi-v7a/libopencv_photo.a \
#$$ANDROID_OPENCV/staticlibs/armeabi-v7a/libopencv_video.a \

# add other file to assets

data.files += assets/ai.png
data.files += assets/icon.png
data.files += model/yolov8s_opt.param
data.files += model/yolov8s_opt.bin

data.path = /assets/pic
INSTALLS += data

}


ANDROID_EXTRA_LIBS += F:/andriod_env/OpenCV-android-sdk/sdk/native/libs/armeabi-v7a/libopencv_java4.so \
                      F:/andriod_env/qtforandroid/android-ndk-r21/platforms/android-28/arch-arm/usr/lib/libandroid.so \
                      F:/andriod_env/qtforandroid/android-ndk-r21/toolchains/llvm/prebuilt/windows-x86_64/lib64/clang/9.0.8/lib/linux/arm/libomp.so

DISTFILES += \
    android/AndroidManifest.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew \
    android/gradlew.bat \
    android/res/values/libs.xml

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

RESOURCES += \
    pic.qrc
