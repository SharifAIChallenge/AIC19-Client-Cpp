#include "InitMessage.h"

#include <Utility/Logger.h>
#include "../../Model/World.h"
#include "../../Utility.h"
#include "../ParseError.h"

InitMessage::InitMessage(std::string&& string_form)
        : Message(std::move(string_form))
{
    m_root = m_root["args"][0];
}

Map InitMessage::parse_map() {
    size_t width = m_root["map"]["size"][0].asUInt64();
    size_t height = m_root["map"]["size"][1].asUInt64();
    Logger::Get(DEBUG) << "Map dimensions are " << Point(width, height) << std::endl;

    Json::Value& map_json = m_root["map"]["cells"];

    std::vector<std::vector<Cell*>> cells(width, std::vector<Cell*>(height, nullptr));
    for (size_t i = 0; i < width; ++i) {
        Logger::Get(DEBUG) << map_json[static_cast<int>(i)].asString() << std::endl;

        for (size_t j = 0; j < height; ++j) {
            char ch = map_json[static_cast<int>(i)].asString()[j];
            if (ch == 'g')
                cells[i][j] = new GrassCell(Point(i, j));
            else if (ch == 'r')
                cells[i][j] = new RoadCell(Point(i, j));
            else
                cells[i][j] = new BlockCell(Point(i, j));
        }
    }

    return Map(rotate_grid(cells));
}

std::vector<Path*> InitMessage::parse_paths(const Map& map) {
    std::vector<Path*> result;

    Logger::Get(DEBUG) << "Paths count = " << m_root["paths"].size() << std::endl;

    for (Json::Value& path_json : m_root["paths"]) {
        std::vector<RoadCell*> cells;
        for (Json::Value& point_json : path_json["cells"]) {
            int x = point_json["x"].asInt();
            int y = point_json["y"].asInt();

            auto cell = map.get_cell(x, y);
            if (!cell) {
                Logger::Get(DEBUG) << "Cell " << Point(x, y) << " does not exist" << std::endl;
                throw ParseError("Null-Pointer exception");
            }

            auto road_cell = dynamic_cast<RoadCell*>(cell);
            if (!road_cell) {
                Logger::Get(DEBUG) << "Cell " << Point(x, y) << " type is " << cell->get_type() << std::endl;
                throw ParseError("Bad coordinates");
            }

            cells.push_back(road_cell);
        }

        result.push_back(new Path(cells));

        Logger::Get(DEBUG) << "Path: " << *result.back() << std::endl;
    }

    return result;
}

void InitMessage::parse_world_constants() {
    World::INITIAL_HEALTH = m_root["params"][0].asInt();
    Logger::Get(DEBUG) << "INITIAL_HEALTH = " << World::INITIAL_HEALTH << std::endl;

    World::INITIAL_MONEY = m_root["params"][1].asInt();
    Logger::Get(DEBUG) << "INITIAL_MONEY = " << World::INITIAL_MONEY << std::endl;

    World::MAX_TURNS_IN_GAME = m_root["params"][2].asInt();
    Logger::Get(DEBUG) << "MAX_TURNS_IN_GAME = " << World::MAX_TURNS_IN_GAME << std::endl;

    World::INITIAL_BEANS_COUNT = m_root["params"][3].asInt();
    Logger::Get(DEBUG) << "INITIAL_BEANS_COUNT = " << World::INITIAL_BEANS_COUNT << std::endl;

    World::INITIAL_STORMS_COUNT = m_root["params"][4].asInt();
    Logger::Get(DEBUG) << "INITIAL_STORMS_COUNT = " << World::INITIAL_STORMS_COUNT << std::endl;

    World::STORM_RANGE = m_root["params"][5].asInt();
    Logger::Get(DEBUG) << "STORM_RANGE = " << World::STORM_RANGE << std::endl;
}

