#include "Map.h"

#include "../Utility.h"

Map::Map(const std::vector<std::vector<Cell*>>& cells_grid)
        : m_cells_grid(cells_grid)
{
}

Map::~Map() {
    clear_cells_grid();
}

size_t Map::get_width() const {
    return m_cells_grid.size();
}

size_t Map::get_height() const {
    return m_cells_grid.front().size();
}

void Map::set_cells_grid(const std::vector<std::vector<Cell*>>& cells_grid) {
    clear_cells_grid();
    m_cells_grid = cells_grid;
}

const std::vector<std::vector<Cell*>>& Map::get_cells_grid() {
    return m_cells_grid;
}

std::vector<std::vector<const Cell*>> Map::get_cells_grid() const {
    return const_grid_cast<const Cell*>(m_cells_grid);
}

std::vector<Cell*> Map::get_cells_list() {
    return flatten_list(m_cells_grid);
}

std::vector<const Cell*> Map::get_cells_list() const {
    return const_list_cast<const Cell*>(flatten_list(m_cells_grid));
}

Cell* Map::get_cell(Point location) {
    return m_cells_grid[location.get_x()][location.get_y()];
}

const Cell* Map::get_cell(Point location) const {
    return m_cells_grid[location.get_x()][location.get_y()];
}

void Map::clear_cells_grid() {
    for (Cell* cell : get_cells_list())
        delete cell;
    m_cells_grid.clear();
}
