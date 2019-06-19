#-------------------------------------------------
#
# Project created by QtCreator 2019-05-28T19:04:32
#
#-------------------------------------------------

QT       += core gui
QT       += serialbus serialport widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = wire
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        maindialog.cpp \
    historyimage.cpp \
    keyboard.cpp \
    password.cpp \
    sys.cpp \
    sysdate.cpp \
    Listener1.cpp \
    historyimage.cpp \
    keyboard.cpp \
    Listener1.cpp \
    main.cpp \
    maindialog.cpp \
    password.cpp \
    sys.cpp \
    sysdate.cpp \
    debugMode.cpp \
    writeregistermodel.cpp \
    mainwindow.cpp \
    settingsdialog.cpp \
    debugMode.cpp \
    historyimage.cpp \
    keyboard.cpp \
    Listener1.cpp \
    main.cpp \
    maindialog.cpp \
    mainwindow.cpp \
    password.cpp \
    settingsdialog.cpp \
    sys.cpp \
    sysdate.cpp \
    writeregistermodel.cpp \
    TIS_Camera.cpp

HEADERS += \
        maindialog.h \
    msvc_macro.h \
    TIS_Camera.h \
    historyimage.h \
    keyboard.h \
    password.h \
    sys.h \
    sysdate.h \
    Listener1.h \
    historyimage.h \
    keyboard.h \
    Listener1.h \
    maindialog.h \
    msvc_macro.h \
    password.h \
    sys.h \
    sysdate.h \
    TIS_Camera.h \
    debugMode.h \
    writeregistermodel.h \
    mainwindow.h \
    settingsdialog.h \
    include/AnalogChannelItem.h \
    include/AviSink.h \
    include/Codec.h \
    include/DeBayerTransform.h \
    include/dshow_header.h \
    include/dstring.h \
    include/dvector.h \
    include/Error.h \
    include/filterdll.h \
    include/filterfactory.h \
    include/FilterInfoObject.h \
    include/filterloader.h \
    include/FrameFilter.h \
    include/FrameFilterBase.h \
    include/FrameFilterImpl.h \
    include/FrameGrabberSink.h \
    include/FrameHandlerSink.h \
    include/FrameType.h \
    include/Grabber.h \
    include/GrabberListener.h \
    include/GrabberSinkType.h \
    include/iframe_def.h \
    include/int_interface_pre.h \
    include/IVCDProperty.h \
    include/IVCDProperty_inl.h \
    include/IVCDPropertyInterfaces.h \
    include/IVCDPropertyInterfaces_inl.h \
    include/libbasedefs.h \
    include/libutil_string.h \
    include/MediaStreamContainer.h \
    include/MediaStreamSink.h \
    include/MemBuffer.h \
    include/MemBufferCollection.h \
    include/modbus-rtu.h \
    include/modbus-tcp.h \
    include/modbus-version.h \
    include/modbus.h \
    include/OverlayBitmap.h \
    include/simplectypes.h \
    include/smart_com.h \
    include/smart_ptr.h \
    include/tisudshl.h \
    include/UDSHL_defs.h \
    include/UDSHL_lnk.h \
    include/VCDPropertyDef.h \
    include/VCDPropertyID.h \
    include/VCDPropertyIDTis.h \
    include/VideoCaptureDeviceItem.h \
    include/VideoFormatDesc.h \
    include/VideoFormatItem.h \
    include/VideoNormItem.h \
    debugMode.h \
    historyimage.h \
    keyboard.h \
    Listener1.h \
    maindialog.h \
    mainwindow.h \
    msvc_macro.h \
    password.h \
    settingsdialog.h \
    sys.h \
    sysdate.h \
    TIS_Camera.h \
    writeregistermodel.h

FORMS += \
        maindialog.ui \
    historyimage.ui \
    keyboard.ui \
    password.ui \
    sys.ui \
    debugMode.ui \
    mainwindow.ui \
    settingsdialog.ui

#CONFIG += console


DEPENDPATH += $$PWD/include

INCLUDEPATH += $$quote(D:\QT\wire\include)
INCLUDEPATH += D:\OPENCV\build\include
INCLUDEPATH += D:\OPENCV\build\include\opencv2

LIBS += $$quote(D:\QT\wire\Library\TIS_UDSHL11_x64.lib)
LIBS += $$quote(D:\QT\wire\Library\TIS_UDSHL11d_x64.lib)

win32: LIBS += -L$$PWD/Library/ -llibmodbus-5

CONFIG(debug, debug|release): {
LIBS += -LD:\OPENCV\build\x64\vc14\lib \
-lopencv_world320 \
-lopencv_world320d \
} else:CONFIG(release, debug|release): {
LIBS += -LD:\OPENCV\build\x64\vc14\lib \
-lopencv_world320 \
-lopencv_world320d \
}

DISTFILES +=

RESOURCES += \
    style1.qrc
