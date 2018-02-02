#include "World.h"

World::World(const Player& my_information, const Player& enemy_information, const Map& attack_map,
             const Map& defence_map, const SharedPtrList<Path>& attack_paths,
             const SharedPtrList<Path>& defence_paths)
        : m_players{my_information, enemy_information}
        , m_maps{attack_map, defence_map}
        , m_paths{attack_paths, defence_paths}
        , m_current_turn(0)
{
}

void World::set_my_information(const Player& my_information) {
    m_players[0] = my_information;
}

const Player& World::get_my_information() const {
    return m_players[0];
}

void World::set_enemy_information(const Player& enemy_information) {
    m_players[1] = enemy_information;
}

const Player& World::get_enemy_information() const {
    return m_players[1];
}

void World::set_attack_map(const Map& attack_map) {
    m_maps[0] = attack_map;
}

const Map& World::get_attack_map() const {
    return m_maps[0];
}

void World::set_defence_map(const Map& defence_map) {
    m_maps[1] = defence_map;
}

const Map& World::get_defence_map() const {
    return m_maps[1];
}

void World::set_attack_map_paths(const SharedPtrList<Path>& attack_paths) {
    m_paths[0] = attack_paths;
}

SharedPtrList<const Path> World::get_attack_map_paths() const {
    return SharedPtrList<const Path>(m_paths[0].begin(), m_paths[0].end());
}

void World::set_defence_map_paths(const SharedPtrList<Path>& defence_paths) {
    m_paths[1] = defence_paths;
}

SharedPtrList<const Path> World::get_defence_map_paths() const {
    return SharedPtrList<const Path>(m_paths[1].begin(), m_paths[1].end());
}

void World::set_current_turn(int current_turn) {
    m_current_turn = current_turn;
}

int World::get_current_turn() const {
    return m_current_turn;
}

SharedPtrList<const Unit> World::get_my_units() const {
    SharedPtrList<const Unit> result;

    for (const auto& cell : get_attack_map().get_cells_list())
        if (const RoadCell* road_cell = dynamic_cast<const RoadCell*>(&cell))
            result.insert(result.end(), road_cell->get_units().begin(), road_cell->get_units().end());

    return result;
}

SharedPtrList<const Unit> World::get_enemy_units() const {
    SharedPtrList<const Unit> result;

    for (const auto& cell : get_defence_map().get_cells_list())
        if (const RoadCell* road_cell = dynamic_cast<const RoadCell*>(&cell))
            result.insert(result.end(), road_cell->get_units().begin(), road_cell->get_units().end());

    return result;
}

SharedPtrList<const Tower> World::get_my_towers() const {
    SharedPtrList<const Tower> result;

    for (const auto& cell : get_defence_map().get_cells_list())
        if (const GrassCell* grass_cell = dynamic_cast<const GrassCell*>(&cell))
            if (grass_cell->get_tower())
                result.push_back(grass_cell->get_tower());

    return result;
}

SharedPtrList<const Tower> World::get_visible_enemy_towers() const {
    SharedPtrList<const Tower> result;

    for (const auto& cell : get_attack_map().get_cells_list())
        if (const GrassCell* grass_cell = dynamic_cast<const GrassCell*>(&cell))
            if (grass_cell->get_tower())
                result.push_back(grass_cell->get_tower());

    return result;
}

void World::set_dead_units_in_this_turn(const SharedPtrList<Unit>& dead_units) {
    m_dead_units = dead_units;
}

SharedPtrList<const Unit> World::get_dead_units_in_this_turn() const {
    return SharedPtrList<const Unit>(m_dead_units.begin(), m_dead_units.end());
}

void World::set_passed_units_in_this_turn(const SharedPtrList<Unit>& passed_units) {
    m_passed_units = passed_units;
}

SharedPtrList<const Unit> World::get_passed_units_in_this_turn() const {
    return SharedPtrList<const Unit>(m_passed_units.begin(), m_passed_units.end());
}

void World::set_destroyed_towers_in_this_turn(const SharedPtrList<Tower>& destroyed_towers) {
    m_destroyed_towers = destroyed_towers;
}

SharedPtrList<const Tower> World::get_destroyed_towers_in_this_turn() const {
    return SharedPtrList<const Tower>(m_destroyed_towers.begin(), m_destroyed_towers.end());
}

void World::set_beans_in_this_turn(const SharedPtrList<BeanEvent>& beans) {
    m_bean_events = beans;
}

SharedPtrList<const BeanEvent> World::get_beans_in_this_turn() const {
    return SharedPtrList<const BeanEvent>(m_bean_events.begin(), m_bean_events.end());
}

void World::set_storms_in_this_turn(const SharedPtrList<StormEvent>& storms) {
    m_storm_events = storms;
}

SharedPtrList<const StormEvent> World::get_storms_in_this_turn() const {
    return SharedPtrList<const StormEvent>(m_storm_events.begin(), m_storm_events.end());
}

void World::create_light_unit(const std::shared_ptr<const Path>& path) {
    // TODO: Implement this
}

void World::create_heavy_unit(const std::shared_ptr<const Path>& path) {
    // TODO: Implement this
}

void World::create_cannon_tower(int level, Point location) {
    // TODO: Implement this
}

void World::create_archer_tower(int level, Point location) {
    // TODO: Implement this
}

void World::upgrade_tower(const std::shared_ptr<const Tower>& tower) {
    // TODO: Implement this
}

void World::plant_bean(Point location) {
    // TODO: Implement this
}

void World::create_storm(Point location) {
    // TODO: Implement this
}

int World::INITIAL_HEALTH = 0;
int World::MAX_TURNS_IN_GAME = 0;
int World::INITIAL_MONEY = 0;
int World::INITIAL_BEANS_COUNT = 0;
int World::INITIAL_STORMS_COUNT = 0;
int World::STORM_RANGE = 0;
