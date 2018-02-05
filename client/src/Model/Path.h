#ifndef AIC18_CLIENT_CPP_PATH_H
#define AIC18_CLIENT_CPP_PATH_H

#include <vector>
#include <iostream>

class RoadCell;

/**
 * A list of road cells that units may pass
 */
class Path {
public:

    Path() = default;
    ~Path() = default;

    Path(const Path&) = default;
    Path& operator= (const Path&) = default;

    explicit Path(const std::vector<RoadCell*>& road);

    void set_road(const std::vector<RoadCell*>& road);
    std::vector<RoadCell*>& get_road();
    const std::vector<RoadCell*>& get_road() const;

    friend std::ostream& operator<< (std::ostream& output, const Path& path);

private:

    /// List of road cells for this path
    std::vector<RoadCell*> m_road;
};

#endif // AIC18_CLIENT_CPP_PATH_H
