QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cc \
    model/grotto.cc \
    view/cave.cc \
    view/mainwindow.cc \
    view/render_area.cc \
    model/maze.cc \
    model/throughmaze.cc \
    view/tangle.cc



HEADERS += \
        model/grotto.h \
        view/cave.h \
        view/mainwindow.h \
        view/render_area.h \
        model/maze.h \
        model/throughmaze.h \
        view/tangle.h



FORMS += \
    view/cave.ui \
    view/mainwindow.ui \
    view/tangle.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES +=
