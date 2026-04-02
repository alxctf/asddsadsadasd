// file_io.h
#ifndef FILE_IO_H
#define FILE_IO_H

#include "structures.h"
#include <vector>

// Пространство имён для функций загрузки данных из файлов
namespace FileIO {
    bool load_cars(const char* filename, std::vector<Car>& cars);      // Загрузка автомобилей
    bool load_regs(const char* filename, std::vector<Registration>& regs); // Загрузка регистраций
}

#endif