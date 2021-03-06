#-------------------------------------------------
#
# Project created by QtCreator 2019-05-28T19:04:32
#
#-------------------------------------------------

QT       += core gui
QT       += serialbus serialport widgets
QT += winextras #毛玻璃尝试

#权限  需要以管理员运行creator
QMAKE_LFLAGS += /MANIFESTUAC:\"level=\'requireAdministrator\' uiAccess=\'false\'\" #以管理员运行
QMAKE_LFLAGS += /SUBSYSTEM:WINDOWS,\"5.01\" #VS2013 在XP运行

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
    debugMode.cpp \
    historyimage.cpp \
    keyboard.cpp \
    Listener1.cpp \
    main.cpp \
    maindialog.cpp \
    password.cpp \
    sys.cpp \
    sysdate.cpp \
    TIS_Camera.cpp \
    lineRotate.cpp \
    easyModbus02.cpp \
    statewidget.cpp \
    adjustparameters.cpp \
    threeparams.cpp \
    paramsetting.cpp \
    ClassThresholdTools.cpp \
    FxPLC.cpp \
    TIS_Camera2.cpp \
    Listener2.cpp \
    lineRotate2.cpp \
    paramsetting2.cpp \
    adjustparameters2.cpp \
    paramsetting.cpp \
    threeparams2.cpp

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
    msvc_macro.h \
    password.h \
    sys.h \
    sysdate.h \
    TIS_Camera.h \
    LineRotate.h \
    CRC16.h \
    easyModbus02.h \
    statewidget.h \
    adjustparameters.h \
    threeparams.h \
    paramsetting.h \
    ClassThresholdTools.h \
    FxPlc.h \
    TIS_Camera2.h \
    Listener2.h \
    LineRotate2.h \
    paramsetting2.h \
    adjustparameters2.h \
    paramsetting2.h \
    paramsetting.h \
    threeparams2.h

FORMS += \
        maindialog.ui \
    historyimage.ui \
    keyboard.ui \
    password.ui \
    sys.ui \
    debugMode.ui \
    adjustparameters.ui \
    threeparams.ui \
    adjustparameters2.ui \
    threeparams2.ui

RC_ICONS = 1.ico

#CONFIG += console


DEPENDPATH += $$PWD/include

INCLUDEPATH += $$quote(D:\QT\wire\include)
#INCLUDEPATH += D:\OPENCV\build\include
#INCLUDEPATH += D:\OPENCV\build\include\opencv2
INCLUDEPATH += D:\OPENCV\opencv4.1\build\include
INCLUDEPATH += D:\OPENCV\opencv4.1\build\include\opencv2

LIBS += $$quote(D:\QT\wire\Library\TIS_UDSHL11_x64.lib)
LIBS += $$quote(D:\QT\wire\Library\TIS_UDSHL11d_x64.lib)
#LIBS += $$quote(D:\QT\wire\Library\FxPlc.lib)

win32: LIBS += -L$$PWD/Library/ -llibmodbus-5

#CONFIG(debug, debug|release): {
#LIBS += -LD:\OPENCV\build\x64\vc14\lib \
#-lopencv_world320 \
#-lopencv_world320d \
#} else:CONFIG(release, debug|release): {
#LIBS += -LD:\OPENCV\build\x64\vc14\lib \
#-lopencv_world320 \
#-lopencv_world320d \
#}

CONFIG(debug, debug|release): {
LIBS += -LD:\OPENCV\opencv4.1\build\x64\vc14\lib \
#-lopencv_world410 \
-lopencv_world410d \
} else:CONFIG(release, debug|release): {
LIBS += -LD:\OPENCV\opencv4.1\build\x64\vc14\lib \
-lopencv_world410 \
#-lopencv_world410d \
}

DISTFILES +=

RESOURCES += \
    style1.qrc
