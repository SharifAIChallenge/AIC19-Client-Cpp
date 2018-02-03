#include "Path.h"

#include <algorithm>

Path::Path(const SharedPtrList<RoadCell>& road)
        : m_road(road)
{
}

void Path::set_road(const SharedPtrList<RoadCell>& road) {
    m_road = road;
}

std::vector<RoadCell*> Path::get_road() {
    std::vector<RoadCell*> result(m_road.size());
    std::transform(m_road.begin(), m_road.end(), result.begin(), [](const auto& x) { return x.get(); });
    return result;
}

std::vector<const RoadCell*> Path::get_road() const {
    std::vector<const RoadCell*> result(m_road.size());
    std::transform(m_road.begin(), m_road.end(), result.begin(), [](const auto& x) { return x.get(); });
    return result;
}
