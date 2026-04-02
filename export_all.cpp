// export_all.cpp
#define _CRT_SECURE_NO_WARNINGS                     // Отключает предупреждения безопасности

#include "export_all.h"                             // Подключаем свой заголовок
#include "search_core.h"                            // Подключаем функции печати записей
#include "texts.h"                                  // Подключаем все текстовые константы
#include "debug.h"                                  // Подключаем отладочные сообщения
#include <vector>                                   // Для std::vector
#include <set>                                      // Для std::set (чтобы собрать уникальные ID)
#include <cstdio>                                   // Для fopen, fprintf, fclose

namespace ExportAll {                               // Пространство имён для полного экспорта

    bool execute(const std::vector<Car>& cars, const std::vector<Registration>& regs) {
        if (Debug::ENABLE_DEBUG) printf("%s", Debug::DBG_EXPORT_START); // Отладка: начало экспорта

        // Открываем файл result.txt на запись (режим "w" — перезаписать)
        FILE* f = fopen(Text::FILE_RESULT, "w");
        if (!f) {                                   // Если файл не удалось создать
            printf(Text::ERR_CREATE_FILE, Text::FILE_RESULT); // Используем константу из texts.h
            return false;                           // Возвращаем ошибку
        }

        // Записываем заголовок отчёта
        fprintf(f, "%s", Text::MSG_FULL_REPORT_HEADER);
        fprintf(f, Text::REPORT_TOTAL, regs.size()); // Записываем общее количество регистраций

        // Создаём множество всех уникальных ID из обоих файлов
        std::set<int> all_ids;
        for (const auto& c : cars) all_ids.insert(c.id);   // Добавляем ID из машин
        for (const auto& r : regs) all_ids.insert(r.id);   // Добавляем ID из регистраций

        if (Debug::ENABLE_DEBUG) printf(Debug::DBG_TOTAL_IDS, all_ids.size()); // Отладка

        int output_count = 0;                       // Счётчик записанных записей

        // Проходим по всем уникальным ID
        for (int id : all_ids) {
            // Ищем машину с этим ID
            const Car* car_ptr = nullptr;
            for (const auto& c : cars)
                if (c.id == id) { car_ptr = &c; break; }

            // Ищем регистрацию с этим ID
            const Registration* reg_ptr = nullptr;
            for (const auto& r : regs)
                if (r.id == id) { reg_ptr = &r; break; }

            // Отладочные сообщения
            if (Debug::ENABLE_DEBUG) {
                if (!car_ptr) printf(Debug::DBG_NO_CAR, id);
                if (!reg_ptr) printf(Debug::DBG_NO_REG, id);
            }

            // Записываем запись в файл (даже если чего-то не хватает)
            SearchCore::print_record_file(f, car_ptr, reg_ptr);
            output_count++;                         // Увеличиваем счётчик
        }

        fclose(f);                                  // Закрываем файл

        // Сообщаем пользователю об успехе
        printf(Text::MSG_SUCCESS_FILE, Text::FILE_RESULT);
        if (Debug::ENABLE_DEBUG) printf(Debug::DBG_EXPORT_FINISH, output_count); // Отладка

        return true;                                // Успешно
    }

} // namespace ExportAll