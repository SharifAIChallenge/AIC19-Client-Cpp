#include "Path.h"

#include "Cell.h"
#include "../Utility.h"

Path::Path(const std::vector<const RoadCell*>& road)
        : m_road(road)
{
}

void Path::set_road(const std::vector<const RoadCell*>& road) {
    m_road = road;
}

const std::vector<const RoadCell*>& Path::get_road() {
    return m_road;
}

std::vector<const RoadCell*> Path::get_road() const {
    return const_list_cast<const RoadCell*>(m_road);
}

std::ostream& operator<<(std::ostream& output, const Path& path) {
    for (const Cell* cell : path.get_road())
        output << cell->get_location() << " ";
    return output;
}
