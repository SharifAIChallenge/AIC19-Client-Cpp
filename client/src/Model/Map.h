#ifndef AIC18_CLIENT_CPP_MAP_H
#define AIC18_CLIENT_CPP_MAP_H

#include "Cell.h"
#include "Point.h"

/**
 * A 2d grid of @see Cell objects
 */
class Map {
public:

    Map() = default;
    explicit Map(const std::vector<std::vector<Cell*>>& cells_grid);

    Map(const Map& other);
    Map& operator=(const Map& other);

    Map(Map&& other) noexcept;
    Map& operator=(Map&& other) noexcept;

    ~Map();

    int get_width() const;
    int get_height() const;

    void set_cells_grid(const std::vector<std::vector<Cell*>>& cells_grid);

    std::vector<std::vector<Cell*>>& get_cells_grid();
    const std::vector<std::vector<Cell*>>& get_cells_grid() const;

    std::vector<Cell*> get_cells_list() const;

    /**
     * @tparam CellType Type of the return value
     *
     * @return Pointer to cell at location (@param x, @param y).
     * Returns nullptr if the cast fails (ie. the cell at the given location is not of type @tparam CellType)
     */
    template <class CellType = Cell>
    CellType* get_cell(int x, int y) const;

private:

    void clear_cells_grid();

    /// 2d array of map cells
    std::vector<std::vector<Cell*>> m_cells_grid;

};

template <class CellType>
CellType* Map::get_cell(int x, int y) const {
    return dynamic_cast<CellType*>(m_cells_grid[x][y]);
}

#endif // AIC18_CLIENT_CPP_MAP_H
