#include "InitMessage.h"

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
    DEBUG("Map width = " << width);

    size_t height = m_root["map"]["size"][1].asUInt64();
    DEBUG("Map height = " << height);

    Json::Value& map_json = m_root["map"]["cells"];

    std::vector<std::vector<Cell*>> cells(width, std::vector<Cell*>(height, nullptr));
    for (size_t i = 0; i < width; ++i) {
        DEBUG(map_json[static_cast<int>(i)].asString());

        for (size_t j = 0; j < height; ++j) {
            const char& ch = map_json[static_cast<int>(i)].asString()[j];
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

    DEBUG("Paths count = " << m_root["paths"].size());

    for (Json::Value& path_json : m_root["paths"]) {
        std::vector<const RoadCell*> cells;
        for (Json::Value& point_json : path_json["cells"]) {
            int x = point_json["x"].asInt();
            int y = point_json["y"].asInt();

            auto cell = map.get_cell(x, y);
            if (!cell)
                throw ParseError("Null-Pointer exception");

            auto road_cell = dynamic_cast<const RoadCell*>(cell);
            if (!road_cell) {
                DEBUG("Cell " << Point(x, y) << " type is " << cell->get_type());
                throw ParseError("Bad coordinates");
            }

            cells.push_back(road_cell);
        }

        result.push_back(new Path(cells));

        DEBUG("Path: " << *result.back());
    }

    return result;
}

void InitMessage::parse_world_constants() {
    World::INITIAL_HEALTH = m_root["params"][0].asInt();
    DEBUG("INITIAL_HEALTH = " << World::INITIAL_HEALTH);

    World::INITIAL_MONEY = m_root["params"][1].asInt();
    DEBUG("INITIAL_MONEY = " << World::INITIAL_MONEY);

    World::MAX_TURNS_IN_GAME = m_root["params"][2].asInt();
    DEBUG("MAX_TURNS_IN_GAME = " << World::MAX_TURNS_IN_GAME);

    World::INITIAL_BEANS_COUNT = m_root["params"][3].asInt();
    DEBUG("INITIAL_BEANS_COUNT = " << World::INITIAL_BEANS_COUNT);

    World::INITIAL_STORMS_COUNT = m_root["params"][4].asInt();
    DEBUG("INITIAL_STORMS_COUNT = " << World::INITIAL_STORMS_COUNT);

    World::STORM_RANGE = m_root["params"][5].asInt();
    DEBUG("STORM_RANGE = " << World::STORM_RANGE);
}

void InitMessage::parse_unit_constants() {
    Json::Value& light_unit_constants_json = m_root["params"][6][0];

    LightUnit::INITIAL_PRICE = light_unit_constants_json[0].asInt();
    DEBUG("LightUnit::INITIAL_PRICE = " << LightUnit::INITIAL_PRICE);

    LightUnit::PRICE_INCREASE = light_unit_constants_json[1].asInt();
    DEBUG("LightUnit::PRICE_INCREASE = " << LightUnit::PRICE_INCREASE);

    LightUnit::INITIAL_HEALTH = light_unit_constants_json[2].asInt();
    DEBUG("LightUnit::INITIAL_HEALTH = " << LightUnit::INITIAL_HEALTH);

    LightUnit::HEALTH_COEFF = light_unit_constants_json[3].asDouble();
    DEBUG("LightUnit::HEALTH_COEFF = " << LightUnit::HEALTH_COEFF);

    LightUnit::INITIAL_BOUNTY = light_unit_constants_json[4].asInt();
    DEBUG("LightUnit::INITIAL_BOUNTY = " << LightUnit::INITIAL_BOUNTY);

    LightUnit::BOUNTY_INCREASE = light_unit_constants_json[5].asInt();
    DEBUG("LightUnit::BOUNTY_INCREASE = " << LightUnit::BOUNTY_INCREASE);

    LightUnit::MOVE_SPEED = light_unit_constants_json[6].asInt();
    DEBUG("LightUnit::MOVE_SPEED = " << LightUnit::MOVE_SPEED);

    LightUnit::DAMAGE = light_unit_constants_json[7].asInt();
    DEBUG("LightUnit::DAMAGE = " << LightUnit::DAMAGE);

    LightUnit::VISION_RANGE = light_unit_constants_json[8].asInt();
    DEBUG("LightUnit::VISION_RANGE = " << LightUnit::VISION_RANGE);

    LightUnit::LEVEL_UP_THRESHOLD = light_unit_constants_json[9].asInt();
    DEBUG("LightUnit::LEVEL_UP_THRESHOLD = " << LightUnit::LEVEL_UP_THRESHOLD);

    LightUnit::ADDED_INCOME = light_unit_constants_json[10].asInt();
    DEBUG("LightUnit::ADDED_INCOME = " << LightUnit::ADDED_INCOME);


    Json::Value& heavy_unit_constants_json = m_root["params"][6][1];

    HeavyUnit::INITIAL_PRICE = heavy_unit_constants_json[0].asInt();
    DEBUG("HeavyUnit::INITIAL_PRICE = " << HeavyUnit::INITIAL_PRICE);

    HeavyUnit::PRICE_INCREASE = heavy_unit_constants_json[1].asInt();
    DEBUG("HeavyUnit::PRICE_INCREASE = " << HeavyUnit::PRICE_INCREASE);

    HeavyUnit::INITIAL_HEALTH = heavy_unit_constants_json[2].asInt();
    DEBUG("HeavyUnit::INITIAL_HEALTH = " << HeavyUnit::INITIAL_HEALTH);

    HeavyUnit::HEALTH_COEFF = heavy_unit_constants_json[3].asDouble();
    DEBUG("HeavyUnit::HEALTH_COEFF = " << HeavyUnit::HEALTH_COEFF);

    HeavyUnit::INITIAL_BOUNTY = heavy_unit_constants_json[4].asInt();
    DEBUG("HeavyUnit::INITIAL_BOUNTY = " << HeavyUnit::INITIAL_BOUNTY);

    HeavyUnit::BOUNTY_INCREASE = heavy_unit_constants_json[5].asInt();
    DEBUG("HeavyUnit::BOUNTY_INCREASE = " << HeavyUnit::BOUNTY_INCREASE);

    HeavyUnit::MOVE_SPEED = heavy_unit_constants_json[6].asInt();
    DEBUG("HeavyUnit::MOVE_SPEED = " << HeavyUnit::MOVE_SPEED);

    HeavyUnit::DAMAGE = heavy_unit_constants_json[7].asInt();
    DEBUG("HeavyUnit::DAMAGE = " << HeavyUnit::DAMAGE);

    HeavyUnit::VISION_RANGE = heavy_unit_constants_json[8].asInt();
    DEBUG("HeavyUnit::VISION_RANGE = " << HeavyUnit::VISION_RANGE);

    HeavyUnit::LEVEL_UP_THRESHOLD = heavy_unit_constants_json[9].asInt();
    DEBUG("HeavyUnit::LEVEL_UP_THRESHOLD = " << HeavyUnit::LEVEL_UP_THRESHOLD);

    HeavyUnit::ADDED_INCOME = heavy_unit_constants_json[10].asInt();
    DEBUG("HeavyUnit::ADDED_INCOME = " << HeavyUnit::ADDED_INCOME);
}

void InitMessage::parse_tower_constants() {
    Json::Value& archer_tower_constants_json = m_root["params"][7][0];

    ArcherTower::INITIAL_PRICE = archer_tower_constants_json[0].asInt();
    DEBUG("ArcherTower::INITIAL_PRICE = " << ArcherTower::INITIAL_PRICE);

    ArcherTower::INITIAL_LEVEL_UP_PRICE = archer_tower_constants_json[1].asInt();
    DEBUG("ArcherTower::INITIAL_LEVEL_UP_PRICE = " << ArcherTower::INITIAL_LEVEL_UP_PRICE);

    ArcherTower::PRICE_COEFF = archer_tower_constants_json[2].asDouble();
    DEBUG("ArcherTower::PRICE_COEFF = " << ArcherTower::PRICE_COEFF);

    ArcherTower::INITIAL_DAMAGE = archer_tower_constants_json[3].asInt();
    DEBUG("ArcherTower::INITIAL_DAMAGE = " << ArcherTower::INITIAL_DAMAGE);

    ArcherTower::DAMAGE_COEFF = archer_tower_constants_json[4].asDouble();
    DEBUG("ArcherTower::DAMAGE_COEFF = " << ArcherTower::DAMAGE_COEFF);

    ArcherTower::ATTACK_SPEED = archer_tower_constants_json[5].asInt();
    DEBUG("ArcherTower::ATTACK_SPEED = " << ArcherTower::ATTACK_SPEED);

    ArcherTower::ATTACK_RANGE = archer_tower_constants_json[6].asInt();
    DEBUG("ArcherTower::ATTACK_RANGE = " << ArcherTower::ATTACK_RANGE);


    Json::Value& cannon_tower_constants_json = m_root["params"][7][1];

    CannonTower::INITIAL_PRICE = cannon_tower_constants_json[0].asInt();
    DEBUG("CannonTower::INITIAL_PRICE = " << CannonTower::INITIAL_PRICE);

    CannonTower::INITIAL_LEVEL_UP_PRICE = cannon_tower_constants_json[1].asInt();
    DEBUG("CannonTower::INITIAL_LEVEL_UP_PRICE = " << CannonTower::INITIAL_LEVEL_UP_PRICE);

    CannonTower::PRICE_COEFF = cannon_tower_constants_json[2].asDouble();
    DEBUG("CannonTower::PRICE_COEFF = " << CannonTower::PRICE_COEFF);

    CannonTower::INITIAL_DAMAGE = cannon_tower_constants_json[3].asInt();
    DEBUG("CannonTower::INITIAL_DAMAGE = " << CannonTower::INITIAL_DAMAGE);

    CannonTower::DAMAGE_COEFF = cannon_tower_constants_json[4].asDouble();
    DEBUG("CannonTower::DAMAGE_COEFF = " << CannonTower::DAMAGE_COEFF);

    CannonTower::ATTACK_SPEED = cannon_tower_constants_json[5].asInt();
    DEBUG("CannonTower::ATTACK_SPEED = " << CannonTower::ATTACK_SPEED);

    CannonTower::ATTACK_RANGE = cannon_tower_constants_json[6].asInt();
    DEBUG("CannonTower::ATTACK_RANGE = " << CannonTower::ATTACK_RANGE);
}
