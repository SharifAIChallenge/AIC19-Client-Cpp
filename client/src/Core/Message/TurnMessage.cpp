#include "TurnMessage.h"

#include "ParseError.h"

#include <algorithm>

#include <Utility/Utility.h>
#include <Utility/Logger.h>


TurnMessage::TurnMessage(Json::Value&& root)
        : Message(std::move(root))
{
    if (Message::get_name() != "turn")
        throw ParseError("Invalid turn message");
}

TurnMessage::TurnMessage(std::string&& json_form)
        : Message(std::move(json_form))
{
    if (Message::get_name() != "turn")
        throw ParseError("Invalid turn message");
}

void TurnMessage::parse_my_units(Map& attack_map, const std::vector<Path*>& paths) {
    Json::Value root = Message::get_args()[0];

    for (Cell* cell : attack_map.get_cells_list())
        if (auto road_cell = dynamic_cast<RoadCell*>(cell))
            road_cell->set_units({});

    int count = 0;
    for (Json::Value& unit_json : root["myunits"]) {
        Unit* unit = nullptr;
        if (unit_json[1].asString() == "l")
            unit = new LightUnit();
        else
            unit = new HeavyUnit();

        unit->set_type(unit_json[1].asString() == "l" ? UnitType::LIGHT : UnitType::HEAVY);
        unit->set_id(unit_json[0].asInt());
        unit->set_level(unit_json[2].asInt());
        unit->set_health(unit_json[3].asInt());
        unit->set_location(Point(unit_json[4]));
        unit->set_path(paths.at(unit_json[6].asUInt()));
        unit->set_owner(Owner::ME);

        RoadCell* road_cell = dynamic_cast<RoadCell*>(attack_map.get_cell(unit->get_location().get_x(),
                                                                          unit->get_location().get_y()));
        road_cell->get_units().push_back(unit);
        ++count;
    }

    Logger::Get(LogLevel_DEBUG) << "My units = " << count << std::endl;
}

void TurnMessage::parse_enemy_units(Map& defence_map, const std::vector<Path*>& paths) {
    Json::Value root = Message::get_args()[0];

    for (Cell* cell : defence_map.get_cells_list())
        if (auto road_cell = dynamic_cast<RoadCell*>(cell))
            road_cell->set_units({});

    int count = 0;
    for (Json::Value& unit_json : root["enemyunits"]) {
        Unit* unit = nullptr;
        if (unit_json[1].asString() == "l")
            unit = new LightUnit();
        else
            unit = new HeavyUnit();

        unit->set_type(unit_json[1].asString() == "l" ? UnitType::LIGHT : UnitType::HEAVY);
        unit->set_id(unit_json[0].asInt());
        unit->set_level(unit_json[2].asInt());
        unit->set_location(Point(unit_json[3]));
        unit->set_owner(Owner::ENEMY);
        unit->set_path(nullptr);

        RoadCell* road_cell = dynamic_cast<RoadCell*>(defence_map.get_cell(unit->get_location().get_x(),
                                                                          unit->get_location().get_y()));
        road_cell->get_units().push_back(unit);
        ++count;
    }

    Logger::Get(LogLevel_DEBUG) << "Enemy units = " << count << std::endl;
}

void TurnMessage::parse_my_towers(Map& defence_map) {
    Json::Value root = Message::get_args()[0];

    for (Cell* cell : defence_map.get_cells_list())
        if (auto grass_cell = dynamic_cast<GrassCell*>(cell))
            grass_cell->set_tower(nullptr);

    int count = 0;
    for (Json::Value& tower_json : root["mytowers"]) {
        Tower* tower = nullptr;
        if (tower_json[1].asString() == "a")
            tower = new ArcherTower();
        else
            tower = new CannonTower();

        tower->set_type(tower_json[1].asString() == "a" ? TowerType::ARCHER : TowerType::CANNON);
        tower->set_id(tower_json[0].asInt());
        tower->set_level(tower_json[2].asInt());
        tower->set_location(Point(tower_json[3]));
        tower->set_price(tower_json[4].asInt());
        tower->set_owner(Owner::ME);

        GrassCell* grass_cell = dynamic_cast<GrassCell*>(defence_map.get_cell(tower->get_location().get_x(),
                                                                              tower->get_location().get_y()));
        if (!grass_cell)
            throw ParseError("Wrong coordinates");
        grass_cell->set_tower(tower);

        ++count;
    }

    Logger::Get(LogLevel_DEBUG) << "My towers = " << count << std::endl;
}

void TurnMessage::parse_enemy_towers(Map& attack_map) {
    Json::Value root = Message::get_args()[0];

    for (Cell* cell : attack_map.get_cells_list())
        if (auto grass_cell = dynamic_cast<GrassCell*>(cell))
            grass_cell->set_tower(nullptr);

    int count = 0;
    for (Json::Value& tower_json : root["enemytowers"]) {
        Tower* tower = nullptr;
        if (tower_json[1].asString() == "a")
            tower = new ArcherTower();
        else
            tower = new CannonTower();

        tower->set_type(tower_json[1].asString() == "a" ? TowerType::ARCHER : TowerType::CANNON);
        tower->set_id(tower_json[0].asInt());
        tower->set_level(tower_json[2].asInt());
        tower->set_location(Point(tower_json[3]));
        tower->set_owner(Owner::ENEMY);

        GrassCell* grass_cell = dynamic_cast<GrassCell*>(attack_map.get_cell(tower->get_location().get_x(),
                                                                              tower->get_location().get_y()));
        if (!grass_cell)
            throw ParseError("Wrong coordinates");
        grass_cell->set_tower(tower);

        ++count;
    }

    Logger::Get(LogLevel_DEBUG) << "Enemy towers = " << count << std::endl;
}

