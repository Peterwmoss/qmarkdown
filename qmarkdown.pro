TEMPLATE = app

QT += webenginewidgets webchannel

HEADERS += \
    mainwindow.h \
    document.h \

SOURCES = \
    main.cpp \
    mainwindow.cpp \
    document.cpp \

RESOURCES = \
    resources/qmarkdown.qrc

# Disable Qt Quick compiler because the example doesn't use QML, but more importantly so that
# the source code of the .js files is not removed from the embedded qrc file.
CONFIG -= qtquickcompiler

DISTFILES += \
    resources/3rdparty/MARKDOWN-LICENSE.txt \
    resources/3rdparty/MARKED-LICENSE.txt

# install
target.path = /usr/bin/qmarkdown
INSTALLS += target
