// search_core.h
#ifndef SEARCH_CORE_H                          // Защита от повторного включения файла
#define SEARCH_CORE_H

#include "structures.h"                        // Подключаем структуры Car и Registration
#include <cstdio>                              // Для FILE* и fprintf

// Пространство имён для общих функций поиска и вывода
namespace SearchCore {

    // Выводит одну полную запись на экран (режим поиска)
    void print_record_screen(const Car& car, const Registration& reg);

    // Записывает одну полную запись в файл result.txt
    // Принимает указатели, потому что запись может быть неполной (машина или регистрация может отсутствовать)
    void print_record_file(FILE* f, const Car* car, const Registration* reg);

    // Проверяет, подходит ли текущая запись под запрос пользователя
    // Возвращает true, если совпадение найдено
    bool field_matches(const Car& car, const Registration& reg, int field, const char* query);

} // namespace SearchCore

#endif