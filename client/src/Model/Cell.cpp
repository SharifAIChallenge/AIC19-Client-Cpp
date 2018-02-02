#include "Cell.h"

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

const SharedPtrList<Unit>& RoadCell::get_units() {
    return m_units;
}

SharedPtrList<const Unit> RoadCell::get_units() const {
    return SharedPtrList<const Unit>(m_units.begin(), m_units.end());
}

GrassCell::GrassCell(Point location)
        : Cell(location)
{
}

void GrassCell::set_tower(const std::shared_ptr<Tower>& tower) {
    m_tower = tower;
}

std::shared_ptr<Tower> GrassCell::get_tower() {
    return m_tower;
}

std::shared_ptr<const Tower> GrassCell::get_tower() const {
    return std::const_pointer_cast<const Tower>(m_tower);
}

BlockCell::BlockCell(Point location)
        : Cell(location)
{
}
