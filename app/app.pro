TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    save.c \
    m.c \
    load.c \
    editor.c \
    text/append_line.c \
    text/create_text.c \
    text/delete_line.c \
    text/process_forward.c \
    text/remove_all.c \
    show.c \
    mpweb.c \
    getcrsr.c \
    text/change_cursor_position.c \
    mwbb.c \
    mle.c \
    rc.c \
    rh.c

HEADERS += \
    data.h \
    common.h \
    text/_text.h \
    text/text.h

# gcov
QMAKE_CFLAGS += -fprofile-arcs -ftest-coverage
LIBS += -lgcov
