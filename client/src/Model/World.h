#ifndef AIC18_CLIENT_CPP_WORLD_H
#define AIC18_CLIENT_CPP_WORLD_H

#include "../Core/Utility.h"
#include "../Core/EventQueue.h"

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

    World(EventQueue& event_queue, const Player& my_information, const Player& enemy_information, const Map& attack_map,
          const Map& defence_map, const SharedPtrList<Path>& attack_paths, const SharedPtrList<Path>& defence_paths);

    ~World() = default;

    // Member setter/getters:

    void set_my_information(const Player& my_information);
    const Player& get_my_information() const;

    void set_enemy_information(const Player& enemy_information);
    const Player& get_enemy_information() const;

    void set_attack_map(const Map& attack_map);
    const Map& get_attack_map() const;

    void set_defence_map(const Map& defence_map);
    const Map& get_defence_map() const;

    void set_attack_map_paths(const SharedPtrList<Path>& attack_paths);
    std::vector<const Path*> get_attack_map_paths() const;

    void set_defence_map_paths(const SharedPtrList<Path>& defence_paths);
    std::vector<const Path*> get_defence_map_paths() const;

    void set_current_turn(int current_turn);
    int get_current_turn() const;

    // Computational getters:

    std::vector<const Unit*> get_my_units() const;
    std::vector<const Unit*> get_enemy_units() const;

    std::vector<const Tower*> get_my_towers() const;
    std::vector<const Tower*> get_visible_enemy_towers() const;

    // Events:

    void set_dead_units_in_this_turn(const SharedPtrList<Unit>& dead_units);
    std::vector<const Unit*> get_dead_units_in_this_turn() const;

    void set_passed_units_in_this_turn(const SharedPtrList<Unit>& passed_units);
    std::vector<const Unit*> get_passed_units_in_this_turn() const;

    void set_destroyed_towers_in_this_turn(const SharedPtrList<Tower>& destroyed_towers);
    std::vector<const Tower*> get_destroyed_towers_in_this_turn() const;

    void set_beans_in_this_turn(const SharedPtrList<BeanEvent>& beans);
    std::vector<const BeanEvent*> get_beans_in_this_turn() const;

    void set_storms_in_this_turn(const SharedPtrList<StormEvent>& storms);
    std::vector<const StormEvent*> get_storms_in_this_turn() const;

    // Actions:

    void create_light_unit(const std::shared_ptr<const Path>& path);
    void create_heavy_unit(const std::shared_ptr<const Path>& path);

    void create_cannon_tower(int level, Point location);
    void create_archer_tower(int level, Point location);

    void upgrade_tower(const std::shared_ptr<const Tower>& tower);

    void plant_bean(Point location);
    void create_storm(Point location);

    // Constants:

    static int INITIAL_HEALTH;
    static int MAX_TURNS_IN_GAME;
    static int INITIAL_MONEY;
    static int INITIAL_BEANS_COUNT;
    static int INITIAL_STORMS_COUNT;
    static int STORM_RANGE;

private:

    Player m_players[2];
    Map m_maps[2];
    SharedPtrList<Path> m_paths[2];

    int m_current_turn;

    SharedPtrList<Unit> m_dead_units;
    SharedPtrList<Unit> m_passed_units;

    SharedPtrList<Tower> m_destroyed_towers;

    SharedPtrList<BeanEvent> m_bean_events;
    SharedPtrList<StormEvent> m_storm_events;

    EventQueue& m_event_queue;
};

#endif // AIC18_CLIENT_CPP_WORLD_H
