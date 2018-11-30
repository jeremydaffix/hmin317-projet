QT       += core gui widgets

TARGET = projet
TEMPLATE = app

INCLUDEPATH += src/

SOURCES += \
    src/calendar.cpp \
    src/component.cpp \
    src/cube.cpp \
    src/gameobject.cpp \
    src/gamescene.cpp \
    src/gridmainwidget.cpp \
    src/main.cpp \
    src/mainwidget.cpp \
    src/model3d.cpp \
    src/movingcubecomponent.cpp \
    src/objet3d.cpp \
    src/plane.cpp \
    src/sprite.cpp \
    src/terrain.cpp

SOURCES +=

HEADERS += \
    src/calendar.h \
    src/component.h \
    src/cube.h \
    src/gameobject.h \
    src/gamescene.h \
    src/gridmainwidget.h \
    src/mainwidget.h \
    src/model3d.h \
    src/movingcubecomponent.h \
    src/objet3d.h \
    src/plane.h \
    src/sprite.h \
    src/terrain.h

RESOURCES += \
    textures.qrc \
    shaders.qrc

# install
target.path = $$[QT_INSTALL_EXAMPLES]/opengl/projet
INSTALLS += target

DISTFILES +=

CONFIG += resources_big

FORMS +=
