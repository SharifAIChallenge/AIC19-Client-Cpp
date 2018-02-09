#include "World.h"

#include <Utility/Utility.h>
#include <Utility/Logger.h>

#include <Core/Message/CreateUnitMessage.h>
#include <Core/Message/CreateTowerMessage.h>
#include <Core/Message/UpgradeTowerMessage.h>
#include <Core/Message/PlantBeanMessage.h>
#include <Core/Message/CreateStormMessage.h>

World::World(EventQueue& event_queue)
        : m_event_queue(event_queue)
{
}

World::~World() {
    clear_attack_paths();
    clear_defence_paths();

    clear_dead_units();
    clear_passed_units();
    clear_destroyed_towers();

    clear_bean_events();
    clear_storm_events();
}

void World::set_my_information(const Player& my_information) {
    m_players[0] = my_information;
}

Player& World::get_my_information() {
    return m_players[0];
}

const Player& World::get_my_information() const {
    return m_players[0];
}

void World::set_enemy_information(const Player& enemy_information) {
    m_players[1] = enemy_information;
}

Player& World::get_enemy_information() {
    return m_players[1];
}

const Player& World::get_enemy_information() const {
    return m_players[1];
}

void World::set_attack_map(const Map& attack_map) {
    m_maps[0] = attack_map;
}

Map& World::get_attack_map() {
    return m_maps[0];
}

const Map& World::get_attack_map() const {
    return m_maps[0];
}

void World::set_defence_map(const Map& defence_map) {
    m_maps[1] = defence_map;
}

Map& World::get_defence_map() {
    return m_maps[1];
}

const Map& World::get_defence_map() const {
    return m_maps[1];
}

void World::set_attack_map_paths(const std::vector<Path*>& attack_paths) {
    clear_attack_paths();
    m_paths[0] = attack_paths;
}

std::vector<Path*>& World::get_attack_map_paths() {
    return m_paths[0];
}

const std::vector<Path*>& World::get_attack_map_paths() const {
    return m_paths[0];
}

void World::set_defence_map_paths(const std::vector<Path*>& defence_paths) {
    clear_defence_paths();
    m_paths[1] = defence_paths;
}

std::vector<Path*>& World::get_defence_map_paths() {
    return m_paths[1];
}

const std::vector<Path*>& World::get_defence_map_paths() const {
    return m_paths[1];
}

void World::set_current_turn(int current_turn) {
    m_current_turn = current_turn;
}

int World::get_current_turn() const {
    return m_current_turn;
}

std::vector<Unit*> World::get_my_units() const {
    std::vector<Unit*> result;

    for (Cell* cell : get_attack_map().get_cells_list())
        if (auto road_cell = dynamic_cast<RoadCell*>(cell)) {
            const auto& units = road_cell->get_units();
            result.insert(result.end(), units.begin(), units.end());
        }

    return result;
}

std::vector<Unit*> World::get_enemy_units() const {
    std::vector<Unit*> result;

    for (Cell* cell : get_defence_map().get_cells_list())
        if (auto road_cell = dynamic_cast<RoadCell*>(cell)) {
            const auto& units = road_cell->get_units();
            result.insert(result.end(), units.begin(), units.end());
        }

    return result;
}

std::vector<Tower*> World::get_my_towers() const {
    std::vector<Tower*> result;

    for (Cell* cell : get_defence_map().get_cells_list())
        if (auto grass_cell = dynamic_cast<GrassCell*>(cell))
            if (grass_cell->get_tower())
                result.push_back(grass_cell->get_tower());

    return result;
}

std::vector<Tower*> World::get_visible_enemy_towers() const {
    std::vector<Tower*> result;

    for (Cell* cell : get_attack_map().get_cells_list())
        if (auto grass_cell = dynamic_cast<GrassCell*>(cell))
            if (grass_cell->get_tower())
                result.push_back(grass_cell->get_tower());

    return result;
}

void World::set_dead_units_in_this_turn(const std::vector<Unit*>& dead_units) {
    clear_dead_units();
    m_dead_units = dead_units;
}

std::vector<Unit*>& World::get_dead_units_in_this_turn() {
    return m_dead_units;
}

const std::vector<Unit*>& World::get_dead_units_in_this_turn() const {
    return m_dead_units;
}

void World::set_passed_units_in_this_turn(const std::vector<Unit*>& passed_units) {
    clear_passed_units();
    m_passed_units = passed_units;
}

std::vector<Unit*>& World::get_passed_units_in_this_turn() {
    return m_passed_units;
}

const std::vector<Unit*>& World::get_passed_units_in_this_turn() const {
    return m_passed_units;
}

void World::set_destroyed_towers_in_this_turn(const std::vector<Tower*>& destroyed_towers) {
    clear_destroyed_towers();
    m_destroyed_towers = destroyed_towers;
}

std::vector<Tower*>& World::get_destroyed_towers_in_this_turn() {
    return m_destroyed_towers;
}

const std::vector<Tower*>& World::get_destroyed_towers_in_this_turn() const {
    return m_destroyed_towers;
}

