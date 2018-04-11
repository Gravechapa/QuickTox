QT += quick core
CONFIG += c++14
SOURCE_DIR = $$PWD/src

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES +=  $$SOURCE_DIR/main.cpp \
            $$SOURCE_DIR/controllers/*.cpp \
            $$SOURCE_DIR/core/*.cpp

HEADERS +=  $$SOURCE_DIR/controllers/*.h \
            $$SOURCE_DIR/core/*.h \
            $$SOURCE_DIR/configs/*.h

RESOURCES += $$SOURCE_DIR/qml/qml.qrc \
             $$PWD/resources/resources.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

android: LIBS += -L$$PWD/prebuild_libs/Android/$${ANDROID_TARGET_ARCH}/
win32: LIBS += -L$$PWD/prebuild_libs/Windows
LIBS += -ltoxcore -lsodium
android: INCLUDEPATH += $$PWD/prebuild_libs/include
android: DEPENDPATH += $$PWD/prebuild_libs/include
win32: INCLUDEPATH += $$PWD/prebuild_libs/include
win32: DEPENDPATH += $$PWD/prebuild_libs/include

android: ANDROID_EXTRA_LIBS = \
        $$PWD/prebuild_libs/Android/$${ANDROID_TARGET_ARCH}/libtoxcore.so\
        $$PWD/prebuild_libs/Android/$${ANDROID_TARGET_ARCH}/libsodium.so
