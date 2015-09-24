#-------------------------------------------------
#
# Project created by QtCreator 2015-09-21T21:23:18
#
#-------------------------------------------------

#You need to declare config.pro file. Use config.pro_in as template.
include(config.pro)

CONFIG += c++11

QT       += core gui webkitwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MlushPlayer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    VkManager/VkManager.cpp \
    VkManager/VkOAuthView.cpp \
    MlushApplication.cpp

HEADERS  += mainwindow.h \
    VkManager/VkManager.h \
    VkManager/VkOAuthView.h \
    MlushApplication.h

FORMS    += mainwindow.ui

CONFIG( debug, debug|release ) {
    # debug
    DEPLOY_TARGET = $$shell_quote($$shell_path($${OUT_PWD}/debug/MlushPlayer.exe))
    BIN_DIR = $$shell_path($${OUT_PWD}/debug)
} else {
    # release
    DEPLOY_TARGET = $$shell_quote($$shell_path($${OUT_PWD}/release/MlushPlayer.exe))
    BIN_DIR = $$shell_path($${OUT_PWD}/release)
}

#QMAKE_POST_LINK = windeployqt $${DEPLOY_TARGET} && copy D:\Development\SDK\SSL\mingw491_32\*.dll $${BIN_DIR}
QMAKE_POST_LINK = copy D:\Development\SDK\SSL\mingw491_32\*.dll $${BIN_DIR}