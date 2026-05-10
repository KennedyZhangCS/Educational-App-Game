QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    dragitem.cpp \
    levelfour.cpp \
    levelone.cpp \
    levelsmenu.cpp \
    levelthree.cpp \
    leveltwo.cpp \
    main.cpp \
    mainwindow.cpp \
    startpage.cpp

HEADERS += \
    dragitem.h \
    levelfour.h \
    levelone.h \
    levelsmenu.h \
    levelthree.h \
    leveltwo.h \
    mainwindow.h \
    startpage.h

FORMS += \
    levelfour.ui \
    levelone.ui \
    levelsmenu.ui \
    levelthree.ui \
    leveltwo.ui \
    mainwindow.ui \
    startpage.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
