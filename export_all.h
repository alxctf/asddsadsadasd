// export_all.h
#ifndef EXPORT_ALL_H                          // Защита от повторного включения файла
#define EXPORT_ALL_H

#include "structures.h"                       // Подключаем структуры Car и Registration
#include <vector>                             // Для std::vector

// Пространство имён для режима "Полный вывод в файл"
namespace ExportAll {

    // Основная функция режима 2
    // Принимает два вектора: машины и регистрации
    // Возвращает true, если экспорт прошёл успешно
    bool execute(const std::vector<Car>& cars, const std::vector<Registration>& regs);

} // namespace ExportAll

#endif