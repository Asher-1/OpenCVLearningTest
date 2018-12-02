TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp

INCLUDEPATH += D:/develop/tools/opencv343/build/include
               D:/develop/tools/opencv343/build/include/opencv
               D:/develop/tools/opencv343/build/include/opencv2
               D:/develop/tools/opencv343/build/x64/vc14/bin

CONFIG(debug, debug|release): {
LIBS += -LD:/develop/tools/opencv343/build/x64/vc14/lib \
-lopencv_world343d \

} else:CONFIG(release, debug|release): {
LIBS += -LD:/develop/tools/opencv343/build/x64/vc14/lib \
-lopencv_world343 \
}

HEADERS += \
    plot.h
