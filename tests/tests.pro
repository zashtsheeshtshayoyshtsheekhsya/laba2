include(gtest_dependency.pri)

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG += thread
CONFIG -= qt

HEADERS += \
        tst_test.h \
    ../app/data.h \
    ../app/common.h \
    ../app/text/_text.h \
    ../app/text/text.h

SOURCES += \
        main.cpp \
    ../app/show.c \
    ../app/save.c \
    ../app/rh.c \
    ../app/rc.c \
    ../app/mwbb.c \
    ../app/mpweb.c \
    ../app/mle.c \
    ../app/m.c \
    ../app/load.c \
    ../app/getcrsr.c \
    ../app/text/append_line.c \
    ../app/text/change_cursor_position.c \
    ../app/text/create_text.c \
    ../app/text/delete_line.c \
    ../app/text/process_forward.c \
    ../app/text/remove_all.c

DISTFILES += \
    ../app/showrew.o \
    ../app/showrev.o \
    ../app/mwef.o \
    ../app/text/libtext.a

QMAKE_CXXFLAGS += -std=c++0x

# gcov
QMAKE_CXXFLAGS += -fprofile-arcs -ftest-coverage
QMAKE_CFLAGS += -fprofile-arcs -ftest-coverage
LIBS += -lgcov
