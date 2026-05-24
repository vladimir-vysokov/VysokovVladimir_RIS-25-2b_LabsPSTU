QT += core widgets

CONFIG += c++17
macx: CONFIG += app_bundle
win32: CONFIG += windows

TARGET = GraphAlgorithms
TEMPLATE = app

SOURCES += \
    main.cpp \
    graph.cpp \
    graphview.cpp \
    mainwindow.cpp

HEADERS += \
    graph.h \
    graphview.h \
    mainwindow.h

# Default rules for deployment
qnx: target.path = /tmp/$${TARGET}/bin
macx: target.path = /Applications
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
