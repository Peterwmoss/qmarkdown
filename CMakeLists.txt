cmake_minimum_required(VERSION 3.1.0)

project(qmarkdown)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Multithreading
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

# Qt5 libraries
find_package(Qt6Core REQUIRED)
find_package(Qt6Widgets REQUIRED)
find_package(Qt6WebEngineCore REQUIRED)
find_package(Qt6WebEngineWidgets REQUIRED)
find_package(Qt6WebChannel REQUIRED)
find_package(Qt6Gui REQUIRED)

set(CMAKE_CXX_FLAGS "-O3 -Wall -Wextra")

add_executable(qmarkdown
    src/helpers.cpp
    src/resgen.cpp
    src/fileinput.cpp
    src/webpage.cpp
    src/document.cpp
    src/mainwindow.cpp
    src/main.cpp
    src/resources/resources.qrc
)

target_link_libraries(qmarkdown Qt::Widgets Qt::Core Qt::WebEngineCore Qt::WebEngineWidgets Qt::WebChannel Qt::Gui stdc++fs Threads::Threads)

install(TARGETS qmarkdown DESTINATION ${DESTDIR}${PREFIX}/usr/bin)
