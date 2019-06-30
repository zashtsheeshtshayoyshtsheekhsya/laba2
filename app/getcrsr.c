#include "common.h"
#include "data.h"
#include "text/text.h"
#include <assert.h>
#include <ctype.h>
#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>

static void get_cursor_position(int index, char *contents, int cursor,
                                void *data);

void getcrsr(text txt) { process_forward(txt, get_cursor_position, NULL); }

static void get_cursor_position(int index, char *contents, int cursor,
                                void *data) {
  assert(contents != NULL);
  UNUSED(data);
  if (cursor >= 0) {
    printf("cursor line - %d\ncursor position -  %d\n", index + 1, cursor + 1);
  }
}
