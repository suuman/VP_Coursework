#-------------------------------------------------
#
# Project created by QtCreator 2012-03-22T20:29:45
#
#-------------------------------------------------

QT += widgets
TARGET = vp_hw

QT += testlib


SOURCES += main.cpp\
window_QT.cpp     \
        mainwindow.cpp \
    options.cpp \
    cvfunctions.cpp \
    CameraCalibrator.cpp

HEADERS  += mainwindow.h \
    window_QT.h \
    options.h \
    cvfunctions.h \
    definations.h \
    matcher.h \
    CameraCalibrator.h

FORMS    += mainwindow.ui \
    options.ui

## For windows
win32 {
    # Set this to the folder where you compiled the opencv source
    OPENCV_DIR = "C:\OpenCV"

    INCLUDEPATH += $$OPENCV_DIR\\include \
                $$OPENCV_DIR\\include\\opencv \
                $$OPENCV_DIR\\include\\opencv2
    LIBS += -L$$OPENCV_DIR\\lib \
        -lopencv_core231.dll \
        -lopencv_highgui231.dll \
        -lopencv_imgproc231.dll \
        -lopencv_features2d231.dll \
        -lopencv_calib3d231.dll\
        -lopencv_flann231.dll\
        -lopencv_contrib231.dll\
        -lopencv_objdetect231.dll
}

# For Linux
unix {
    # using pkg-config
    CONFIG += link_pkgconfig
    PKGCONFIG += opencv4
}

RESOURCES += \
    window_QT.qrc
