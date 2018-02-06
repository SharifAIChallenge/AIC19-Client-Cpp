#include "TurnMessage.h"

#include <algorithm>

#include <Utility/Utility.h>
#include <Utility/Logger.h>

#include <Core/ParseError.h>

TurnMessage::TurnMessage(std::string&& string_form)
        : Message(std::move(string_form))
{
    if (m_root["name"] == "shutdown")
        throw ParseError("Received shutdown message");
    m_root = m_root["args"][0];
}

void TurnMessage::parse_my_units(Map& attack_map, const std::vector<Path*>& paths) {
    for (Cell* cell : attack_map.get_cells_list())
        if (auto road_cell = dynamic_cast<RoadCell*>(cell))
            road_cell->set_units({});

    int count = 0;
    for (Json::Value& unit_json : m_root["myunits"]) {
        Unit* unit = nullptr;
        if (unit_json[1].asString() == "l")
            unit = new LightUnit();
        else
            unit = new HeavyUnit();

        unit->set_id(unit_json[0].asInt());
        unit->set_level(unit_json[2].asInt());
        unit->set_health(unit_json[3].asInt());
        unit->set_location(Point(unit_json[4]));
        unit->set_path(paths.at(unit_json[6].asUInt()));

        RoadCell* road_cell = dynamic_cast<RoadCell*>(attack_map.get_cell(unit->get_location().get_x(),
                                                                          unit->get_location().get_y()));
        road_cell->get_units().push_back(unit);
        ++count;
    }

    Logger::Get(DEBUG) << "My units = " << count << std::endl;
}

void TurnMessage::parse_enemy_units(Map& defence_map, const std::vector<Path*>& paths) {
    for (Cell* cell : defence_map.get_cells_list())
        if (auto road_cell = dynamic_cast<RoadCell*>(cell))
            road_cell->set_units({});

    int count = 0;
    for (Json::Value& unit_json : m_root["enemyunits"]) {
        Unit* unit = nullptr;
        if (unit_json[1].asString() == "l")
            unit = new LightUnit();
        else
            unit = new HeavyUnit();

        unit->set_id(unit_json[0].asInt());
        unit->set_level(unit_json[2].asInt());
        unit->set_location(Point(unit_json[3]));
        unit->set_path(nullptr);

        RoadCell* road_cell = dynamic_cast<RoadCell*>(defence_map.get_cell(unit->get_location().get_x(),
                                                                          unit->get_location().get_y()));
        road_cell->get_units().push_back(unit);
        ++count;
    }

    Logger::Get(DEBUG) << "Enemy units = " << count << std::endl;
}

void TurnMessage::parse_my_towers(Map& defence_map) {
    for (Cell* cell : defence_map.get_cells_list())
        if (auto grass_cell = dynamic_cast<GrassCell*>(cell))
            grass_cell->set_tower(nullptr);

    int count = 0;
    for (Json::Value& tower_json : m_root["mytowers"]) {
        Tower* tower = nullptr;
        if (tower_json[1].asString() == "a")
            tower = new ArcherTower();
        else
            tower = new CannonTower();

        tower->set_id(tower_json[0].asInt());
        tower->set_level(tower_json[2].asInt());
        tower->set_location(Point(tower_json[3]));

        GrassCell* grass_cell = dynamic_cast<GrassCell*>(defence_map.get_cell(tower->get_location().get_x(),
                                                                              tower->get_location().get_y()));
        if (!grass_cell)
            throw ParseError("Wrong coordinates");
        grass_cell->set_tower(tower);

        ++count;
    }

    Logger::Get(DEBUG) << "My towers = " << count << std::endl;
}

void TurnMessage::parse_enemy_towers(Map& attack_map) {
    for (Cell* cell : attack_map.get_cells_list())
        if (auto grass_cell = dynamic_cast<GrassCell*>(cell))
            grass_cell->set_tower(nullptr);

    int count = 0;
    for (Json::Value& tower_json : m_root["enemytowers"]) {
        Tower* tower = nullptr;
        if (tower_json[1].asString() == "a")
            tower = new ArcherTower();
        else
            tower = new CannonTower();

        tower->set_id(tower_json[0].asInt());
        tower->set_level(tower_json[2].asInt());
        tower->set_location(Point(tower_json[3]));

        GrassCell* grass_cell = dynamic_cast<GrassCell*>(attack_map.get_cell(tower->get_location().get_x(),
                                                                              tower->get_location().get_y()));
        if (!grass_cell)
            throw ParseError("Wrong coordinates");
        grass_cell->set_tower(tower);

        ++count;
    }

    Logger::Get(DEBUG) << "Enemy towers = " << count << std::endl;
}

