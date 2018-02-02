#include "Map.h"

Map::Map(const SharedPtrGrid<Cell>& cells_grid)
        : m_cells_grid(cells_grid)
{
}

void Map::set_cells_grid(const SharedPtrGrid<Cell>& cells_grid) {
    m_cells_grid = cells_grid;
}

const SharedPtrGrid<Cell>& Map::get_cells_grid() {
    return m_cells_grid;
}

SharedPtrGrid<const Cell> Map::get_cells_grid() const {
    SharedPtrGrid<const Cell> result;
    for (const auto& row : m_cells_grid)
        result.emplace_back(row.begin(), row.end());
    return result;
}

SharedPtrList<Cell> Map::get_cells_list() {
    SharedPtrList<Cell> result;
    for (const auto& row : m_cells_grid)
        result.insert(result.end(), row.begin(), row.end());
    return result;
}

SharedPtrList<const Cell> Map::get_cells_list() const {
    SharedPtrList<const Cell> result;
    for (const auto& row : m_cells_grid)
        result.insert(result.end(), row.begin(), row.end());
    return result;
}

std::shared_ptr<Cell> Map::get_cell(Point location) {
    return m_cells_grid[location.get_x()][location.get_y()];
}

std::shared_ptr<const Cell> Map::get_cell(Point location) const {
    return std::const_pointer_cast<const Cell>(m_cells_grid[location.get_x()][location.get_y()]);
}
