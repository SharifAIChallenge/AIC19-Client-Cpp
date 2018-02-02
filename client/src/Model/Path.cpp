#include "Path.h"

Path::Path(const SharedPtrList<RoadCell>& road)
        : m_road(road)
{
}

void Path::set_road(const SharedPtrList<RoadCell>& road) {
    m_road = road;
}

const SharedPtrList<RoadCell>& Path::get_road() {
    return m_road;
}

SharedPtrList<const RoadCell> Path::get_road() const {
    return SharedPtrList<const RoadCell>(m_road.begin(), m_road.end());
}
