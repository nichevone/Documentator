QT += core gui widgets

CONFIG += c++17
# Build with static libs instead of dynamic
CONFIG += static staticlib
# Disable compiler-specific extensions
CONFIG += strict_c++

QMAKE_CXXFLAGS += -fno-sized-deallocation

# Strip symbols on unix-based distros
unix:!macx {
    QMAKE_STRIP = strip
}



# Sources
SOURCES += \
    src/main.cpp \
    src/window.cpp \
    src/filehandler.cpp \
    src/docxmanipulator.cpp

HEADERS += \
    src/window.h \
    src/filehandler.h \
    src/docxmanipulator.h \
    src/constants.h

FORMS += \
    forms/window.ui



# Libraries
SOURCES += \
    thirdparty/duckx/src/duckx.cpp \
    thirdparty/pugixml/pugixml.cpp \
    thirdparty/zip/zip.c

HEADERS += \
    thirdparty/duckx/include/constants.hpp \
    thirdparty/duckx/include/duckx.hpp \
    thirdparty/duckx/include/duckxiterator.hpp \
    thirdparty/pugixml/pugixml.hpp \
    thirdparty/pugixml/pugiconfig.hpp \
    thirdparty/zip/zip.h \
    thirdparty/zip/miniz.h



INCLUDEPATH += $$PWD/thirdparty/duckx/include
INCLUDEPATH += $$PWD/thirdparty/pugixml
INCLUDEPATH += $$PWD/thirdparty/zip

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
