// search.cpp
#define _CRT_SECURE_NO_WARNINGS

#include "search.h"
#include "texts.h"
#include <vector>
#include <string>
#include <cstdio>
#include <cstring>
#include <cctype>

// Вспомогательные функции
namespace SearchUtils {

    bool contains_ignore_case(const std::string& str, const std::string& substr) {
        if (substr.empty()) return true;
        std::string s1 = str;
        std::string s2 = substr;
        for (char& c : s1) c = (char)std::tolower((unsigned char)c);
        for (char& c : s2) c = (char)std::tolower((unsigned char)c);
        return s1.find(s2) != std::string::npos;
    }

    void print_record(const Registration& reg, const Car& car) {
        printf(MSG_RECORD_ID, reg.id);
        printf(MSG_RECORD_PLATE, reg.plate.c_str());
        printf(MSG_RECORD_BRAND_AND_MODEL, car.brand.c_str(), car.model.c_str());
        printf(MSG_RECORD_SURNAME, reg.fio.c_str());
        printf(MSG_RECORD_ADDRESS, reg.address.c_str());
        printf(MSG_RECORD_YEAR, reg.reg_year);
        printf(MSG_LINE_SEPARATOR);
    }
}

void search_by_plate(const std::vector<Car>& cars, const std::vector<Registration>& regs, const char* plate)
{
    bool found = false;
    printf(MSG_RESULT_PLATE, plate);

    for (const auto& reg : regs) {
        if (_stricmp(reg.plate.c_str(), plate) == 0) {
            for (const auto& car : cars) {
                if (car.id == reg.id) {
                    SearchUtils::print_record(reg, car);
                    found = true;
                    break;
                }
            }
        }
    }
    if (!found) printf(MSG_NO_DATA);
}


void search_by_fio(const std::vector<Car>& cars, const std::vector<Registration>& regs, const char* fio_part)
{
    bool found = false;
    printf(MSG_RESULT_SURNAME, fio_part);

    for (const auto& reg : regs) {
        if (SearchUtils::contains_ignore_case(reg.fio, fio_part)) {
            for (const auto& car : cars) {
                if (car.id == reg.id) {
                    SearchUtils::print_record(reg, car);
                    found = true;
                    break;
                }
            }
        }
    }
    if (!found) printf(MSG_NO_DATA);
}

void search_by_id(const std::vector<Car>& cars, const std::vector<Registration>& regs, int id)
{
    bool found = false;
    printf(MSG_RESULT_ID, id);

    for (const auto& reg : regs) {
        if (reg.id == id) {
            for (const auto& car : cars) {
                if (car.id == id) {
                    SearchUtils::print_record(reg, car);
                    found = true;
                    break;
                }
            }
        }
    }
    if (!found) printf(MSG_NO_DATA);
}

void show_all(const std::vector<Car>& cars, const std::vector<Registration>& regs)
{
    printf(MSG_RESULT_ALL, regs.size());

    for (const auto& reg : regs) {
        for (const auto& car : cars) {
            
            printf("ID: %d | %s | %s %s | %s | %s | %d\n",
                    reg.id, reg.plate.c_str(),
                    car.brand.c_str(), car.model.c_str(),
                    reg.fio.c_str(), reg.address.c_str(), reg.reg_year);
            break;
            
        }
    }
    printf(MSG_LINE_SEPARATOR);
}