#include "Map.h"

Map::Map(const SharedPtrGrid<Cell>& cells_grid)
        : m_cells_grid(cells_grid)
{
}

size_t Map::get_width() const {
    return m_cells_grid.size();
}

size_t Map::get_height() const {
    return m_cells_grid.front().size();
}

void Map::set_cells_grid(const SharedPtrGrid<Cell>& cells_grid) {
    m_cells_grid = cells_grid;
}

std::vector<std::vector<Cell*>> Map::get_cells_grid() {
    return shared_ptr_grid_to_raw_pointer_grid<Cell>(m_cells_grid);
}

std::vector<std::vector<const Cell*>> Map::get_cells_grid() const {
    return shared_ptr_grid_to_raw_pointer_grid<const Cell>(m_cells_grid);
}

std::vector<Cell*> Map::get_cells_list() {
    return flatten_list(get_cells_grid());
}

std::vector<const Cell*> Map::get_cells_list() const {
    return flatten_list(get_cells_grid());
}

Cell* Map::get_cell(Point location) {
    return m_cells_grid[location.get_x()][location.get_y()].get();
}

const Cell* Map::get_cell(Point location) const {
    return m_cells_grid[location.get_x()][location.get_y()].get();
}
