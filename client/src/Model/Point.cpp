#include "Point.h"

Point::Point(int x, int y)
        : m_x(x)
        , m_y(y)
{
}

void Point::set_x(int x) {
    m_x = x;
}

int Point::get_x() const {
    return m_x;
}

void Point::set_y(int y) {
    m_y = y;
}

int Point::get_y() const {
    return m_y;
}

Json::Value Point::to_json() const {
    Json::Value result;
    result["x"] = m_x;
    result["y"] = m_y;
    return result;
}

std::ostream& operator<<(std::ostream& output, const Point& point) {
    return output << "(" << point.x() << ", " << point.y() << ")";
}
