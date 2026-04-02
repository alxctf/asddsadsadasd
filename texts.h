// texts.h
#ifndef TEXTS_H                              // Защита от повторного включения
#define TEXTS_H

#define _CRT_SECURE_NO_WARNINGS              // Отключает предупреждения Visual Studio о небезопасных функциях

namespace Text {                             // Все текстовые строки программы собраны здесь

    // Имена файлов

	const char* const ERR_CREATE_FILE = "ошибка создания файла %s\n"; // Сообщение об ошибке при создании файла

    const char* const FILE_CARS = "cars.txt";     // Файл с данными об автомобилях
    const char* const FILE_REGS = "regs.txt";     // Файл с данными о регистрации
    const char* const FILE_RESULT = "result.txt";   // Файл для сохранения полного отчёта

    // Основные сообщения для пользователя
    const char* const MSG_WELCOME = "\n=== ПРОГРАММА ОБРАБОТКИ ДАННЫХ АВТОМОБИЛЕЙ ===\n\n";
    const char* const MSG_ERROR_OPEN = "Ошибка открытия файла %s\n";
    const char* const MSG_LOADED = "Загружено %zu записей из %s\n";
    const char* const MSG_TOTAL = "Всего загружено: %zu машин и %zu регистраций\n\n";
    const char* const MSG_NO_DATA = "По вашему запросу ничего не найдено.\n";
    const char* const MSG_SUCCESS_FILE = "Данные успешно записаны в файл %s\n";
    const char* const MSG_PROGRAM_END = "\nПрограмма завершена.\n";
    const char* const MSG_INVALID_CHOICE = "Неверный выбор!\n";
    const char* const MSG_PRESS_ENTER = "\nНажмите Enter для продолжения...";

    // Главное меню
    const char* const MSG_MAIN_MENU =
        "\nВыберите режим работы:\n"
        "1. Поиск информации на экран (избирательный режим)\n"
        "2. Полный вывод всех данных в файл result.txt\n"
        "0. Выход из программы\n"
        "Ваш выбор: ";

    // Меню выбора поля для поиска
    const char* const MSG_SEARCH_FIELD =
        "\nПо какому полю выполнять поиск?\n"
        "1. Номерной знак (основной ключ)\n"
        "2. ФИО владельца\n"
        "3. Марка автомобиля\n"
        "4. Модель автомобиля\n"
        "5. Адрес регистрации\n"
        "6. Год регистрации\n"
        "7. ID записи\n"
        "Выберите поле (1-7): ";

    const char* const MSG_ENTER_QUERY = "Введите поисковый запрос: ";

    // Заголовки вывода
    const char* const MSG_SEARCH_HEADER = "\n=== РЕЗУЛЬТАТЫ ПОИСКА ===\n";
    const char* const MSG_FULL_REPORT_HEADER = "=== ПОЛНЫЙ ОТЧЁТ ПО АВТОМОБИЛЯМ ===\n\n";
    const char* const MSG_RECORD_SEPARATOR = "--------------------------------------------------\n";

    // Тексты для вывода на экран
    const char* const PRINT_ID = "ID: %d\n";
    const char* const PRINT_PLATE = "Номерной знак: %s\n";
    const char* const PRINT_CAR = "Авто: %s %s\n";
    const char* const PRINT_OWNER = "Владелец: %s\n";
    const char* const PRINT_ADDRESS = "Адрес регистрации: %s\n";
    const char* const PRINT_YEAR = "Год регистрации: %d\n";

    // Тексты для записи в файл result.txt
    const char* const REPORT_ID = "ID: %d\n";
    const char* const REPORT_PLATE = "Номерной знак: %s\n";
    const char* const REPORT_CAR = "Авто: %s %s\n";
    const char* const REPORT_OWNER = "Владелец: %s\n";
    const char* const REPORT_ADDRESS = "Адрес регистрации: %s\n";
    const char* const REPORT_YEAR = "Год регистрации: %d\n";
    const char* const REPORT_TOTAL = "Всего записей: %zu\n\n";

    // Тексты для пустых полей
    const char* const EMPTY_PLATE = "Номерной знак: *пусто*\n";
    const char* const EMPTY_CAR = "Авто: *пусто*\n";
    const char* const EMPTY_CAR_BRAND = "Авто: %s *пусто*\n";
    const char* const EMPTY_CAR_MODEL = "Авто: *пусто* %s\n";
    const char* const EMPTY_OWNER = "Владелец: *пусто*\n";
    const char* const EMPTY_ADDRESS = "Адрес регистрации: *пусто*\n";
    const char* const EMPTY_YEAR = "Год регистрации: *пусто*\n";

} // namespace Text

#endif