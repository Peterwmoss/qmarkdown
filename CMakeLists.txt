cmake_minimum_required(VERSION 3.1.0)

project(qmarkdown)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Try to use Qt6 libraries by default
find_package(Qt6 COMPONENTS Core Widgets WebEngineCore WebEngineWidgets WebChannel Gui)
if (NOT Qt6_FOUND)
    # Otherwise use Qt5.15+ ones
    find_package(Qt5 5.15 REQUIRED COMPONENTS Core Widgets WebEngineCore WebEngineWidgets WebChannel Gui)
endif()

set(CMAKE_CXX_FLAGS "-O3 -Wall -Wextra")

add_executable(qmarkdown
    src/resgen.cpp
    src/fileinput.cpp
    src/webpage.cpp
    src/document.cpp
    src/mainwindow.cpp
    src/main.cpp
    src/resources/resources.qrc
)

target_link_libraries(qmarkdown Qt::Core Qt::Widgets Qt::WebEngineCore Qt::WebEngineWidgets Qt::WebChannel Qt::Gui stdc++fs)

install(TARGETS qmarkdown DESTINATION ${DESTDIR}${PREFIX}/usr/bin)
