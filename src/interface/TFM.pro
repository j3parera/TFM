QT       += widgets charts qml quick network opengl sql script scripttools svg xml xmlpatterns multimedia testlib dbus

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TFM
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += main.cpp\
        mainwindow.cpp \
    ../tools/Logger.cpp \
    ../tools/fft.cpp \
    ../module/AudioObject.cpp \
    ../module/AudioSignal.cpp \
    ObjectsConfiguration.cpp \
    Objects.cpp \
    ObjectInput.cpp \
    DeviceChannel.cpp \
    DeviceLevel.cpp \
    Device.cpp \
    AudioChart.cpp

HEADERS  += mainwindow.h \
    ../tools/Logger.h \
    ../tools/fft.h \
    ../module/AudioObject.h \
    ../module/AudioSignal.h \
    ../../lib/QtLibraries/src/qtlibraries.h \
    objects.h \
    device.h \
    audiochart.h

FORMS    += mainwindow.ui
