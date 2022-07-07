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

INCLUDEPATH += $$PWD/headers

SOURCES += \
    src/addconsumerecorddialog.cpp \
    src/addsavingsdialog.cpp \
    src/dbsetting.cpp \
    src/logindialog.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/modifyconsumerecorddialog.cpp \
    src/modifysavingsdialog.cpp \
    src/registdialog.cpp

HEADERS += \
    headers/addconsumerecorddialog.h \
    headers/addsavingsdialog.h \
    headers/dbsetting.h \
    headers/logindialog.h \
    headers/mainwindow.h \
    headers/modifyconsumerecorddialog.h \
    headers/modifysavingsdialog.h \
    headers/registdialog.h

FORMS += \
    ui/addconsumerecorddialog.ui \
    ui/addsavingsdialog.ui \
    ui/logindialog.ui \
    ui/mainwindow.ui \
    ui/modifyconsumerecorddialog.ui \
    ui/modifysavingsdialog.ui \
    ui/registdialog.ui

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

