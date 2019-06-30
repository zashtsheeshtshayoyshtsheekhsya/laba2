/**
 * editor.c -- строковый текстовый редактор
 *
 * Copyright (c) 2017, Alexander Borodin <aborod@petrsu.ru>
 *
 * This code is licensed under a MIT-style license.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "text/text.h"

#define MAXLINE 255

int main() {
  char cmdline[MAXLINE + 1];
  char *cmd;
  char *arg;

  /* Создаем объект для представления текста */
  text txt = create_text();

  /* Цикл обработки команд */
  while (1) {
    printf("ed > ");

    /* Получаем команду */
    fgets(cmdline, MAXLINE, stdin);

    /* Извлекаем имя команды */
    if ((cmd = strtok(cmdline, " \n")) == NULL) {
      continue;
    }
    /* Распознаем поддерживаемую команду */

    /* Завершаем работу редактора */
    if (strcmp(cmd, "quit") == 0) {
      fprintf(stderr, "Bye!\n");
      break;
    }

    /* Загружаем содержимое файла, заданного параметром */
    if (strcmp(cmd, "load") == 0) {
      if ((arg = strtok(NULL, " \n")) == NULL) {
        fprintf(stderr, "Usage: load filename\n");
      } else
        load(txt, arg);
      continue;
    }

    /* Сохраняем текст в указанный файл */
    if (strcmp(cmd, "save") == 0) {
      if ((arg = strtok(NULL, " \n")) == NULL) {
        fprintf(stderr, "Usage: save filename\n");
      } else {
        save(txt, arg);
      }
      continue;
    }

    /* Удаляем текущую строку */
    if (strcmp(cmd, "rc") == 0) {
        rc(txt);
        continue;
    }

    /* Удаляем первую строку */
    if (strcmp(cmd, "rh") == 0) {
        rh(txt);
        continue;
    }

    /* Выводим текст */
    if (strcmp(cmd, "show") == 0) {
      show(txt);
      continue;
    }

    /* Перемещаем курсор в конец предыдущего слова, если это возможно */
    if (strcmp(cmd, "mpweb") == 0) {
        mpweb(txt);
        continue;
    }

    /* Перемещаем курсор в начало слова */
    if (strcmp(cmd, "mwbb") == 0) {
        mwbb(txt);
        continue;
    }

    if (strcmp(cmd, "getcrsr") == 0) {
        getcrsr(txt);
        continue;
    }

    /* Меняем позицию курсора на заданную */
    if (strcmp(cmd, "m") == 0) {
        char *line = strtok(NULL, " \n"), *position = strtok(NULL, " \n");
        if (line && position)
            m(txt, atoi(line), atoi(position));
        else
            printf("Usage: mwcrsr line position\n");
        continue;
    }

    /* Если команда не известна */
    fprintf(stderr, "Unknown command: %s\n", cmd);
  }

  return 0;
}
