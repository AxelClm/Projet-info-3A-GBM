QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    dicomimage.cpp \
    dicomreader.cpp \
    dicomrow.cpp \
    groupdisplayer.cpp \
    imagedisplayer.cpp \
    main.cpp \
    fenetre.cpp \
    parsingjob.cpp \
    seriedamier.cpp \
    seriedisplayer.cpp \
    seriefusion.cpp \
    series.cpp \
    synchro.cpp \
    viewcontroler.cpp

HEADERS += \
    dicomimage.h \
    dicomreader.h \
    dicomrow.h \
    fenetre.h \
    groupdisplayer.h \
    imagedisplayer.h \
    parsingjob.h \
    seriedamier.h \
    seriedisplayer.h \
    seriefusion.h \
    series.h \
    synchro.h \
    viewcontroler.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
