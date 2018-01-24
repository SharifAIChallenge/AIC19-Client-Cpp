#include "Map.h"

Map::Map(size_t width, size_t height)
        : m_width(width)
        , m_height(height)
        , m_cells(width, std::vector<Cell>(height))
{
}

size_t Map::get_width() const {
    return m_width;
}

size_t Map::get_height() const {
    return m_height;
}

std::vector<Cell>& Map::operator[](int index) {
    return m_cells[index];
}

const std::vector<Cell>& Map::operator[](int index) const {
    return m_cells[index];
}
