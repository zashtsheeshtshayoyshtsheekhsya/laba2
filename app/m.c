#include "common.h"

void change_cursor_position(text txt, int new_line, int new_position);

/* функция ставящая курсор в нужную позицию (строчка, позиция курсора) */
 
void m(text txt, int line, int cursor)
{
  change_cursor_position(txt, line, cursor);
}
