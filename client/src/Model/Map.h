#ifndef AIC18_CLIENT_CPP_MAP_H
#define AIC18_CLIENT_CPP_MAP_H

#include "../Core/Utility.h"
#include "Cell.h"
#include "Point.h"

/**
 * A 2d grid of @see Cell objects
 */
class Map {
public:

    Map() = default;
    ~Map() = default;

    Map(const Map&) = default;
    Map& operator=(const Map&) = default;

    explicit Map(const SharedPtrGrid<Cell>& cells_grid);

    size_t get_width() const;
    size_t get_height() const;

    void set_cells_grid(const SharedPtrGrid<Cell>& cells_grid);

    std::vector<std::vector<Cell*>> get_cells_grid();
    std::vector<std::vector<const Cell*>> get_cells_grid() const;

    std::vector<Cell*> get_cells_list();
    std::vector<const Cell*> get_cells_list() const;

    Cell* get_cell(Point location);
    const Cell* get_cell(Point location) const;

private:

    /// 2d array of map cells
    SharedPtrGrid<Cell> m_cells_grid;

};

#endif // AIC18_CLIENT_CPP_MAP_H
