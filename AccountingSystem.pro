QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

QT += sql
# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addconsumerecorddialog.cpp \
    addsavingsdialog.cpp \
    dbsetting.cpp \
    logindialog.cpp \
    main.cpp \
    mainwindow.cpp \
    modifyconsumerecorddialog.cpp \
    modifysavingsdialog.cpp \
    registdialog.cpp

HEADERS += \
    addconsumerecorddialog.h \
    addsavingsdialog.h \
    dbsetting.h \
    logindialog.h \
    mainwindow.h \
    modifyconsumerecorddialog.h \
    modifysavingsdialog.h \
    registdialog.h

FORMS += \
    addconsumerecorddialog.ui \
    addsavingsdialog.ui \
    logindialog.ui \
    mainwindow.ui \
    modifyconsumerecorddialog.ui \
    modifysavingsdialog.ui \
    registdialog.ui

CONFIG(release):DESTDIR = $$PWD/../bin
CONFIG(debug, debug|release):DESTDIR = $$PWD/../bin 

OBJECTS_DIR = $$DESTDIR/.obj
MOC_DIR = $$DESTDIR/.moc
RCC_DIR = $$DESTDIR/.qrc
UI_DIR = $$DESTDIR/.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    app.icon

