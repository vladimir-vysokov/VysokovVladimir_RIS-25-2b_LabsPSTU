cmake_minimum_required(VERSION 3.20)

project(vysokov_rebuilt_materials LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
option(BUILD_QT_PROJECTS "Build Qt visualization projects when Qt6 is available" ON)

function(add_lab target)
    add_executable(${target} ${ARGN})
    target_include_directories(${target} PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}
            ${CMAKE_CURRENT_SOURCE_DIR}/sem2/manual_1/lab11)
endfunction()

function(add_qt_lab target dir)
    add_executable(${target} ${ARGN})
    target_include_directories(${target} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/${dir})
    target_link_libraries(${target} Qt6::Core Qt6::Gui Qt6::Widgets)
    set_target_properties(${target} PROPERTIES
            AUTOMOC ON
            AUTORCC ON
            AUTOUIC ON
            CXX_STANDARD 20
            CXX_STANDARD_REQUIRED ON)
endfunction()

# Первый семестр: домашние задания.
add_lab(sem1_hometasks_switch sem1/hometasks/switch.cpp)
add_lab(sem1_homeworks_empty_square sem1/homeworks/2025.09.01_empty_square.cpp)
add_lab(sem1_homeworks_isosceles_triangle sem1/homeworks/2025.09.01_isosceles_triangle.cpp)
add_lab(sem1_homeworks_isosceles_triangle_down sem1/homeworks/2025.09.01_isosceles_triangle_down.cpp)
add_lab(sem1_homeworks_main sem1/homeworks/2025.09.01_main.cpp)
add_lab(sem1_homeworks_rhomb sem1/homeworks/2025.09.01_rhomb.cpp)

# Первый семестр: лабораторная работа 7.
add_lab(sem1_lab7_bisection sem1/lab7/bisection.cpp)
add_lab(sem1_lab7_iteration_method sem1/lab7/iteration_method.cpp)
add_lab(sem1_lab7_newton sem1/lab7/newton.cpp)

# Второй семестр: домашние задания 1.
add_lab(sem2_hw1_8_queens sem2/homeworks_1/8_queens/2026.02.23_8_queens.cpp)
add_lab(sem2_hw1_bracket_sequences sem2/homeworks_1/bracket_sequences/main.cpp)
add_lab(sem2_hw1_fibonacci sem2/homeworks_1/fibonacci/2026.02.23_fibonacci.cpp)
add_lab(sem2_hw1_hanoi sem2/homeworks_1/hanoi/2026.02.23_hanoi.cpp)
add_lab(sem2_hw1_is_sort sem2/homeworks_1/isSort/main.cpp)
add_lab(sem2_hw1_max sem2/homeworks_1/max/2026.02.06_max.cpp)
add_lab(sem2_hw1_reverse sem2/homeworks_1/reverse/2026.02.06_reverse.cpp)
add_lab(sem2_hw1_sort_bubble sem2/homeworks_1/sorts/2026.02.06_buble.cpp)
add_lab(sem2_hw1_sort_insertion sem2/homeworks_1/sorts/2026.02.06_insertion.cpp)
add_lab(sem2_hw1_sort_selection sem2/homeworks_1/sorts/2026.02.06_selection.cpp)

# Второй семестр: домашние задания 2.
add_lab(sem2_hw2_difficult_searches sem2/homeworks_2/difficult_searches/main.cpp)
add_lab(sem2_hw2_external_sorts sem2/homeworks_2/external_sorts/main.cpp)
add_lab(sem2_hw2_hash_tables
        sem2/homeworks_2/hash_tables/main.cpp)
add_lab(sem2_hw2_quick_sorts sem2/homeworks_2/quick_sorts/main.cpp)
add_lab(sem2_hw2_simple_searches sem2/homeworks_2/simple_searches/main.cpp)
add_lab(sem2_hw2_simple_sorts_bucket sem2/homeworks_2/simple_sorts/bucket.cpp)
add_lab(sem2_hw2_simple_sorts_bucket_presentation sem2/homeworks_2/simple_sorts/bucket_presentation.cpp)
add_lab(sem2_hw2_simple_sorts_counting sem2/homeworks_2/simple_sorts/counting.cpp)
add_lab(sem2_hw2_simple_sorts_counting_nums sem2/homeworks_2/simple_sorts/counting_nums.cpp)
add_lab(sem2_hw2_simple_sorts_main sem2/homeworks_2/simple_sorts/main.cpp)
add_lab(sem2_hw2_simple_sorts_merge sem2/homeworks_2/simple_sorts/merge.cpp)

# Второй семестр: методичка 1.
add_lab(sem2_manual1_lab03 sem2/manual_1/lab03/main.cpp)
add_lab(sem2_manual1_lab04 sem2/manual_1/lab04/main.cpp)
add_lab(sem2_manual1_lab05 sem2/manual_1/lab05/main.cpp)
add_lab(sem2_manual1_lab06 sem2/manual_1/lab06/main.cpp)
add_lab(sem2_manual1_lab07_task_1 sem2/manual_1/lab07/7.1.cpp)
add_lab(sem2_manual1_lab07_task_2 sem2/manual_1/lab07/7.2.cpp)
add_lab(sem2_manual1_lab07_test sem2/manual_1/lab07/test.cpp)
add_lab(sem2_manual1_lab08 sem2/manual_1/lab08/main.cpp)
add_lab(sem2_manual1_lab09 sem2/manual_1/lab09/main.cpp)
add_lab(sem2_manual1_lab10 sem2/manual_1/lab10/main.cpp)
add_lab(sem2_manual1_lab11 sem2/manual_1/lab11/main.cpp)
add_lab(sem2_manual1_lab11_queue sem2/manual_1/lab11/queue/queue.cpp)

