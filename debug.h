// debug.h
#ifndef DEBUG_H
#define DEBUG_H

namespace Debug {

    // Эта константа включает или отключает все отладочные сообщения
    constexpr bool ENABLE_DEBUG = true;

    const char* const DBG_LOADING = "[DEBUG] Начало загрузки \n";

    // Отладочные сообщения
    const char* const DBG_LOADING_CARS = "[DEBUG] Начало загрузки cars.txt...\n";
    const char* const DBG_LOADING_REGS = "[DEBUG] Начало загрузки regs.txt...\n";
    const char* const DBG_CARS_LOADED = "[DEBUG] Загружено %zu машин\n";
    const char* const DBG_REGS_LOADED = "[DEBUG] Загружено %zu регистраций\n";

    const char* const DBG_SEARCH_START = "[DEBUG] Начало поиска по полю %d, запрос: \"%s\"\n";
    const char* const DBG_RECORD_FOUND = "[DEBUG] Найдена запись с ID = %d\n";
    const char* const DBG_NO_MATCH = "[DEBUG] Совпадений не найдено\n";

    const char* const DBG_EXPORT_START = "[DEBUG] Начало экспорта в result.txt...\n";
    const char* const DBG_TOTAL_IDS = "[DEBUG] Всего уникальных ID: %zu\n";
    const char* const DBG_NO_CAR = "[DEBUG] Для ID %d машина не найдена\n";
    const char* const DBG_NO_REG = "[DEBUG] Для ID %d регистрация не найдена\n";
    const char* const DBG_EXPORT_FINISH = "[DEBUG] Экспорт завершён. Записано %zu записей\n";

    const char* const DBG_MODE_SELECTED = "[DEBUG] Выбран режим: %d\n";

} // namespace Debug

#endif