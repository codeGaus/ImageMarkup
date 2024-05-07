cmake_minimum_required(VERSION 3.5)

set(project_name ImageMarkup)

project(${project_name} VERSION 1.0 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

set(PROJECT_SOURCES
        imagemarkupwidget.h
        imagemarkupwidget.cpp
        mainwindow.h
        mainwindow.cpp
        imagemarkupwidget.ui
        main.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(${project_name}
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )

else()
        add_executable(${project_name}
            ${PROJECT_SOURCES}
        )
endif()

target_link_libraries(${project_name} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

install(TARGETS ${project_name} DESTINATION bin)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(ImageMarkup)
endif()
