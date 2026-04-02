// search_by_field.cpp
#define _CRT_SECURE_NO_WARNINGS

#include "search_by_field.h"                        // Подключаем свой заголовок
#include "search_core.h"                            // Подключаем общие функции печати и сравнения
#include "texts.h"                                  // Подключаем тексты
#include "debug.h"                                  // Подключаем отладку
#include "constants.h"                              // Подключаем константы размеров
#include <vector>                                   // Для std::vector
#include <cstdio>                                   // Для printf
#include <cstring>                                  // Для strlen

namespace SearchByField {

    void execute(const std::vector<Car>& cars, const std::vector<Registration>& regs) {
        if (Debug::ENABLE_DEBUG) printf(Debug::DBG_MODE_SELECTED, 1); // Отладка: выбран режим поиска

        printf("%s", Text::MSG_SEARCH_FIELD);       // Показываем меню выбора поля
        int field = 0;
        scanf("%d", &field);                        // Считываем номер поля
        getchar();                                  // Очищаем буфер после ввода числа

        char query[MAX_QUERY] = { 0 };                // Буфер для поискового запроса
        printf("%s", Text::MSG_ENTER_QUERY);        // Просим ввести запрос
        fgets(query, sizeof(query), stdin);         // Считываем строку (включая пробелы)
        query[strcspn(query, "\n")] = '\0';         // Убираем символ новой строки

        if (strlen(query) == 0) {                   // Если пользователь ничего не ввёл
            printf("%s", Text::MSG_NO_DATA);
            return;
        }

        if (Debug::ENABLE_DEBUG) printf(Debug::DBG_SEARCH_START, field, query); // Отладка

        bool found = false;                         // Флаг: найдено ли хоть одно совпадение
        printf("%s", Text::MSG_SEARCH_HEADER);      // Заголовок результатов поиска

        for (const auto& reg : regs) {              // Перебираем все регистрации
            for (const auto& car : cars) {          // Для каждой регистрации ищем машину
                if (car.id != reg.id) continue;     // Если ID не совпадает — пропускаем

                if (SearchCore::field_matches(car, reg, field, query)) { // Проверяем совпадение
                    if (Debug::ENABLE_DEBUG) printf(Debug::DBG_RECORD_FOUND, reg.id);
                    SearchCore::print_record_screen(car, reg); // Выводим запись на экран
                    found = true;
                    break;                          // Выходим из внутреннего цикла
                }
            }
        }

        if (!found) {                               // Если ничего не нашли
            if (Debug::ENABLE_DEBUG) printf("%s", Debug::DBG_NO_MATCH);
            printf("%s", Text::MSG_NO_DATA);
        }
    }

} // namespace SearchByField