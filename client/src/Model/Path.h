#ifndef AIC18_CLIENT_CPP_PATH_H
#define AIC18_CLIENT_CPP_PATH_H

#include <vector>

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

    Path(int id, const std::vector<RoadCell*>& road);

    void set_id(int id);
    int get_id() const;

    void set_road(const std::vector<RoadCell*>& road);
    const std::vector<RoadCell*>& get_road();
    std::vector<const RoadCell*> get_road() const;

private:

    /// Unique id for this path
    int m_id;

    /// List of road cells for this path
    std::vector<RoadCell*> m_road;
};

#endif // AIC18_CLIENT_CPP_PATH_H
