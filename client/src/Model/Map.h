#ifndef AIC18_CLIENT_CPP_MAP_H
#define AIC18_CLIENT_CPP_MAP_H

#include <vector>

#include "Cell.h"

/**
 * A 2d grid of @see Cell objects
 */
class Map {
public:

    Map(size_t width, size_t height);
    ~Map() = default;

    Map(const Map&) = default;
    Map& operator= (const Map&) = default;

    size_t get_width() const;
    size_t get_height() const;

    std::vector<Cell>& operator[] (int index);
    const std::vector<Cell>& operator[] (int index) const;

private:

    /// Map dimensions
    size_t m_width , m_height;

    /// The actual cells of the map
    std::vector<std::vector<Cell>> m_cells;

};

#endif // AIC18_CLIENT_CPP_MAP_H
