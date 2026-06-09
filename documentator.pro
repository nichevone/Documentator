QT += core gui widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Libraries
SOURCES += \
    duckx/src/duckx.cpp \
    filehandler.cpp \
    thirdparty/pugixml/pugixml.cpp \
    thirdparty/zip/zip.c

HEADERS += \
    duckx/include/constants.hpp \
    duckx/include/duckx.hpp \
    duckx/include/duckxiterator.hpp \
    filehandler.h \
    thirdparty/pugixml/pugixml.hpp \
    thirdparty/pugixml/pugiconfig.hpp \
    thirdparty/zip/zip.h \
    thirdparty/zip/miniz.h

INCLUDEPATH += $$PWD/duckx/include
INCLUDEPATH += $$PWD/thirdparty/pugixml
INCLUDEPATH += $$PWD/thirdparty/zip

# Sources
SOURCES += \
    main.cpp \
    window.cpp

HEADERS += \
    window.h

FORMS += \
    window.ui

# Copy the whole templates folder to build folder
assets.files = $$PWD/templates/*
assets.path = $$OUT_PWD/templates
COPIES += assets

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target