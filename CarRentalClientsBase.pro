ROOT_DIR = $${PWD}

QT += quick

TARGET = CarRentalClientsBase

CONFIG += c++11

DESTDIR = $${ROOT_DIR}
CONFIG -= debug_and_release debug_and_release_target

include(CarRentalClientsBase.pri)

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

MOC_DIR = $${ROOT_DIR}/build-$${QT_VERSION}/$${TARGET}
OBJECTS_DIR = $${ROOT_DIR}/build-$${QT_VERSION}/$${TARGET}
UI_DIR = $${ROOT_DIR}/build-$${QT_VERSION}/$${TARGET}


