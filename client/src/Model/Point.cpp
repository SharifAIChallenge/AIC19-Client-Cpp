#include "Point.h"

Point::Point(int x, int y)
        : m_x(x)
        , m_y(y)
{
}

int& Point::x() {
    return m_x;
}

int& Point::y() {
    return m_y;
}

int Point::x() const {
    return m_x;
}

int Point::y() const {
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
