TEMPLATE = app

QT += qml quick pdf widgets svg

SOURCES += main.cpp

RESOURCES += \
    viewer.qrc
EXAMPLE_FILES = \
    viewer.qml

target.path = $$[QT_INSTALL_EXAMPLES]/pdf/multipage
INSTALLS += target