void InitMessage::parse_unit_constants() {
    Json::Value& light_unit_constants_json = m_root["params"][6][0];

    LightUnit::INITIAL_PRICE = light_unit_constants_json[0].asInt();
    Logger::Get(DEBUG) << "LightUnit::INITIAL_PRICE = " << LightUnit::INITIAL_PRICE << std::endl;

    LightUnit::PRICE_INCREASE = light_unit_constants_json[1].asInt();
    Logger::Get(DEBUG) << "LightUnit::PRICE_INCREASE = " << LightUnit::PRICE_INCREASE << std::endl;

    LightUnit::INITIAL_HEALTH = light_unit_constants_json[2].asInt();
    Logger::Get(DEBUG) << "LightUnit::INITIAL_HEALTH = " << LightUnit::INITIAL_HEALTH << std::endl;

    LightUnit::HEALTH_COEFF = light_unit_constants_json[3].asDouble();
    Logger::Get(DEBUG) << "LightUnit::HEALTH_COEFF = " << LightUnit::HEALTH_COEFF << std::endl;

    LightUnit::INITIAL_BOUNTY = light_unit_constants_json[4].asInt();
    Logger::Get(DEBUG) << "LightUnit::INITIAL_BOUNTY = " << LightUnit::INITIAL_BOUNTY << std::endl;

    LightUnit::BOUNTY_INCREASE = light_unit_constants_json[5].asInt();
    Logger::Get(DEBUG) << "LightUnit::BOUNTY_INCREASE = " << LightUnit::BOUNTY_INCREASE << std::endl;

    LightUnit::MOVE_SPEED = light_unit_constants_json[6].asInt();
    Logger::Get(DEBUG) << "LightUnit::MOVE_SPEED = " << LightUnit::MOVE_SPEED << std::endl;

    LightUnit::DAMAGE = light_unit_constants_json[7].asInt();
    Logger::Get(DEBUG) << "LightUnit::DAMAGE = " << LightUnit::DAMAGE << std::endl;

    LightUnit::VISION_RANGE = light_unit_constants_json[8].asInt();
    Logger::Get(DEBUG) << "LightUnit::VISION_RANGE = " << LightUnit::VISION_RANGE << std::endl;

    LightUnit::LEVEL_UP_THRESHOLD = light_unit_constants_json[9].asInt();
    Logger::Get(DEBUG) << "LightUnit::LEVEL_UP_THRESHOLD = " << LightUnit::LEVEL_UP_THRESHOLD << std::endl;

    LightUnit::ADDED_INCOME = light_unit_constants_json[10].asInt();
    Logger::Get(DEBUG) << "LightUnit::ADDED_INCOME = " << LightUnit::ADDED_INCOME << std::endl;


    Json::Value& heavy_unit_constants_json = m_root["params"][6][1];

    HeavyUnit::INITIAL_PRICE = heavy_unit_constants_json[0].asInt();
    Logger::Get(DEBUG) << "HeavyUnit::INITIAL_PRICE = " << HeavyUnit::INITIAL_PRICE << std::endl;

    HeavyUnit::PRICE_INCREASE = heavy_unit_constants_json[1].asInt();
    Logger::Get(DEBUG) << "HeavyUnit::PRICE_INCREASE = " << HeavyUnit::PRICE_INCREASE << std::endl;

    HeavyUnit::INITIAL_HEALTH = heavy_unit_constants_json[2].asInt();
    Logger::Get(DEBUG) << "HeavyUnit::INITIAL_HEALTH = " << HeavyUnit::INITIAL_HEALTH << std::endl;

    HeavyUnit::HEALTH_COEFF = heavy_unit_constants_json[3].asDouble();
    Logger::Get(DEBUG) << "HeavyUnit::HEALTH_COEFF = " << HeavyUnit::HEALTH_COEFF << std::endl;

    HeavyUnit::INITIAL_BOUNTY = heavy_unit_constants_json[4].asInt();
    Logger::Get(DEBUG) << "HeavyUnit::INITIAL_BOUNTY = " << HeavyUnit::INITIAL_BOUNTY << std::endl;

    HeavyUnit::BOUNTY_INCREASE = heavy_unit_constants_json[5].asInt();
    Logger::Get(DEBUG) << "HeavyUnit::BOUNTY_INCREASE = " << HeavyUnit::BOUNTY_INCREASE << std::endl;

    HeavyUnit::MOVE_SPEED = heavy_unit_constants_json[6].asInt();
    Logger::Get(DEBUG) << "HeavyUnit::MOVE_SPEED = " << HeavyUnit::MOVE_SPEED << std::endl;

    HeavyUnit::DAMAGE = heavy_unit_constants_json[7].asInt();
    Logger::Get(DEBUG) << "HeavyUnit::DAMAGE = " << HeavyUnit::DAMAGE << std::endl;

    HeavyUnit::VISION_RANGE = heavy_unit_constants_json[8].asInt();
    Logger::Get(DEBUG) << "HeavyUnit::VISION_RANGE = " << HeavyUnit::VISION_RANGE << std::endl;

    HeavyUnit::LEVEL_UP_THRESHOLD = heavy_unit_constants_json[9].asInt();
    Logger::Get(DEBUG) << "HeavyUnit::LEVEL_UP_THRESHOLD = " << HeavyUnit::LEVEL_UP_THRESHOLD << std::endl;

    HeavyUnit::ADDED_INCOME = heavy_unit_constants_json[10].asInt();
    Logger::Get(DEBUG) << "HeavyUnit::ADDED_INCOME = " << HeavyUnit::ADDED_INCOME << std::endl;
}

