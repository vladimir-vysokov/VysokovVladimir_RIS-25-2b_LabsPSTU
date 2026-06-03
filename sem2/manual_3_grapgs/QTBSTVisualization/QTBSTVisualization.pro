QT += core gui widgets

CONFIG += c++20
TEMPLATE = app
TARGET = QTBSTVisualization

SOURCES += \
    main.cpp \
    MainWindow.cpp \
    BST.cpp \
    UiVertex.cpp \
    GraphWorker.cpp

HEADERS += \
    MainWindow.h \
    BST.h \
    UiVertex.h \
    GraphWorker.h
