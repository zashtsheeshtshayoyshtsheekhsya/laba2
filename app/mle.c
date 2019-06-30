#include "common.h"
#include "text/text.h"
#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

static void mlee(int index, char *contents, int cursor, void *data);

/**
 * Переводит курсор в конец текущей строки
 */
void mle(text txt) {
    /* Применяем функцию mle к каждой строке текста */
    process_forward(txt, mlee, txt);
}

static void mlee(int index, char *contents, int cursor, void *data) {
    assert(contents != NULL);

    UNUSED(index);
    UNUSED(cursor);
    UNUSED(data);

    if (cursor != -1) {
        m((text)data, index + 1, (int)strlen(contents));
    }
}