Player TurnMessage::parse_my_information() {
    Json::Value& player_json = m_root["players"][0];
    Player result(player_json[0].asInt(), player_json[1].asInt(), player_json[2].asInt(), player_json[3].asInt(),
                  player_json[4].asInt());
    Logger::Get(DEBUG) << "Me: " << result << std::endl;
    return result;
}

Player TurnMessage::parse_enemy_information() {
    Json::Value& player_json = m_root["players"][1];
    Player result(player_json[0].asInt(), 0, 0, player_json[1].asInt(), player_json[2].asInt());
    Logger::Get(DEBUG) << "Enemy: " << result << std::endl;
    return result;
}

std::vector<Unit*> TurnMessage::parse_dead_units(World& world) {
    std::vector<Unit*> my_units = world.get_my_units();
    std::vector<Unit*> enemy_units = world.get_enemy_units();

    std::vector<Unit*> result;
    for (Json::Value& unit_json : m_root["events"]["deadunits"]) {
        std::vector<Unit*>& units = (unit_json[0].asInt() == 0 ? enemy_units : my_units);
        auto iter = std::find_if(units.begin(), units.end(),
                                 [&](auto& x) { return x->get_id() == unit_json[1].asInt(); });
        if (iter != units.end())
            result.push_back(new Unit(**iter));
    }

    Logger::Get(DEBUG) << "Dead units = " << result.size() << std::endl;

    return result;
}

std::vector<Unit*> TurnMessage::parse_passed_units(World& world) {
    std::vector<Unit*> my_units = world.get_my_units();
    std::vector<Unit*> enemy_units = world.get_enemy_units();

    std::vector<Unit*> result;
    for (Json::Value& unit_json : m_root["events"]["endofpath"]) {
        std::vector<Unit*>& units = (unit_json[0].asInt() == 0 ? enemy_units : my_units);
        auto iter = std::find_if(units.begin(), units.end(),
                                 [&](auto& x) { return x->get_id() == unit_json[1].asInt(); });
        if (iter != units.end())
            result.push_back(new Unit(**iter));
    }

    Logger::Get(DEBUG) << "Passed units = " << result.size() << std::endl;

    return result;
}

std::vector<Tower*> TurnMessage::parse_destroyed_towers(World& world) {
    std::vector<Tower*> my_towers = world.get_my_towers();
    std::vector<Tower*> enemy_towers = world.get_visible_enemy_towers();

    std::vector<Tower*> result;
    for (Json::Value& tower_json : m_root["events"]["destroyedtowers"]) {
        std::vector<Tower*>& towers = (tower_json[0].asInt() == 0 ? enemy_towers : my_towers);
        auto iter = std::find_if(towers.begin(), towers.end(),
                                 [&](auto& x) { return x->get_id() == tower_json[1].asInt(); });
        if (iter != towers.end())
            result.push_back(new Tower(**iter));
    }

    Logger::Get(DEBUG) << "Destroyed towers = " << result.size() << std::endl;

    return result;
}

std::vector<BeanEvent*> TurnMessage::parse_bean_events() {
    std::vector<BeanEvent*> result;
    for (Json::Value& bean_json : m_root["events"]["beans"])
        result.push_back(new BeanEvent(bean_json[0].asInt() == 0 ? Owner::ME : Owner::ENEMY,
                                       Point(bean_json[1])));
    Logger::Get(DEBUG) << "Bean events = " << result.size() << std::endl;
    return result;
}

std::vector<StormEvent*> TurnMessage::parse_storm_events() {
    std::vector<StormEvent*> result;
    for (Json::Value& storm_json : m_root["events"]["storms"])
        result.push_back(new StormEvent(storm_json[0].asInt() == 1 ? Owner::ME : Owner::ENEMY,
                                       Point(storm_json[1])));
    Logger::Get(DEBUG) << "Storm events = " << result.size() << std::endl;
    return result;
}
