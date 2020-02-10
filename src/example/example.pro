TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c

HEADERS += \
    ../include/vXc.h


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../lib/release/ -lcosmos
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../lib/debug/ -lcosmos
else:unix: LIBS += -L$$PWD/../lib/ -lcosmos

INCLUDEPATH += $$PWD/../include
DEPENDPATH += $$PWD/../include

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../lib/release/libcosmos.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../lib/debug/libcosmos.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../lib/release/cosmos.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../lib/debug/cosmos.lib
else:unix: PRE_TARGETDEPS += $$PWD/../lib/libcosmos.a
