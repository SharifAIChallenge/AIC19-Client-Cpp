#ifndef AIC18_CLIENT_CPP_PATH_H
#define AIC18_CLIENT_CPP_PATH_H

#include "../Core/Utility.h"

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

    Path(int id, const SharedPtrList<RoadCell>& road);

    void set_id(int id);
    int get_id() const;

    void set_road(const SharedPtrList<RoadCell>& road);
    std::vector<RoadCell*> get_road();
    std::vector<const RoadCell*> get_road() const;

private:

    /// Unique id for this path
    int m_id;

    /// List of road cells for this path
    SharedPtrList<RoadCell> m_road;
};

#endif // AIC18_CLIENT_CPP_PATH_H
