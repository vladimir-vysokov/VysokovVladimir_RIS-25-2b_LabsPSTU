cmake_minimum_required(VERSION 3.16)
project(GraphAlgorithms VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

add_executable(GraphAlgorithms
    WIN32
    MACOSX_BUNDLE
    main.cpp
    graph.cpp
    graphview.cpp
    mainwindow.cpp
)

target_link_libraries(GraphAlgorithms
    Qt6::Core
    Qt6::Widgets
)

set_target_properties(GraphAlgorithms PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.GraphAlgorithms
    MACOSX_BUNDLE_BUNDLE_NAME GraphAlgorithms
)

install(TARGETS GraphAlgorithms
    BUNDLE DESTINATION .
    RUNTIME DESTINATION bin
)
