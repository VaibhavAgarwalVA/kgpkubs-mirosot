# -------------------------------------------------
# Project created by QtCreator 2009-11-18T18:56:10
# -------------------------------------------------
QT += network \
    opengl
TARGET = grSim
TEMPLATE = app
SOURCES += main.cpp \
    mainwindow.cpp \
    glwidget.cpp \
    Graphics/graphics.cpp \
    Physics/pworld.cpp \
    Physics/pobject.cpp \
    Physics/pball.cpp \
    Physics/pground.cpp \
    sslworld.cpp \
    Physics/pfixedbox.cpp \
    Physics/pcylinder.cpp \
    robot.cpp \
    Physics/pbox.cpp \
    proto/netraw.cpp \
    proto/robocup_ssl_server.cpp \
    proto/messages_robocup_ssl_wrapper.pb.cc \
    proto/messages_robocup_ssl_refbox_log.pb.cc \
    proto/messages_robocup_ssl_geometry.pb.cc \
    proto/messages_robocup_ssl_detection.pb.cc \
    Physics/pray.cpp \
    configwidget.cpp \
    statuswidget.cpp \
    logger.cpp \
    robotwidget.cpp \
    getpositionwidget.cpp \
    proto/grSim_Replacement.pb.cc \
    proto/grSim_Commands.pb.cc \
    proto/grSim_Packet.pb.cc \
    proto/sslDebug_Data.pb.cc \
    graphicaldebugger.cpp
HEADERS += mainwindow.h \
    glwidget.h \
    Graphics/graphics.h \
    Physics/pworld.h \
    Physics/pobject.h \
    Physics/pball.h \
    Physics/pground.h \
    sslworld.h \
    Physics/pfixedbox.h \
    Physics/pcylinder.h \
    robot.h \
    Physics/pbox.h \
    proto/netraw.h \
    proto/robocup_ssl_server.h \
    proto/messages_robocup_ssl_refbox_log.pb.h \
    proto/messages_robocup_ssl_geometry.pb.h \
    proto/messages_robocup_ssl_detection.pb.h \
    proto/messages_robocup_ssl_wrapper.pb.h \
    Physics/pray.h \
    configwidget.h \
    statuswidget.h \
    logger.h \
    robotwidget.h \
    getpositionwidget.h \
    proto/grSim_Replacement.pb.h \
    proto/grSim_Commands.pb.h \
    proto/grSim_Packet.pb.h \
    graphicaldebugger.h \
    proto/sslDebug_Data.pb.h
LIBS += -L$$PWD/libs/ \
    -lode \
    -lprotobuf \
    -lVarTypes
MOC_DIR = $$PWD/objs
OBJECTS_DIR = $$PWD/objs
DESTDIR = $$PWD/bin
INCLUDEPATH += $$PWD/include
INCLUDEPATH += $$PWD/include/VarTypes
RESOURCES += textures.qrc
QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_RELEASE += -O3
QMAKE_CFLAGS_RELEASE -= -O2
QMAKE_CFLAGS_RELEASE += -O3
