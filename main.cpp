// main.cpp
#define _CRT_SECURE_NO_WARNINGS                     // Отключает предупреждения Visual Studio

#include "constants.h"                              // Подключаем константы размеров
#include "structures.h"                             // Подключаем структуры данных
#include "file_io.h"                                // Подключаем функции загрузки файлов
#include "texts.h"                                  // Подключаем все текстовые сообщения
#include "search_by_field.h"                        // Подключаем режим поиска
#include "export_all.h"                             // Подключаем режим полного экспорта
#include "debug.h"                                  // Подключаем отладку
#include <vector>                                   // Для std::vector
#include <cstdio>                                   // Для printf, scanf, getchar
#include <windows.h>                                // Для SetConsoleCP и SetConsoleOutputCP
#include <locale.h>                                 // Для setlocale

// Вспомогательная функция: получает корректный выбор пользователя
// Защищает от ввода неправильных чисел
int get_valid_choice(int min, int max) {
    int choice;
    while (true) {                                  // Бесконечный цикл до правильного ввода
        if (scanf("%d", &choice) == 1 && choice >= min && choice <= max) {
            return choice;                          // Ввод корректный — возвращаем значение
        }
        printf("%s", Text::MSG_INVALID_CHOICE);     // Сообщение об ошибке
        while (getchar() != '\n');                  // Очищаем буфер ввода до конца строки
    }
}

int main()                                          // Главная функция программы
{
    setlocale(LC_ALL, "Russian");                   // Устанавливаем русскую локаль
    SetConsoleCP(1251);                             // Устанавливаем кодовую страницу для ввода
    SetConsoleOutputCP(1251);                       // Устанавливаем кодовую страницу для вывода

    std::vector<Car> cars;                          // Вектор для хранения автомобилей
    std::vector<Registration> regs;                 // Вектор для хранения регистраций

    printf("%s", Text::MSG_WELCOME);                // Выводим приветствие

    if (Debug::ENABLE_DEBUG) printf(Debug::DBG_LOADING); // Отладка

    // Загружаем данные из файлов
    if (!FileIO::load_cars(Text::FILE_CARS, cars) ||
        !FileIO::load_regs(Text::FILE_REGS, regs)) {
        getchar();                                  // Ждём нажатия клавиши перед выходом
        return 1;                                   // Завершаем программу с ошибкой
    }

    printf(Text::MSG_TOTAL, cars.size(), regs.size()); // Выводим сколько записей загружено

    int mode;                                       // Переменная для выбора режима
    do {                                            // Цикл меню (повторяется пока не выберут 0)
        printf("%s", Text::MSG_MAIN_MENU);          // Показываем главное меню
        mode = get_valid_choice(0, 2);              // Получаем корректный выбор (0, 1 или 2)

        if (Debug::ENABLE_DEBUG) printf(Debug::DBG_MODE_SELECTED, mode); // Отладка

        if (mode == 1) {                            // Режим 1 — поиск на экран
            SearchByField::execute(cars, regs);
        }
        else if (mode == 2) {                       // Режим 2 — полный экспорт в файл
            ExportAll::execute(cars, regs);
        }

        if (mode != 0) {                            // Если не выход — просим нажать Enter
            printf("%s", Text::MSG_PRESS_ENTER);
            getchar();                              // Съедаем остаток строки
            getchar();                              // Ждём нажатия Enter
        }

    } while (mode != 0);                            // Повторяем, пока не выбрали 0 (выход)

    printf("%s", Text::MSG_PROGRAM_END);            // Прощальное сообщение
    return 0;                                       // Успешное завершение программы
}