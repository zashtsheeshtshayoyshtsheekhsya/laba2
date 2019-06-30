#include "common.h"
#include "text/text.h"
#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

static void remove_first_line(int index, char *contents, int cursor,
                              void *data);

static int flag = 1;

void rh(text txt) {
  flag = 1;
  process_forward(txt, remove_first_line, txt);
}

static void remove_first_line(int index, char *contents, int cursor,
                              void *data) {
  assert(contents != NULL);
  UNUSED(index);
  UNUSED(cursor);

  if (flag == 1) {
    delete_line(data, 1);
  }

  flag = 0;
}
