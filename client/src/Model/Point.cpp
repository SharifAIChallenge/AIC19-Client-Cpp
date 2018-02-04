#include "Point.h"

Point::Point(int x, int y)
        : m_x(x)
        , m_y(y)
{
}

Point::Point(const Json::Value& json_form)
        : m_x(json_form["x"].asInt())
        , m_y(json_form["y"].asInt())
{
}

void Point::set_x(int x) {
    m_x = x;
}

int Point::get_x() const {
    return m_x;
}

int& Point::x() {
    return m_x;
}

int Point::x() const {
    return m_x;
}

void Point::set_y(int y) {
    m_y = y;
}

int Point::get_y() const {
    return m_y;
}

int& Point::y() {
    return m_y;
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
    return output << "(" << point.m_x << ", " << point.m_y << ")";
}