# Второй семестр: объектно-ориентированное программирование.
add_lab(sem2_oop_lab01 sem2/manual_2_oop/lab01/main.cpp)
add_lab(sem2_oop_lab02 sem2/manual_2_oop/lab02/main.cpp)
add_lab(sem2_oop_lab03 sem2/manual_2_oop/lab03/main.cpp)
add_lab(sem2_oop_lab04 sem2/manual_2_oop/lab04/main.cpp)
add_lab(sem2_oop_lab05 sem2/manual_2_oop/lab05/main.cpp)
add_lab(sem2_oop_lab06 sem2/manual_2_oop/lab06/main.cpp)
add_lab(sem2_oop_lab07 sem2/manual_2_oop/lab07/main.cpp)
add_lab(sem2_oop_lab08 sem2/manual_2_oop/lab08/main.cpp)
add_lab(sem2_oop_lab09 sem2/manual_2_oop/lab09/main.cpp)
add_lab(sem2_oop_lab10 sem2/manual_2_oop/lab10/main.cpp)
add_lab(sem2_oop_lab11 sem2/manual_2_oop/lab11/main.cpp)
add_lab(sem2_oop_lab12 sem2/manual_2_oop/lab12/main.cpp)
add_lab(sem2_oop_lab13 sem2/manual_2_oop/lab13/main.cpp)

# Qt-визуализации подключаются только если в CLion настроен Qt6.
# Так консольные лабораторные не ломаются на компьютере без Qt SDK.
if(BUILD_QT_PROJECTS)
    find_package(Qt6 COMPONENTS Core Gui Widgets QUIET)
    if(Qt6_FOUND)
        add_qt_lab(QTGraphVisualization sem2/manual_3_grapgs/QTGraphVisualization
                sem2/manual_3_grapgs/QTGraphVisualization/main.cpp
                sem2/manual_3_grapgs/QTGraphVisualization/MainWindow.cpp
                sem2/manual_3_grapgs/QTGraphVisualization/MainWindow.h
                sem2/manual_3_grapgs/QTGraphVisualization/Graph.cpp
                sem2/manual_3_grapgs/QTGraphVisualization/Graph.h
                sem2/manual_3_grapgs/QTGraphVisualization/UiVertex.cpp
                sem2/manual_3_grapgs/QTGraphVisualization/UiVertex.h
                sem2/manual_3_grapgs/QTGraphVisualization/UiEdge.cpp
                sem2/manual_3_grapgs/QTGraphVisualization/UiEdge.h
                sem2/manual_3_grapgs/QTGraphVisualization/GraphWorker.cpp
                sem2/manual_3_grapgs/QTGraphVisualization/GraphWorker.h
                sem2/manual_3_grapgs/QTGraphVisualization/MatrixEditor.cpp
                sem2/manual_3_grapgs/QTGraphVisualization/MatrixEditor.h)
        add_qt_lab(QTBSTVisualization sem2/manual_3_grapgs/QTBSTVisualization
                sem2/manual_3_grapgs/QTBSTVisualization/main.cpp
                sem2/manual_3_grapgs/QTBSTVisualization/MainWindow.cpp
                sem2/manual_3_grapgs/QTBSTVisualization/MainWindow.h
                sem2/manual_3_grapgs/QTBSTVisualization/BST.cpp
                sem2/manual_3_grapgs/QTBSTVisualization/BST.h
                sem2/manual_3_grapgs/QTBSTVisualization/UiVertex.cpp
                sem2/manual_3_grapgs/QTBSTVisualization/UiVertex.h
                sem2/manual_3_grapgs/QTBSTVisualization/GraphWorker.cpp
                sem2/manual_3_grapgs/QTBSTVisualization/GraphWorker.h)
        add_qt_lab(QTBNBVisualization sem2/manual_3_grapgs/QTBNBVisualization
                sem2/manual_3_grapgs/QTBNBVisualization/main.cpp
                sem2/manual_3_grapgs/QTBNBVisualization/MainWindow.cpp
                sem2/manual_3_grapgs/QTBNBVisualization/MainWindow.h
                sem2/manual_3_grapgs/QTBNBVisualization/Graph.cpp
                sem2/manual_3_grapgs/QTBNBVisualization/Graph.h
                sem2/manual_3_grapgs/QTBNBVisualization/UiVertex.cpp
                sem2/manual_3_grapgs/QTBNBVisualization/UiVertex.h
                sem2/manual_3_grapgs/QTBNBVisualization/UiEdge.cpp
                sem2/manual_3_grapgs/QTBNBVisualization/UiEdge.h
                sem2/manual_3_grapgs/QTBNBVisualization/GraphWorker.cpp
                sem2/manual_3_grapgs/QTBNBVisualization/GraphWorker.h
                sem2/manual_3_grapgs/QTBNBVisualization/MatrixEditor.cpp
                sem2/manual_3_grapgs/QTBNBVisualization/MatrixEditor.h)
    else()
        message(STATUS "Qt6 was not found: Qt visualization targets are skipped.")
        message(STATUS "Set CMAKE_PREFIX_PATH to your Qt installation to enable them.")
    endif()
endif()
