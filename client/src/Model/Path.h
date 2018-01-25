#ifndef AIC18_CLIENT_CPP_PATH_H
#define AIC18_CLIENT_CPP_PATH_H

#include <vector>
#include "Point.h"

/**
 * A list of cells that units may pass
 */
class Path {
public:

    Path() = default;
    ~Path() = default;

    Path(const Path&) = default;
    Path& operator= (const Path&) = default;

    void set_road(const std::vector<Point>& road);

    std::vector<Point>& get_road();
    const std::vector<Point>& get_road() const;

private:

    /// List of points for this path
    std::vector<Point> m_road;
};

#endif // AIC18_CLIENT_CPP_PATH_H
