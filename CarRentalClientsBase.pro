ROOT_DIR = $${PWD}

QT += quick

TARGET = app

CONFIG += c++11

DESTDIR = $${ROOT_DIR}/build-$${QT_VERSION}/$${TARGET}
CONFIG -= debug_and_release debug_and_release_target

include(CarRentalClientsBase.pri)

MOC_DIR = $${ROOT_DIR}/build-$${QT_VERSION}/$${TARGET}
OBJECTS_DIR = $${ROOT_DIR}/build-$${QT_VERSION}/$${TARGET}
UI_DIR = $${ROOT_DIR}/build-$${QT_VERSION}/$${TARGET}


