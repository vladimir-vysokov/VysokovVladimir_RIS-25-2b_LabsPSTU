QT += core gui widgets

CONFIG += c++20
TEMPLATE = app
TARGET = QTBNBVisualization

SOURCES += \
    main.cpp \
    MainWindow.cpp \
    Graph.cpp \
    UiVertex.cpp \
    UiEdge.cpp \
    GraphWorker.cpp \
    MatrixEditor.cpp

HEADERS += \
    MainWindow.h \
    Graph.h \
    UiVertex.h \
    UiEdge.h \
    GraphWorker.h \
    MatrixEditor.h
