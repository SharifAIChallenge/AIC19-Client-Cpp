#include "Cell.h"

#include <algorithm>

Cell::Cell(Point location)
        : m_location(location)
{
}

void Cell::set_location(Point location) {
    m_location = location;
}

Point Cell::get_location() const {
    return m_location;
}

RoadCell::RoadCell(Point location)
        : Cell(location)
{
}

void RoadCell::set_units(const SharedPtrList<Unit>& units) {
    m_units = units;
}

std::vector<Unit*> RoadCell::get_units() {
    std::vector<Unit*> result(m_units.size());
    std::transform(m_units.begin(), m_units.end(), result.begin(), [](const auto& x) { return x.get(); });
    return result;
}

std::vector<const Unit*> RoadCell::get_units() const {
    std::vector<const Unit*> result(m_units.size());
    std::transform(m_units.begin(), m_units.end(), result.begin(), [](const auto& x) { return x.get(); });
    return result;
}

GrassCell::GrassCell(Point location)
        : Cell(location)
{
}

void GrassCell::set_tower(const std::shared_ptr<Tower>& tower) {
    m_tower = tower;
}

Tower* GrassCell::get_tower() {
    return m_tower.get();
}

const Tower* GrassCell::get_tower() const {
    return m_tower.get();
}

BlockCell::BlockCell(Point location)
        : Cell(location)
{
}
