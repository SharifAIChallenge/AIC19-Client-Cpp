#ifndef AIC18_CLIENT_CPP_CELL_H
#define AIC18_CLIENT_CPP_CELL_H

#include "../Core/Utility.h"
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
    ~RoadCell() override = default;

    RoadCell(const RoadCell&) = default;
    RoadCell& operator=(const RoadCell&) = default;

    explicit RoadCell(Point location);

    void set_units(const SharedPtrList<Unit>& units);
    std::vector<Unit*> get_units();
    std::vector<const Unit*> get_units() const;

private:

    /// List of units currently on this cell
    SharedPtrList<Unit> m_units;
};

class GrassCell : public Cell {
public:

    GrassCell() = default;
    ~GrassCell() override = default;

    GrassCell(const GrassCell&) = default;
    GrassCell& operator=(const GrassCell&) = default;

    explicit GrassCell(Point location);

    void set_tower(const std::shared_ptr<Tower>& tower);
    Tower* get_tower();
    const Tower* get_tower() const;

private:

    /// Pointer to the tower built in this grass cell
    std::shared_ptr<Tower> m_tower;
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
