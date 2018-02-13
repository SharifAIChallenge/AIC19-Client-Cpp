#include "Cell.h"

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

RoadCell::RoadCell(const RoadCell& other)
        : Cell(other)
{
    for (Unit* unit : other.m_units)
        if (auto light_unit = dynamic_cast<LightUnit*>(unit))
            m_units.push_back(new LightUnit(*light_unit));
        else if (auto heavy_unit = dynamic_cast<HeavyUnit*>(unit))
            m_units.push_back(new HeavyUnit(*heavy_unit));
}

RoadCell& RoadCell::operator=(const RoadCell& other) {
    Cell::operator=(other);

    clear_units();
    for (Unit* unit : other.m_units)
        if (auto light_unit = dynamic_cast<LightUnit*>(unit))
            m_units.push_back(new LightUnit(*light_unit));
        else if (auto heavy_unit = dynamic_cast<HeavyUnit*>(unit))
            m_units.push_back(new HeavyUnit(*heavy_unit));

    return *this;
}

RoadCell::RoadCell(RoadCell&& other) noexcept
        : Cell(std::move(other))
        , m_units(std::move(other.m_units))
{
    other.m_units.clear();
}

RoadCell& RoadCell::operator=(RoadCell&& other) noexcept {
    Cell::operator= (std::move(other));
    m_units = std::move(other.m_units);
    other.m_units.clear();
    return *this;
}

RoadCell::~RoadCell() {
    clear_units();
}

void RoadCell::set_units(const std::vector<Unit*>& units) {
    clear_units();
    m_units = units;
}

std::vector<Unit*>& RoadCell::get_units() {
    return m_units;
}

const std::vector<Unit*>& RoadCell::get_units() const {
    return m_units;
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
    clear_tower();
    m_tower = tower;
}

Tower* GrassCell::get_tower() const {
    return m_tower;
}

void GrassCell::clear_tower() {
    delete m_tower;
    m_tower = nullptr;
}

GrassCell::GrassCell(const GrassCell& other)
        : Cell(other)
        , m_tower(nullptr)
{
    if (other.m_tower)
        m_tower = other.m_tower->clone();
}

GrassCell& GrassCell::operator=(const GrassCell& other) {
    Cell::operator=(other);

    clear_tower();
    if (other.m_tower)
        m_tower = other.m_tower->clone();

    return *this;
}

GrassCell::GrassCell(GrassCell&& other) noexcept
        : Cell(std::move(other))
        , m_tower(std::move(other.m_tower))
{
    other.m_tower = nullptr;
}

GrassCell& GrassCell::operator=(GrassCell&& other) noexcept {
    Cell::operator=(std::move(other));
    m_tower = std::move(other.m_tower);
    other.m_tower = nullptr;
    return *this;
}

BlockCell::BlockCell(Point location)
        : Cell(CellType::BLOCK, location)
{
}
