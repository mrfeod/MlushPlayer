#-------------------------------------------------
#
# Project created by QtCreator 2015-09-21T21:23:18
#
#-------------------------------------------------

#You need to declare config.pro file. Use config.pro_in as template.
include(config.pro)

CONFIG += c++11

QT += core gui webkitwidgets multimedia widgets

TARGET = MlushPlayer
TEMPLATE = app

SOURCES += main.cpp\
	mainwindow.cpp \
	VkManager/VkManager.cpp \
	VkManager/VkOAuthView.cpp \
	MlushApplication.cpp \
	PlaylistController.cpp \
	Player/PlayerForm.cpp \
	Player/ControlPanel.cpp \
	ObjectsConnector/ObjectsConnector.cpp \
	Player/playlistitemwidget.cpp \
    VkManager/VkCookieJar.cpp

HEADERS  += mainwindow.h \
	VkManager/VkManager.h \
	VkManager/VkOAuthView.h \
	MlushApplication.h \
	PlaylistController.h \
	Player/PlayerForm.h \
	Player/ControlPanel.h \
	ObjectsConnector/ObjectsConnector.h \
	ObjectsConnector/MlushConnectorID.h \
	Player/playlistitemwidget.h \
	Player/playlistitemdata.h \
    VkManager/VkCookieJar.h

FORMS    += mainwindow.ui \
	Player/PlayerForm.ui \
	Player/ControlPanel.ui \
	Player/playlistitemwidget.ui

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
