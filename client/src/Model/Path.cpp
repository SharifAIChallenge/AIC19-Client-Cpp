#include "Path.h"

void Path::set_road(const std::vector<Point>& road) {
    m_road = road;
}

std::vector<Point>& Path::get_road() {
    return m_road;
}

const std::vector<Point>& Path::get_road() const {
    return m_road;
}

