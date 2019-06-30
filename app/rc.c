#include "common.h"
#include "text/text.h"
#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

static void remove_line(int index, char *contents, int cursor, void *data);

/**
 * Удаляет текущую строку
 */
static int flag = 1;
void rc(text txt) {
  flag = 1;
  process_forward(txt, remove_line, txt);
}

static void remove_line(int index, char *contents, int cursor, void *data) {
  assert(contents != NULL);

  if (cursor >= 0 && flag) {
    delete_line(data, index + 1);
    flag = 0;
  }
}
