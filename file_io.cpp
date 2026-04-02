// file_io.cpp
#define _CRT_SECURE_NO_WARNINGS                     // Отключает предупреждения о небезопасных функциях

#include "file_io.h"                                // Подключаем свой заголовок
#include "constants.h"                              // Подключаем константы размеров
#include "texts.h"                                  // Подключаем все текстовые сообщения
#include "debug.h"                                  // Подключаем отладочные сообщения
#include <vector>                                   // Для std::vector
#include <cstdio>                                   // Для fopen, printf, fclose
#include <cstring>                                  // Для strtok, strncpy, strlen

namespace FileIO {                                  // Все функции работы с файлами

    namespace {                                     // Анонимный namespace — функции видны только в этом файле

        // Удаляет символы новой строки из конца строки
        void clean_line(char* line) {
            line[strcspn(line, "\n\r")] = '\0';     // Находим первый \n или \r и заменяем на \0
        }

        // Разбирает одну строку из файла cars.txt
        bool parse_car(const char* line, Car& car) {
            char temp[MAX_LINE];                    // Временный буфер для строки
            strncpy(temp, line, MAX_LINE - 1);        // Копируем строку с защитой от переполнения
            temp[MAX_LINE - 1] = '\0';                // Гарантируем завершение строки

            char* t = strtok(temp, ";");            // Разделяем строку по символу ';'
            if (!t) return false;                   // Если не удалось — ошибка
            car.id = atoi(t);                       // Первый токен — ID

            if ((t = strtok(nullptr, ";"))) car.plate = t;  // Второй токен — номерной знак
            if ((t = strtok(nullptr, ";"))) car.brand = t;  // Третий токен — марка
            if ((t = strtok(nullptr, ";"))) car.model = t;  // Четвёртый токен — модель

            return true;                            // Успешно разобрали
        }

        // Разбирает одну строку из файла regs.txt
        bool parse_reg(const char* line, Registration& reg) {
            char temp[MAX_LINE];
            strncpy(temp, line, MAX_LINE - 1);
            temp[MAX_LINE - 1] = '\0';

            char* t = strtok(temp, ";");
            if (!t) return false;
            reg.id = atoi(t);

            if ((t = strtok(nullptr, ";"))) reg.fio = t;         // ФИО
            if ((t = strtok(nullptr, ";"))) reg.plate = t;       // Номерной знак
            if ((t = strtok(nullptr, ";"))) reg.address = t;     // Адрес
            if ((t = strtok(nullptr, ";"))) reg.reg_year = atoi(t); // Год

            return true;
        }
    } // конец анонимного namespace

    // Загрузка автомобилей из файла
    bool load_cars(const char* filename, std::vector<Car>& cars) {
        if (Debug::ENABLE_DEBUG) printf("%s", Debug::DBG_LOADING_CARS); // Отладка

        FILE* f = fopen(filename, "r");             // Открываем файл на чтение
        if (!f) {                                   // Если не удалось открыть
            printf(Text::MSG_ERROR_OPEN, filename); // Сообщение об ошибке
            return false;
        }

        cars.clear();                               // Очищаем вектор перед загрузкой
        char line[MAX_LINE];                        // Буфер для одной строки
        size_t count = 0;                           // Счётчик загруженных записей

        while (fgets(line, sizeof(line), f)) {      // Читаем файл построчно
            clean_line(line);                       // Убираем \n и \r
            if (strlen(line) == 0) continue;        // Пропускаем пустые строки

            Car car;                                // Создаём временный объект
            if (parse_car(line, car)) {             // Пытаемся разобрать строку
                cars.push_back(std::move(car));     // Добавляем в вектор
                count++;                            // Увеличиваем счётчик
            }
        }
        fclose(f);                                  // Закрываем файл

        printf(Text::MSG_LOADED, count, filename);  // Сообщаем пользователю
        if (Debug::ENABLE_DEBUG) printf(Debug::DBG_CARS_LOADED, count); // Отладка

        return true;
    }

    // Загрузка регистраций из файла
    bool load_regs(const char* filename, std::vector<Registration>& regs) {
        if (Debug::ENABLE_DEBUG) printf("%s", Debug::DBG_LOADING_REGS);

        FILE* f = fopen(filename, "r");
        if (!f) {
            printf(Text::MSG_ERROR_OPEN, filename);
            return false;
        }

        regs.clear();
        char line[MAX_LINE];
        size_t count = 0;

        while (fgets(line, sizeof(line), f)) {
            clean_line(line);
            if (strlen(line) == 0) continue;

            Registration reg;
            if (parse_reg(line, reg)) {
                regs.push_back(std::move(reg));
                count++;
            }
        }
        fclose(f);

        printf(Text::MSG_LOADED, count, filename);
        if (Debug::ENABLE_DEBUG) printf(Debug::DBG_REGS_LOADED, count);

        return true;
    }

} // namespace FileIO