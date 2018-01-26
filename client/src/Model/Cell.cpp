#include "Cell.h"

#include <algorithm>
#include <functional>

Cell::Cell(CellType type, Point location)
        : m_type(type)
        , m_location(location)
{
}

void Cell::set_type(CellType type) {
    m_type = type;
}

void Cell::set_location(Point location) {
    m_location = location;
}

CellType Cell::get_type() const {
    return m_type;
}

Point Cell::get_location() const {
    return m_location;
}

Cell::UnitList& Cell::get_units() {
    return m_units;
}

Cell::ConstUnitList Cell::get_units() const {
    return ConstUnitList(m_units.begin(), m_units.end());
}

void Cell::set_tower(const std::shared_ptr<Tower>& tower) {
    m_tower = tower;
}

bool Cell::has_tower() const {
    return m_tower != nullptr;
}

std::shared_ptr<const Tower> Cell::get_tower() const {
    return m_tower;
}
