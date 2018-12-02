TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp

INCLUDEPATH += E:/develop/opencv343/build/include
               E:/develop/opencv343/build/include/opencv
               E:/develop/opencv343/build/include/opencv2
               E:/develop/opencv343/build/x64/vc14/bin

CONFIG(debug, debug|release): {
LIBS += -LE:/develop/opencv343/build/x64/vc14/lib \
-lopencv_world343d \

} else:CONFIG(release, debug|release): {
LIBS += -LE:/develop/opencv343/build/x64/vc14/lib \
-lopencv_world343 \
}
