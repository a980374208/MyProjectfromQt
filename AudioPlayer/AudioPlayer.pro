QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    images/001.GIF \
    images/110.JPG \
    images/132.bmp \
    images/212.bmp \
    images/214.bmp \
    images/22.ico \
    images/224.bmp \
    images/23.ico \
    images/237.GIF \
    images/316.bmp \
    images/318.bmp \
    images/430.bmp \
    images/5.ico \
    images/610.bmp \
    images/612.bmp \
    images/616.bmp \
    images/620.bmp \
    images/622.bmp \
    images/624.bmp \
    images/630.bmp \
    images/632.bmp \
    images/828.bmp \
    images/Audio CD.ico \
    images/Movie Clip.ico \
    images/Recycle Bin empty.ico \
    images/Wave Sound.ico \
    images/audio_file.ico \
    images/music.ico \
    images/mute.bmp \
    images/volumn.bmp

RESOURCES += \
    res.qrc
