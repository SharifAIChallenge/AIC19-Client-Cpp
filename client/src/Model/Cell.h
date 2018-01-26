#ifndef AIC18_CLIENT_CPP_CELL_H
#define AIC18_CLIENT_CPP_CELL_H

#include <vector>
#include <memory>

#include "Point.h"
#include "Unit.h"
#include "Tower.h"

/**
 * Type of a map cell
 */
enum class CellType {
    ROAD,
    GRASS,
    BLOCK
};

/**
 * A single cell in game map grid
 */
class Cell {

    using UnitList = std::vector<std::shared_ptr<Unit>>;
    using ConstUnitList = std::vector<std::shared_ptr<const Unit>>;

public:

    Cell() = default;
    ~Cell() = default;

    Cell(const Cell&) = default;
    Cell& operator= (const Cell&) = default;

    Cell(CellType type, Point location);

    void set_type(CellType type);
    void set_location(Point location);

    CellType get_type() const;
    Point get_location() const;

    void set_units(const UnitList& units);
    UnitList& get_units();
    ConstUnitList get_units() const;

    void set_tower(const std::shared_ptr<Tower>& tower);
    bool has_tower() const;
    std::shared_ptr<const Tower> get_tower() const;

private:

    /// The type of this cell
    CellType m_type;

    /// Location of this cell on game map
    Point m_location;

    /// List of units currently located on this cell
    std::vector<std::shared_ptr<Unit>> m_units;

    /// An optional tower that may be built on this cell
    std::shared_ptr<Tower> m_tower;
};

#endif // AIC18_CLIENT_CPP_CELL_H
