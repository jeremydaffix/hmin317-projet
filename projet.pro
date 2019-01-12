QT       += core gui widgets

TARGET = projet
TEMPLATE = app

INCLUDEPATH += src/
INCLUDEPATH += /usr/include/boost/
INCLUDEPATH += /usr/include/freetype2/

SOURCES += \
    src/engine/component.cpp \
    src/engine/cube.cpp \
    src/engine/gameobject.cpp \
    src/engine/gamescene.cpp \
    src/game/main.cpp \
    src/engine/mainwidget.cpp \
    src/engine/model3d.cpp \
    src/engine/objet3d.cpp \
    src/engine/plane.cpp \
    src/engine/sprite.cpp \
    src/engine/terrain.cpp \
    src/engine/resourcesmanager.cpp \
    src/engine/movingballcomponent.cpp \
    src/engine/game.cpp \
    src/engine/spriteanimationcomponent.cpp \
    src/game/imaginawars.cpp \
    src/game/gamemap.cpp \
    src/3rd/pathfinders.cpp \
    src/game/walkpathfindingcomponent.cpp \
    src/game/effectspritecomponent.cpp \
    src/game/soldier.cpp \
    src/game/buildingcomponent.cpp \
    src/game/gameplayer.cpp \
    src/game/humanplayercomponent.cpp \
    src/game/debugcomponent.cpp \
    src/game/lifecomponent.cpp

SOURCES +=

HEADERS += \
    src/engine/component.h \
    src/engine/cube.h \
    src/engine/gameobject.h \
    src/engine/gamescene.h \
    src/engine/mainwidget.h \
    src/engine/model3d.h \
    src/engine/objet3d.h \
    src/engine/plane.h \
    src/engine/sprite.h \
    src/engine/terrain.h \
    src/engine/resourcesmanager.h \
    src/engine/movingballcomponent.h \
    src/engine/game.h \
    src/engine/spriteanimationcomponent.h \
    src/game/imaginawars.h \
    src/game/gamemap.h \
    src/3rd/pathfinders.h \
    src/game/walkpathfindingcomponent.h \
    src/game/effectspritecomponent.h \
    src/game/soldier.h \
    src/game/buildingcomponent.h \
    src/game/gameplayer.h \
    src/game/humanplayercomponent.h \
    src/game/debugcomponent.h \
    src/game/lifecomponent.h

RESOURCES += \
    textures.qrc \
    shaders.qrc \
    game.qrc \
    fonts.qrc

LIBS += -lboost_system -lboost_random

# install
target.path = $$[QT_INSTALL_EXAMPLES]/opengl/projet
INSTALLS += target

DISTFILES +=

CONFIG += resources_big

FORMS +=