void World::set_beans_in_this_turn(const std::vector<BeanEvent*>& beans) {
    clear_bean_events();
    m_bean_events = beans;
}

std::vector<BeanEvent*>& World::get_beans_in_this_turn() {
    return m_bean_events;
}

const std::vector<BeanEvent*>& World::get_beans_in_this_turn() const {
    return m_bean_events;
}

void World::set_storms_in_this_turn(const std::vector<StormEvent*>& storms) {
    clear_storm_events();
    m_storm_events = storms;
}

std::vector<StormEvent*>& World::get_storms_in_this_turn() {
    return m_storm_events;
}

const std::vector<StormEvent*>& World::get_storms_in_this_turn() const {
    return m_storm_events;
}

void World::create_light_unit(int path_index) {
    Logger::Get(LogLevel_DEBUG) << format_string("create_light_unit(path_index=%d)", path_index) << std::endl;
    m_event_queue.push(CreateUnitMessage(UnitType::LIGHT, path_index));
}

void World::create_heavy_unit(int path_index) {
    Logger::Get(LogLevel_DEBUG) << format_string("create_heavy_unit(path_index=%d)", path_index) << std::endl;
    m_event_queue.push(CreateUnitMessage(UnitType::HEAVY, path_index));
}

void World::create_cannon_tower(int level, int x, int y) {
    Logger::Get(LogLevel_DEBUG) << format_string("create_cannon_tower(level=%d, x=%d, y=%d)", level, x, y) << std::endl;
    m_event_queue.push(CreateTowerMessage(TowerType::CANNON, level, Point(x, y)));
}

void World::create_archer_tower(int level, int x, int y) {
    Logger::Get(LogLevel_DEBUG) << format_string("create_archer_tower(level=%d, x=%d, y=%d)", level, x, y) << std::endl;
    m_event_queue.push(CreateTowerMessage(TowerType::ARCHER, level, Point(x, y)));
}

void World::upgrade_tower(Tower* tower) {
    Logger::Get(LogLevel_DEBUG) << format_string("upgrade_tower(tower_id=%d)", tower->get_id()) << std::endl;
    m_event_queue.push(UpgradeTowerMessage(tower));
}

void World::plant_bean(int x, int y) {
    Logger::Get(LogLevel_DEBUG) << format_string("plant_bean(x=%d, y=%d)", x, y) << std::endl;
    m_event_queue.push(PlantBeanMessage(Point(x, y)));
}

void World::create_storm(int x, int y) {
    Logger::Get(LogLevel_DEBUG) << format_string("create_storm(x=%d, y=%d)", x, y) << std::endl;
    m_event_queue.push(CreateStormMessage(Point(x, y)));
}

int World::INITIAL_HEALTH = 0;
int World::MAX_TURNS_IN_GAME = 0;
int World::INITIAL_MONEY = 0;
int World::INITIAL_BEANS_COUNT = 0;
int World::INITIAL_STORMS_COUNT = 0;
int World::STORM_RANGE = 0;

void World::clear_attack_paths() {
    for (Path* path : m_paths[0])
        delete path;
    m_paths[0].clear();
}

void World::clear_defence_paths() {
    for (Path* path : m_paths[1])
        delete path;
    m_paths[1].clear();
}

void World::clear_bean_events() {
    for (BeanEvent* event : m_bean_events)
        delete event;
    m_bean_events.clear();
}

void World::clear_storm_events() {
    for (StormEvent* event : m_storm_events)
        delete event;
    m_storm_events.clear();
}

void World::clear_dead_units() {
    for (Unit* unit : m_dead_units)
        delete unit;
    m_dead_units.clear();
}

void World::clear_passed_units() {
    for (Unit* unit : m_passed_units)
        delete unit;
    m_passed_units.clear();
}

void World::clear_destroyed_towers() {
    for (Tower* tower : m_destroyed_towers)
        delete tower;
    m_destroyed_towers.clear();
}

bool World::is_tower_constructible(int x, int y) const {
    const int width = get_defence_map().get_width();
    const int height = get_defence_map().get_height();

    auto grass_cell = dynamic_cast<GrassCell*>(get_defence_map().get_cell(x, y));
    if (!grass_cell || grass_cell->get_tower())
        return false;

    if (0 <= x + 1 && x + 1 < width)
        if (auto grass_cell = dynamic_cast<GrassCell*>(get_defence_map().get_cell(x + 1, y)))
            if (grass_cell->get_tower())
                return false;

    if (0 <= x - 1 && x - 1 < width)
        if (auto grass_cell = dynamic_cast<GrassCell*>(get_defence_map().get_cell(x - 1, y)))
            if (grass_cell->get_tower())
                return false;

    if (0 <= y + 1 && y + 1 < height)
        if (auto grass_cell = dynamic_cast<GrassCell*>(get_defence_map().get_cell(x, y + 1)))
            if (grass_cell->get_tower())
                return false;

    if (0 <= y - 1 && y - 1 < height)
        if (auto grass_cell = dynamic_cast<GrassCell*>(get_defence_map().get_cell(x, y - 1)))
            if (grass_cell->get_tower())
                return false;

    return true;
}