Player TurnMessage::parse_my_information() {
    Json::Value root = Message::get_args()[0];

    Json::Value& player_json = root["players"][0];
    Player result(player_json[0].asInt(), player_json[1].asInt(), player_json[2].asInt(), player_json[3].asInt(),
                  player_json[4].asInt());
    Logger::Get(LogLevel_DEBUG) << "Me: " << result << std::endl;
    return result;
}

Player TurnMessage::parse_enemy_information() {
    Json::Value root = Message::get_args()[0];

    Json::Value& player_json = root["players"][1];
    Player result(player_json[0].asInt(), 0, 0, player_json[1].asInt(), player_json[2].asInt());
    Logger::Get(LogLevel_DEBUG) << "Enemy: " << result << std::endl;
    return result;
}

std::vector<Unit*> TurnMessage::parse_dead_units(World& world) {
    Json::Value root = Message::get_args()[0];

    std::vector<Unit*> my_units = world.get_my_units();
    std::vector<Unit*> enemy_units = world.get_enemy_units();

    std::vector<Unit*> result;
    for (Json::Value& unit_json : root["events"]["deadunits"]) {
        std::vector<Unit*>& units = (unit_json[0].asInt() == 0 ? enemy_units : my_units);
        auto iter = std::find_if(units.begin(), units.end(),
                                 [&](Unit* x) { return x->get_id() == unit_json[1].asInt(); });
        if (iter != units.end())
            result.push_back((*iter)->clone());
    }

    Logger::Get(LogLevel_DEBUG) << "Dead units = " << result.size() << std::endl;

    return result;
}

std::vector<Unit*> TurnMessage::parse_passed_units(World& world) {
    Json::Value root = Message::get_args()[0];

    std::vector<Unit*> my_units = world.get_my_units();
    std::vector<Unit*> enemy_units = world.get_enemy_units();

    std::vector<Unit*> result;
    //std::cout << root["events"]["endofpath"].size();
    for (Json::Value& unit_json : root["events"]["endofpath"]) {
        std::vector<Unit*>& units = (unit_json[0].asInt() == 0 ? enemy_units : my_units);
        auto iter = std::find_if(units.begin(), units.end(),
                                 [&](Unit* x) { return x->get_id() == unit_json[1].asInt(); });
        if (iter != units.end())

            result.push_back((*iter)->clone());
    }

    Logger::Get(LogLevel_DEBUG) << "Passed units = " << result.size() << std::endl;

    //std::cout <<"!3" << std::endl;
    //for (Unit* unit : result){
    //    std::cout << unit->get_id() << unit->get_owner() << std::endl;
    //}
    //std::cout << result.size();
    return result;
}

std::vector<Tower*> TurnMessage::parse_destroyed_towers(World& world) {
    Json::Value root = Message::get_args()[0];

    std::vector<Tower*> my_towers = world.get_my_towers();
    std::vector<Tower*> enemy_towers = world.get_visible_enemy_towers();

    std::vector<Tower*> result;
    for (Json::Value& tower_json : root["events"]["destroyedtowers"]) {
        std::vector<Tower*>& towers = (tower_json[0].asInt() == 1 ? enemy_towers : my_towers);
        auto iter = std::find_if(towers.begin(), towers.end(),
                                 [&](Tower* x) { return x->get_id() == tower_json[1].asInt(); });
        if (iter != towers.end())
            result.push_back((*iter)->clone());
    }

    Logger::Get(LogLevel_DEBUG) << "Destroyed towers = " << result.size() << std::endl;

    return result;
}

std::vector<BeanEvent*> TurnMessage::parse_bean_events() {
    Json::Value root = Message::get_args()[0];

    std::vector<BeanEvent*> result;
    for (Json::Value& bean_json : root["events"]["beans"])
        result.push_back(new BeanEvent(bean_json[0].asInt() == 0 ? Owner::ENEMY : Owner::ME,
                                       Point(bean_json[1])));
    Logger::Get(LogLevel_DEBUG) << "Bean events = " << result.size() << std::endl;
    return result;
}

std::vector<StormEvent*> TurnMessage::parse_storm_events() {
    Json::Value root = Message::get_args()[0];

    std::vector<StormEvent*> result;
    for (Json::Value& storm_json : root["events"]["storms"])
        result.push_back(new StormEvent(storm_json[0].asInt() == 0 ? Owner::ME : Owner::ENEMY,
                                       Point(storm_json[1])));
    Logger::Get(LogLevel_DEBUG) << "Storm events = " << result.size() << std::endl;
    return result;
}
