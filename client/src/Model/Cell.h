#ifndef AIC18_CLIENT_CPP_CELL_H
#define AIC18_CLIENT_CPP_CELL_H

#include "Point.h"
#include "Unit.h"
#include "Tower.h"

enum CellType {
    ROAD = 0,
    GRASS = 1,
    BLOCK = 2
};

/**
 * A single cell in game map grid
 */
class Cell {
public:

    Cell() = default;
    virtual ~Cell() = default;

    Cell(const Cell&) = default;
    Cell& operator= (const Cell&) = default;

    Cell(CellType type, Point location);

    void set_type(CellType type);
    CellType get_type() const;

    void set_location(Point location);
    Point get_location() const;

private:

    /// Type of this cell
    CellType m_type;

    /// Location of this cell on game map
    Point m_location;
};

class RoadCell : public Cell {
public:

    RoadCell() = default;

    explicit RoadCell(Point location);

    RoadCell(const RoadCell& other);
    RoadCell& operator=(const RoadCell& other);

    RoadCell(RoadCell&& other) noexcept ;
    RoadCell& operator=(RoadCell&& other) noexcept;

    ~RoadCell() override;

    void set_units(const std::vector<Unit*>& units);
    std::vector<Unit*>& get_units();
    const std::vector<Unit*>& get_units() const;

private:

    void clear_units();

    /// List of units currently on this cell
    std::vector<Unit*> m_units;
};

class GrassCell : public Cell {
public:

    GrassCell();
    explicit GrassCell(Point location);

    GrassCell(const GrassCell& other);
    GrassCell& operator=(const GrassCell& other);

    GrassCell(GrassCell&& other) noexcept;
    GrassCell& operator=(GrassCell&& other) noexcept;

    ~GrassCell() override;

    void set_tower(Tower* tower);
    Tower* get_tower() const;

private:

    void clear_tower();

    /// Pointer to the tower built in this grass cell
    Tower* m_tower;
};

class BlockCell : public Cell {
public:

    BlockCell() = default;
    ~BlockCell() override = default;

    BlockCell(const BlockCell&) = default;
    BlockCell& operator=(const BlockCell&) = default;

    explicit BlockCell(Point location);
};

#endif // AIC18_CLIENT_CPP_CELL_H
