#ifndef AIC18_CLIENT_CPP_MAP_H
#define AIC18_CLIENT_CPP_MAP_H

#include <vector>
#include <memory>

#include "Cell.h"
#include "Unit.h"
#include "Tower.h"
#include "Path.h"

/**
 * A 2d grid of @see Cell objects
 */
class Map {
public:

    Map() = default;
    ~Map() = default;

    Map(const Map&) = default;
    Map& operator= (const Map&) = default;

    Map(size_t width, size_t height, const std::vector<Path>& paths);
    Map(const std::vector<std::vector<Cell>>& cells, const std::vector<Path>& paths);

    void set_width(size_t width);
    void set_height(size_t height);
    void set_cells(const std::vector<std::vector<Cell>>& cells);
    void set_my_units(const std::vector<Unit>& my_units);
    void set_enemy_units(const std::vector<Unit>& enemy_units);
    void set_my_towers(const std::vector<Tower>& my_towers);
    void set_visible_enemy_towers(const std::vector<Tower>& visible_enemy_towers);
    void set_paths(const std::vector<Path>& paths);

    size_t get_width() const;
    size_t get_height() const;

    std::vector<std::vector<Cell>>& get_cells();
    const std::vector<std::vector<Cell>>& get_cells() const;

    std::vector<std::shared_ptr<Unit>>& get_my_units();
    std::vector<std::shared_ptr<const Unit>> get_my_units() const;

    std::vector<std::shared_ptr<Unit>>& get_enemy_units();
    std::vector<std::shared_ptr<const Unit>> get_enemy_units() const;

    std::vector<std::shared_ptr<Tower>>& get_my_towers();
    std::vector<std::shared_ptr<const Tower>> get_my_towers() const;

    std::vector<std::shared_ptr<Tower>>& get_visible_enemy_towers();
    std::vector<std::shared_ptr<const Tower>> get_visible_enemy_towers() const;

    std::vector<Path>& get_paths();
    const std::vector<Path>& get_paths() const;

private:

    /// Map dimensions
    size_t m_width , m_height;

    /// The actual cells of the map
    std::vector<std::vector<Cell>> m_cells;

    /// List of my units
    std::vector<std::shared_ptr<Unit>> m_my_units;

    /// List of enemy units
    std::vector<std::shared_ptr<Unit>> m_enemy_units;

    /// List of my towers
    std::vector<std::shared_ptr<Tower>> m_my_towers;

    /// List of enemy towers that are visible in this cycle
    std::vector<std::shared_ptr<Tower>> m_visible_enemy_towers;

    /// List of paths on the game map
    std::vector<Path> m_paths;
};

#endif // AIC18_CLIENT_CPP_MAP_H
