// search_by_field.h
#ifndef SEARCH_BY_FIELD_H
#define SEARCH_BY_FIELD_H

#include "structures.h"
#include <vector>

// Пространство имён для режима "Поиск по полю"
namespace SearchByField {
    void execute(const std::vector<Car>& cars, const std::vector<Registration>& regs);
}

#endif