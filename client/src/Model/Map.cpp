#include "Map.h"

#include <Utility/Utility.h>

Map::Map(const std::vector<std::vector<Cell*>>& cells_grid)
        : m_cells_grid(cells_grid)
{
}

Map::Map(const Map& other)
        : m_cells_grid(other.get_width(), std::vector<Cell*>(other.get_height(), nullptr))
{
    for (size_t i = 0; i < other.get_width(); ++i)
        for (size_t j = 0; j < other.get_height(); ++j)
            if (auto road_cell = dynamic_cast<RoadCell*>(other.m_cells_grid[i][j]))
                m_cells_grid[i][j] = new RoadCell(*road_cell);
            else if (auto grass_cell = dynamic_cast<GrassCell*>(other.m_cells_grid[i][j]))
                m_cells_grid[i][j] = new GrassCell(*grass_cell);
            else if (auto block_cell = dynamic_cast<BlockCell*>(other.m_cells_grid[i][j]))
                m_cells_grid[i][j] = new BlockCell(*block_cell);
}

Map& Map::operator=(const Map& other) {
    clear_cells_grid();

    m_cells_grid = std::vector<std::vector<Cell*>>(other.get_width(),
                                                   std::vector<Cell*>(other.get_height(), nullptr));

    for (size_t i = 0; i < other.get_width(); ++i)
        for (size_t j = 0; j < other.get_height(); ++j)
            if (auto road_cell = dynamic_cast<RoadCell*>(other.m_cells_grid[i][j]))
                m_cells_grid[i][j] = new RoadCell(*road_cell);
            else if (auto grass_cell = dynamic_cast<GrassCell*>(other.m_cells_grid[i][j]))
                m_cells_grid[i][j] = new GrassCell(*grass_cell);
            else if (auto block_cell = dynamic_cast<BlockCell*>(other.m_cells_grid[i][j]))
                m_cells_grid[i][j] = new BlockCell(*block_cell);

    return *this;
}

Map::~Map() {
    clear_cells_grid();
}

int Map::get_width() const {
    return static_cast<int>(m_cells_grid.size());
}

int Map::get_height() const {
    return static_cast<int>(m_cells_grid.front().size());
}

void Map::set_cells_grid(const std::vector<std::vector<Cell*>>& cells_grid) {
    clear_cells_grid();
    m_cells_grid = cells_grid;
}

std::vector<std::vector<Cell*>>& Map::get_cells_grid() {
    return m_cells_grid;
}

const std::vector<std::vector<Cell*>>& Map::get_cells_grid() const {
    return m_cells_grid;
}

std::vector<Cell*> Map::get_cells_list() const {
    return flatten_list(m_cells_grid);
}

void Map::clear_cells_grid() {
    for (Cell* cell : get_cells_list())
        delete cell;
    m_cells_grid.clear();
}

Map::Map(Map&& other) noexcept
        : m_cells_grid(std::move(other.m_cells_grid))
{
    other.m_cells_grid.clear();
}

Map& Map::operator=(Map&& other) noexcept {
    m_cells_grid = std::move(other.m_cells_grid);
    other.m_cells_grid.clear();
    return *this;
}
