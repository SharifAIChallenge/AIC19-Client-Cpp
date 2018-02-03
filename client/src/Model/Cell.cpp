#include "Cell.h"

#include "../Utility.h"

Cell::Cell(CellType type, Point location)
        : m_type(type)
        , m_location(location)
{
}

void Cell::set_type(CellType type) {
    m_type = type;
}

CellType Cell::get_type() const {
    return m_type;
}

void Cell::set_location(Point location) {
    m_location = location;
}

Point Cell::get_location() const {
    return m_location;
}

RoadCell::RoadCell(Point location)
        : Cell(CellType::ROAD, location)
{
}

RoadCell::~RoadCell() {
    clear_units();
}

void RoadCell::set_units(const std::vector<Unit*>& units) {
    clear_units();
    m_units = units;
}

const std::vector<Unit*>& RoadCell::get_units() {
    return m_units;
}

std::vector<const Unit*> RoadCell::get_units() const {
    return const_list_cast<const Unit*>(m_units);
}

void RoadCell::clear_units() {
   for (Unit* unit : m_units)
       delete unit;
    m_units.clear();
}

GrassCell::GrassCell()
        : Cell()
        , m_tower(nullptr)
{
}

GrassCell::GrassCell(Point location)
        : Cell(CellType::GRASS, location)
        , m_tower(nullptr)
{
}

GrassCell::~GrassCell() {
    clear_tower();
}

void GrassCell::set_tower(Tower* tower) {
    m_tower = tower;
}

Tower* GrassCell::get_tower() {
    return m_tower;
}

const Tower* GrassCell::get_tower() const {
    return m_tower;
}

void GrassCell::clear_tower() {
    delete m_tower;
    m_tower = nullptr;
}

BlockCell::BlockCell(Point location)
        : Cell(CellType::BLOCK, location)
{
}
