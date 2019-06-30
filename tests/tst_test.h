#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

extern "C" {
    #include "../app/text/_text.h"
    #include "../app/text/text.h"
    #include "../app/common.h"
}

using namespace testing;

static void f(int index, char *contents, int cursor, void *data);

static void f(int index, char *contents, int cursor, void *data) {
    UNUSED(index);
    UNUSED(cursor);
    UNUSED(data);

    assert(contents != NULL);
}

/**
 * Попытка открыть несуществующий файл
 */
TEST(t1, tests)
{
    text txt = create_text();
    load(txt, "<filename>");

    EXPECT_EQ(txt->length, 0);
}

/**
 * Попытка открыть файл, для которого недостаточно прав
 */
TEST(t2, tests)
{
    text txt = create_text();
    load(txt, "/etc/shadow");

    EXPECT_EQ(txt->length, 0);
}

/**
 * Выводим текст на экран
 */
TEST(t3, tests)
{
    text txt = create_text();
    load(txt, "input.txt");
    show(txt);

    EXPECT_EQ(txt->cursor->position, 5);
}


/**
 * Удаляем все из файла
 */
TEST(t4, tests)
{
    text txt = create_text();
    load(txt, "input.txt");
    remove_all(txt);

    EXPECT_NE(txt, nullptr);
    EXPECT_EQ(txt->length, 0);
}

/**
 * Попытка удалить все, если файл не открыт
 */
TEST(t5, tests)
{
    text txt = nullptr;
    remove_all(txt);

    EXPECT_EQ(txt, nullptr);
}

/**
 * Перемещаем курсор в конец данной строки
 */
TEST(t6, tests)
{
    text txt = create_text();
    load(txt, "input.txt");
    mle(txt);

    EXPECT_EQ(txt->cursor->position, 4);
}

/**
 * Перемещаем курсор в начало текущего слова
 */
TEST(t7, tests)
{
    text txt = create_text();
    load(txt, "input.txt");
    mwbb(txt);

    EXPECT_EQ(txt->cursor->position, 0);
}

/**
 * Добавляем строку к тексту
 */
TEST(t8, tests)
{
    text txt = create_text();
    const char* contents = "TEST";
    load(txt, "input.txt");

    EXPECT_NO_FATAL_FAILURE(append_line(txt, contents););
    EXPECT_NE(txt->length, 0);
}

/**
 * Попытка добавить к тексту слишком длинную строку
 */
TEST(t9, tests)
{
    text txt = create_text();
    char contents[10000];
    load(txt, "input.txt");
    for (; strlen(contents) < 10000; strcat(contents, "TEST"));

    EXPECT_EXIT(append_line(txt, contents), ::testing::ExitedWithCode(EXIT_FAILURE), "");
}

/**
 * Перемещаем курсор в указанную позицию
 */
TEST(t10, tests)
{
    text txt = create_text();
    load(txt, "input.txt");
    m(txt, 0, 2);

    EXPECT_EQ(txt->cursor->position, 1);
}

/**
 * Попытка переместить курсор в позицию с отрицательными координатами
 */
TEST(t11, tests)
{
    text txt = create_text();
    load(txt, "input.txt");
    m(txt, -1, -1);

    EXPECT_EQ(txt->cursor->position, 0);
}

/**
 * Попытка вывести текст на экран, если файл не открыт
 */
TEST(t12, tests)
{
    text txt = create_text();
    show(txt);

    EXPECT_EQ(txt->cursor->position, 0);
}

/**
 * Сохраняем текст в файл
 */
TEST(t13, tests)
{
    text txt = create_text();
    load(txt, "input.txt");

    EXPECT_NE(txt->length, 0);
    save(txt, "test.txt");
    EXPECT_NE(fopen("test.txt", "r"), nullptr);
}

/**
 *  Перемещаем курсор в конец предыдущего слова
 */
TEST(t14, tests) {
    text txt = create_text();
    load(txt, "input.txt");

    mpweb(txt);
    EXPECT_NO_FATAL_FAILURE(process_forward(txt, f, NULL));
}

/**
 * Удаляем текущую строку
 */
TEST(t15, tests) {
    text txt = create_text();
    load(txt, "input.txt");

    rc(txt);
    EXPECT_EQ(txt->cursor->position, 5);
}

/**
 * Удаляем первую строку
 */
TEST(t16, tests) {
    text txt = create_text();
    load(txt, "input.txt");

    rh(txt);
    EXPECT_EQ(txt->length, 0);
}

/**
 * Удаляем текущую строку, установив курсор
 */
TEST(t17, tests) {
    text txt = create_text();
    load(txt, "input.txt");

    m(txt, 0, 0);
    rc(txt);
    EXPECT_EQ(txt->length, 0);
}

/**
 * Попытка переместить курсор в начало слова, если курсор на позиции вне текста
 */
TEST(t18, tests) {
    text txt = create_text();
    load(txt, "input.txt");

    m(txt, 3, 5);
    mpweb(txt);
    EXPECT_EQ(txt->cursor->position, 4);
}

/**
 * Получаем позицию курсора
 */
TEST(t19, tests) {
    text txt = create_text();
    load(txt, "input.txt");

    m(txt, 0, 0);
    getcrsr(txt);
    EXPECT_EQ(txt->cursor->position, 0);
}

/**
 * Попытка получить позицию курсора, если его позиция вне текста
 */
TEST(t20, tests) {
    text txt = create_text();
    load(txt, "input.txt");

    m(txt, 5, 5);
    getcrsr(txt);
    EXPECT_EQ(txt->cursor->position, 4);
}

/**
 * Попытка получить позицию курсора, если файл не открыт
 */
TEST(t21, tests) {
    text txt = nullptr;
    EXPECT_NO_FATAL_FAILURE(getcrsr(txt));
}

/**
 * Удаляем первую строку из текста
 */
TEST(t22, tests) {
    text txt = create_text();
    load(txt, "long.txt");

    m(txt, 0, 0);
    delete_line(txt, 1);
    EXPECT_EQ(txt->length, 2);
}

/**
 * Попытка удалить строку из текста, если ее номер вне текста
 */
TEST(t23, tests) {
    text txt = create_text();
    load(txt, "long.txt");

    m(txt, 1, 1);
    EXPECT_DEATH(delete_line(txt, 5), "");
}

/**
 * Удаляем последнюю строку из текста
 */
TEST(t24, tests) {
    text txt = create_text();
    load(txt, "long.txt");

    m(txt, 1, 1);
    delete_line(txt, 3);
    EXPECT_EQ(txt->length, 2);
}

/**
 * Удаляем заданную строку из текста
 */
TEST(t25, tests) {
    text txt = create_text();
    load(txt, "long.txt");

    m(txt, 1, 1);
    delete_line(txt, 2);
    EXPECT_EQ(txt->length, 2);
}
