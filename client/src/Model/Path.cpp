#include "Path.h"

#include "Cell.h"

Path::Path(const std::vector<RoadCell*>& road)
        : m_road(road)
{
}

void Path::set_road(const std::vector<RoadCell*>& road) {
    m_road = road;
}

std::vector<RoadCell*>& Path::get_road() {
    return m_road;
}

const std::vector<RoadCell*>& Path::get_road() const {
    return m_road;
}

std::ostream& operator<<(std::ostream& output, const Path& path) {
    for (const Cell* cell : path.get_road())
        output << cell->get_location() << " ";
    return output;
}
