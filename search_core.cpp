// search_core.cpp
#define _CRT_SECURE_NO_WARNINGS                     // Отключает предупреждения о небезопасных функциях

#include "search_core.h"                            // Подключаем свой заголовочный файл
#include "texts.h"                                  // Подключаем все текстовые константы
#include <cstdio>                                   // Для printf и fprintf
#include <cstring>                                  // Для strlen, strcmp и т.д.

namespace SearchCore {                              // Общие функции поиска и печати

    // Вывод одной записи на экран (используется в режиме поиска)
    void print_record_screen(const Car& car, const Registration& reg) {
        printf(Text::PRINT_ID, reg.id);             // Выводим ID записи
        printf(Text::PRINT_PLATE, reg.plate.c_str()); // Выводим номерной знак
        printf(Text::PRINT_CAR, car.brand.c_str(), car.model.c_str()); // Выводим марку и модель
        printf(Text::PRINT_OWNER, reg.fio.c_str()); // Выводим ФИО владельца
        printf(Text::PRINT_ADDRESS, reg.address.c_str()); // Выводим адрес регистрации
        printf(Text::PRINT_YEAR, reg.reg_year);     // Выводим год регистрации
        printf("%s", Text::MSG_RECORD_SEPARATOR);   // Выводим разделительную линию
    }

    // Запись одной записи в файл result.txt
    // Принимает указатели, потому что может отсутствовать либо машина, либо регистрация
    void print_record_file(FILE* f, const Car* car, const Registration* reg) {
        int id = reg ? reg->id : (car ? car->id : 0);   // Определяем ID: берём из reg, если есть, иначе из car
        fprintf(f, Text::REPORT_ID, id);                // Записываем ID в файл

        // Поле "Номерной знак"
        if (reg && !reg->plate.empty())                 // Если есть регистрация и поле не пустое
            fprintf(f, Text::REPORT_PLATE, reg->plate.c_str()); // Записываем номер
        else
            fprintf(f, "%s", Text::EMPTY_PLATE);        // Иначе записываем "*пусто*"

        // Поле "Авто" (марка + модель)
        if (car && !car->brand.empty() && !car->model.empty())
            fprintf(f, Text::REPORT_CAR, car->brand.c_str(), car->model.c_str());
        else if (car && !car->brand.empty())
            fprintf(f, Text::EMPTY_CAR_BRAND, car->brand.c_str()); // марка есть, модель пустая
        else if (car && !car->model.empty())
            fprintf(f, Text::EMPTY_CAR_MODEL, car->model.c_str()); // модель есть, марка пустая
        else
            fprintf(f, "%s", Text::EMPTY_CAR);          // оба поля пустые

        // Поле "Владелец"
        if (reg && !reg->fio.empty())
            fprintf(f, Text::REPORT_OWNER, reg->fio.c_str());
        else
            fprintf(f, "%s", Text::EMPTY_OWNER);

        // Поле "Адрес регистрации"
        if (reg && !reg->address.empty())
            fprintf(f, Text::REPORT_ADDRESS, reg->address.c_str());
        else
            fprintf(f, "%s", Text::EMPTY_ADDRESS);

        // Поле "Год регистрации"
        if (reg && reg->reg_year != 0)
            fprintf(f, Text::REPORT_YEAR, reg->reg_year);
        else
            fprintf(f, "%s", Text::EMPTY_YEAR);

        fprintf(f, "%s\n", Text::MSG_RECORD_SEPARATOR); // Разделительная линия в файле
    }

    // Проверяет, соответствует ли запись поисковому запросу
    bool field_matches(const Car& car, const Registration& reg, int field, const char* query) {
        switch (field) {
        case 1: return _stricmp(reg.plate.c_str(), query) == 0;   // Сравнение номера авто (без учёта регистра)
        case 2: return strstr(reg.fio.c_str(), query) != nullptr; // Поиск подстроки в ФИО
        case 3: return strstr(car.brand.c_str(), query) != nullptr; // Поиск в марке
        case 4: return strstr(car.model.c_str(), query) != nullptr; // Поиск в модели
        case 5: return strstr(reg.address.c_str(), query) != nullptr; // Поиск в адресе
        case 6: return reg.reg_year == atoi(query);               // Сравнение года
        case 7: return reg.id == atoi(query);                     // Сравнение ID
        default: return false;                                    // Некорректное поле
        }
    }

} // namespace SearchCore