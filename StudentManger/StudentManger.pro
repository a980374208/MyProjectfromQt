QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    admin.cpp \
    coursemanger.cpp \
    dialog_addcourse.cpp \
    dialog_addteacher.cpp \
    dialog_appointtable.cpp \
    dialog_changepassword.cpp \
    dialog_register.cpp \
    main.cpp \
    mainwindow.cpp \
    modifyedachidialog.cpp \
    student.cpp \
    teacher.cpp \
    teachermanger.cpp

HEADERS += \
    admin.h \
    coursemanger.h \
    dialog_addcourse.h \
    dialog_addteacher.h \
    dialog_appointtable.h \
    dialog_changepassword.h \
    dialog_register.h \
    mainwindow.h \
    modifyedachidialog.h \
    student.h \
    teacher.h \
    teachermanger.h

FORMS += \
    admin.ui \
    coursemanger.ui \
    dialog_addcourse.ui \
    dialog_addteacher.ui \
    dialog_appointtable.ui \
    dialog_changepassword.ui \
    dialog_register.ui \
    mainwindow.ui \
    modifyedachidialog.ui \
    student.ui \
    teacher.ui \
    teachermanger.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=
TRANSLATIONS += ./trans_ch.ts

RESOURCES += \
    img/img.qrc
