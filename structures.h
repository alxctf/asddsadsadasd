// structures.h
#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <string>

// Структура для хранения информации об автомобиле
struct Car {
    int id;                    // Порядковый номер записи (внутренний ID)
    std::string plate;         // Номерной знак автомобиля (главный ключ связи)
    std::string brand;         // Марка автомобиля
    std::string model;         // Модель автомобиля
};

// Структура для хранения информации о регистрации автомобиля
struct Registration {
    int id;                    // Порядковый номер записи
    std::string fio;           // ФИО владельца
    std::string plate;         // Номерной знак автомобиля
    std::string address;       // Адрес регистрации
    int reg_year;              // Год регистрации
};

#endif