#include "Map.h"

#include <algorithm>

Map::Map(size_t width, size_t height, const std::vector<Path>& paths)
        : m_width(width)
        , m_height(height)
        , m_cells(width, std::vector<Cell>(height))
        , m_paths(paths)
{
}

Map::Map(const std::vector<std::vector<Cell>>& cells, const std::vector<Path>& paths)
        : m_width(cells.size())
        , m_height(cells.at(0).size())
        , m_cells(cells)
        , m_paths(paths)
{
}

void Map::set_width(size_t width) {
    m_width = width;
    m_cells.resize(m_width, std::vector<Cell>(m_height));
}

void Map::set_height(size_t height) {
    m_height = height;
    for (auto& row : m_cells)
        row.resize(m_height);
}

size_t Map::get_width() const {
    return m_width;
}

size_t Map::get_height() const {
    return m_height;
}

void Map::set_cells(const std::vector<std::vector<Cell>>& cells) {
    m_cells = cells;
}

void Map::set_my_units(const std::vector<Unit>& my_units) {
    m_my_units = std::vector<std::shared_ptr<Unit>>(my_units.size());
    std::transform(my_units.begin(), my_units.end(), m_my_units.begin(),
                   [](auto& unit) { std::make_shared<Unit>(unit); });
}

void Map::set_enemy_units(const std::vector<Unit>& enemy_units) {
    m_enemy_units = std::vector<std::shared_ptr<Unit>>(enemy_units.size());
    std::transform(enemy_units.begin(), enemy_units.end(), m_enemy_units.begin(),
                   [](auto& unit) { std::make_shared<Unit>(unit); });
}

void Map::set_my_towers(const std::vector<Tower>& my_towers) {
    m_my_towers = std::vector<std::shared_ptr<Tower>>(my_towers.size());
    std::transform(my_towers.begin(), my_towers.end(), m_my_towers.begin(),
                   [](auto& unit) { std::make_shared<Tower>(unit); });
}

void Map::set_visible_enemy_towers(const std::vector<Tower>& visible_enemy_towers) {
    m_visible_enemy_towers = std::vector<std::shared_ptr<Tower>>(visible_enemy_towers.size());
    std::transform(visible_enemy_towers.begin(), visible_enemy_towers.end(), m_visible_enemy_towers.begin(),
                   [](auto& unit) { std::make_shared<Tower>(unit); });
}

void Map::set_paths(const std::vector<Path>& paths) {
    m_paths = paths;
}

std::vector<std::vector<Cell>>& Map::get_cells() {
    return m_cells;
}

const std::vector<std::vector<Cell>>& Map::get_cells() const {
    return m_cells;
}

std::vector<std::shared_ptr<Unit>>& Map::get_my_units() {
    return m_my_units;
}

std::vector<std::shared_ptr<const Unit>> Map::get_my_units() const {
    return std::vector<std::shared_ptr<const Unit>>(m_my_units.begin(), m_my_units.end());
}

std::vector<std::shared_ptr<Unit>>& Map::get_enemy_units() {
    return m_enemy_units;
}

std::vector<std::shared_ptr<const Unit>> Map::get_enemy_units() const {
    return std::vector<std::shared_ptr<const Unit>>(m_my_units.begin(), m_my_units.end());
}

std::vector<std::shared_ptr<Tower>>& Map::get_my_towers() {
    return m_my_towers;
}

std::vector<std::shared_ptr<const Tower>> Map::get_my_towers() const {
    return std::vector<std::shared_ptr<const Tower>>(m_my_towers.begin(), m_my_towers.end());
}

std::vector<std::shared_ptr<Tower>>& Map::get_visible_enemy_towers() {
    return m_visible_enemy_towers;
}

std::vector<std::shared_ptr<const Tower>> Map::get_visible_enemy_towers() const {
    return std::vector<std::shared_ptr<const Tower>>(m_visible_enemy_towers.begin(), m_visible_enemy_towers.end());
}

std::vector<Path>& Map::get_paths() {
    return m_paths;
}

const std::vector<Path>& Map::get_paths() const {
    return m_paths;
}
