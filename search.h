// search.h
#ifndef SEARCH_H
#define SEARCH_H

#include "structures.h"
#include <vector>

void search_by_plate(const std::vector<Car>& cars, const std::vector<Registration>& regs, const char* plate);
void search_by_fio(const std::vector<Car>& cars, const std::vector<Registration>& regs, const char* fio_part);
void search_by_id(const std::vector<Car>& cars, const std::vector<Registration>& regs, int id);
void show_all(const std::vector<Car>& cars, const std::vector<Registration>& regs);

#endif