void InitMessage::parse_tower_constants() {
    Json::Value& archer_tower_constants_json = m_root["params"][7][0];

    ArcherTower::INITIAL_PRICE = archer_tower_constants_json[0].asInt();
    Logger::Get(DEBUG) << "ArcherTower::INITIAL_PRICE = " << ArcherTower::INITIAL_PRICE << std::endl;

    ArcherTower::INITIAL_LEVEL_UP_PRICE = archer_tower_constants_json[1].asInt();
    Logger::Get(DEBUG) << "ArcherTower::INITIAL_LEVEL_UP_PRICE = " << ArcherTower::INITIAL_LEVEL_UP_PRICE << std::endl;

    ArcherTower::PRICE_COEFF = archer_tower_constants_json[2].asDouble();
    Logger::Get(DEBUG) << "ArcherTower::PRICE_COEFF = " << ArcherTower::PRICE_COEFF << std::endl;

    ArcherTower::INITIAL_DAMAGE = archer_tower_constants_json[3].asInt();
    Logger::Get(DEBUG) << "ArcherTower::INITIAL_DAMAGE = " << ArcherTower::INITIAL_DAMAGE << std::endl;

    ArcherTower::DAMAGE_COEFF = archer_tower_constants_json[4].asDouble();
    Logger::Get(DEBUG) << "ArcherTower::DAMAGE_COEFF = " << ArcherTower::DAMAGE_COEFF << std::endl;

    ArcherTower::ATTACK_SPEED = archer_tower_constants_json[5].asInt();
    Logger::Get(DEBUG) << "ArcherTower::ATTACK_SPEED = " << ArcherTower::ATTACK_SPEED << std::endl;

    ArcherTower::ATTACK_RANGE = archer_tower_constants_json[6].asInt();
    Logger::Get(DEBUG) << "ArcherTower::ATTACK_RANGE = " << ArcherTower::ATTACK_RANGE << std::endl;


    Json::Value& cannon_tower_constants_json = m_root["params"][7][1];

    CannonTower::INITIAL_PRICE = cannon_tower_constants_json[0].asInt();
    Logger::Get(DEBUG) << "CannonTower::INITIAL_PRICE = " << CannonTower::INITIAL_PRICE << std::endl;

    CannonTower::INITIAL_LEVEL_UP_PRICE = cannon_tower_constants_json[1].asInt();
    Logger::Get(DEBUG) << "CannonTower::INITIAL_LEVEL_UP_PRICE = " << CannonTower::INITIAL_LEVEL_UP_PRICE << std::endl;

    CannonTower::PRICE_COEFF = cannon_tower_constants_json[2].asDouble();
    Logger::Get(DEBUG) << "CannonTower::PRICE_COEFF = " << CannonTower::PRICE_COEFF << std::endl;

    CannonTower::INITIAL_DAMAGE = cannon_tower_constants_json[3].asInt();
    Logger::Get(DEBUG) << "CannonTower::INITIAL_DAMAGE = " << CannonTower::INITIAL_DAMAGE << std::endl;

    CannonTower::DAMAGE_COEFF = cannon_tower_constants_json[4].asDouble();
    Logger::Get(DEBUG) << "CannonTower::DAMAGE_COEFF = " << CannonTower::DAMAGE_COEFF << std::endl;

    CannonTower::ATTACK_SPEED = cannon_tower_constants_json[5].asInt();
    Logger::Get(DEBUG) << "CannonTower::ATTACK_SPEED = " << CannonTower::ATTACK_SPEED << std::endl;

    CannonTower::ATTACK_RANGE = cannon_tower_constants_json[6].asInt();
    Logger::Get(DEBUG) << "CannonTower::ATTACK_RANGE = " << CannonTower::ATTACK_RANGE << std::endl;
}
