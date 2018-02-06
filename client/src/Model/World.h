#ifndef AIC18_CLIENT_CPP_WORLD_H
#define AIC18_CLIENT_CPP_WORLD_H

#include <vector>

#include <Core/EventQueue.h>

#include "Player.h"
#include "Unit.h"
#include "Tower.h"
#include "Map.h"
#include "Path.h"
#include "GameEvent.h"

class World final {
public:

    World(const World&) = delete;
    World& operator=(const World&) = delete;

    explicit World(EventQueue& event_queue);

    ~World();

    // Member setter/getters:

    void set_my_information(const Player& my_information);
    Player& get_my_information();
    const Player& get_my_information() const;

    void set_enemy_information(const Player& enemy_information);
    Player& get_enemy_information();
    const Player& get_enemy_information() const;

    void set_attack_map(const Map& attack_map);
    Map& get_attack_map();
    const Map& get_attack_map() const;

    void set_defence_map(const Map& defence_map);
    Map& get_defence_map();
    const Map& get_defence_map() const;

    void set_attack_map_paths(const std::vector<Path*>& attack_paths);
    std::vector<Path*>& get_attack_map_paths();
    const std::vector<Path*>& get_attack_map_paths() const;

    void set_defence_map_paths(const std::vector<Path*>& defence_paths);
    std::vector<Path*>& get_defence_map_paths();
    const std::vector<Path*>& get_defence_map_paths() const;

    void set_current_turn(int current_turn);
    int get_current_turn() const;

    // Computational getters:

    std::vector<Unit*> get_my_units() const;
    std::vector<Unit*> get_enemy_units() const;

    std::vector<Tower*> get_my_towers() const;
    std::vector<Tower*> get_visible_enemy_towers() const;

    bool is_tower_constructible(int x, int y) const;

    // Events:

    void set_dead_units_in_this_turn(const std::vector<Unit*>& dead_units);
    std::vector<Unit*>& get_dead_units_in_this_turn();
    const std::vector<Unit*>& get_dead_units_in_this_turn() const;

    void set_passed_units_in_this_turn(const std::vector<Unit*>& passed_units);
    std::vector<Unit*>& get_passed_units_in_this_turn();
    const std::vector<Unit*>& get_passed_units_in_this_turn() const;

    void set_destroyed_towers_in_this_turn(const std::vector<Tower*>& destroyed_towers);
    std::vector<Tower*>& get_destroyed_towers_in_this_turn();
    const std::vector<Tower*>& get_destroyed_towers_in_this_turn() const;

    void set_beans_in_this_turn(const std::vector<BeanEvent*>& beans);
    std::vector<BeanEvent*>& get_beans_in_this_turn();
    const std::vector<BeanEvent*>& get_beans_in_this_turn() const;

    void set_storms_in_this_turn(const std::vector<StormEvent*>& storms);
    std::vector<StormEvent*>& get_storms_in_this_turn();
    const std::vector<StormEvent*>& get_storms_in_this_turn() const;

    // Actions:

    void create_light_unit(int path_index);
    void create_heavy_unit(int path_index);

    void create_cannon_tower(int level, int x, int y);
    void create_archer_tower(int level, int x, int y);

    void upgrade_tower(Tower* tower);

    void plant_bean(int x, int y);
    void create_storm(int x, int y);

    // Constants:

    static int INITIAL_HEALTH;
    static int MAX_TURNS_IN_GAME;
    static int INITIAL_MONEY;
    static int INITIAL_BEANS_COUNT;
    static int INITIAL_STORMS_COUNT;
    static int STORM_RANGE;

private:

    void clear_attack_paths();
    void clear_defence_paths();

    void clear_dead_units();
    void clear_passed_units();
    void clear_destroyed_towers();

    void clear_bean_events();
    void clear_storm_events();

    Player m_players[2];
    Map m_maps[2];
    std::vector<Path*> m_paths[2];

    int m_current_turn;

    std::vector<Unit*> m_dead_units;
    std::vector<Unit*> m_passed_units;

    std::vector<Tower*> m_destroyed_towers;

    std::vector<BeanEvent*> m_bean_events;
    std::vector<StormEvent*> m_storm_events;

    EventQueue& m_event_queue;
};

#endif // AIC18_CLIENT_CPP_WORLD_H
