#include "InitMessage.h"

#include "../../Model/World.h"

InitMessage::InitMessage(std::string&& string_form)
        : Message(std::move(string_form))
{
    m_root = m_root["args"][0];
}

Map InitMessage::parse_map() const {
    size_t width = m_root["map"]["size"][0].asUInt64();
    size_t height = m_root["map"]["size"][1].asUInt64();
    const std::string& map_string = m_root["map"]["cells"].asString();

    std::vector<std::vector<Cell*>> cells(width, std::vector<Cell*>(height, nullptr));
    for (size_t i = 0; i < width; ++i)
        for (size_t j = 0; j < height; ++j) {
            const char& ch = map_string.at(i * width + height);
            if (ch == 'g')
                cells[i][j] = new GrassCell(Point(i, j));
            else if (ch == 'r')
                cells[i][j] = new RoadCell(Point(i, j));
            else
                cells[i][j] = new BlockCell(Point(i, j));
        }

    return Map(cells);
}

std::vector<Path*> InitMessage::parse_paths(const Map& map) {
    std::vector<Path*> result;

    for (Json::Value& path_json : m_root["paths"]) {
        std::vector<const RoadCell*> cells;
        for (Json::Value& point_json : path_json["cells"])
            cells.push_back(dynamic_cast<const RoadCell*>(map.get_cell(
                    point_json["x"].asInt(), point_json["y"].asInt())));

        result.push_back(new Path(cells));
    }

    return result;
}

void InitMessage::parse_world_constants() {
    World::INITIAL_HEALTH = m_root["params"][0].asInt();
    World::INITIAL_MONEY = m_root["params"][1].asInt();
    World::MAX_TURNS_IN_GAME = m_root["params"][2].asInt();
    World::INITIAL_BEANS_COUNT = m_root["params"][3].asInt();
    World::INITIAL_STORMS_COUNT = m_root["params"][4].asInt();
    World::STORM_RANGE = m_root["params"][5].asInt();
}

void InitMessage::parse_unit_constants() {
    Json::Value& light_unit_constants_json = m_root["params"][6][0];
    LightUnit::INITIAL_PRICE = light_unit_constants_json[0].asInt();
    LightUnit::PRICE_INCREASE = light_unit_constants_json[1].asInt();
    LightUnit::INITIAL_HEALTH = light_unit_constants_json[2].asInt();
    LightUnit::HEALTH_COEFF = light_unit_constants_json[3].asDouble();
    LightUnit::INITIAL_BOUNTY = light_unit_constants_json[4].asInt();
    LightUnit::BOUNTY_INCREASE = light_unit_constants_json[5].asInt();
    LightUnit::MOVE_SPEED = light_unit_constants_json[6].asInt();
    LightUnit::DAMAGE = light_unit_constants_json[7].asInt();
    LightUnit::VISION_RANGE = light_unit_constants_json[8].asInt();
    LightUnit::LEVEL_UP_THRESHOLD = light_unit_constants_json[9].asInt();
    LightUnit::ADDED_INCOME = light_unit_constants_json[10].asInt();

    Json::Value& heavy_unit_constants_json = m_root["params"][6][1];
    HeavyUnit::INITIAL_PRICE = heavy_unit_constants_json[0].asInt();
    HeavyUnit::PRICE_INCREASE = heavy_unit_constants_json[1].asInt();
    HeavyUnit::INITIAL_HEALTH = heavy_unit_constants_json[2].asInt();
    HeavyUnit::HEALTH_COEFF = heavy_unit_constants_json[3].asDouble();
    HeavyUnit::INITIAL_BOUNTY = heavy_unit_constants_json[4].asInt();
    HeavyUnit::BOUNTY_INCREASE = heavy_unit_constants_json[5].asInt();
    HeavyUnit::MOVE_SPEED = heavy_unit_constants_json[6].asInt();
    HeavyUnit::DAMAGE = heavy_unit_constants_json[7].asInt();
    HeavyUnit::VISION_RANGE = heavy_unit_constants_json[8].asInt();
    HeavyUnit::LEVEL_UP_THRESHOLD = heavy_unit_constants_json[9].asInt();
    HeavyUnit::ADDED_INCOME = heavy_unit_constants_json[10].asInt();
}

void InitMessage::parse_tower_constants() {
    Json::Value& archer_tower_constants_json = m_root["params"][7][0];
    ArcherTower::INITIAL_PRICE = archer_tower_constants_json[0].asInt();
    ArcherTower::INITIAL_LEVEL_UP_PRICE = archer_tower_constants_json[1].asInt();
    ArcherTower::PRICE_COEFF = archer_tower_constants_json[2].asDouble();
    ArcherTower::INITIAL_DAMAGE = archer_tower_constants_json[3].asInt();
    ArcherTower::DAMAGE_COEFF = archer_tower_constants_json[4].asDouble();
    ArcherTower::ATTACK_SPEED = archer_tower_constants_json[5].asInt();
    ArcherTower::ATTACK_RANGE = archer_tower_constants_json[6].asInt();

    Json::Value& cannon_tower_constants_json = m_root["params"][7][1];
    CannonTower::INITIAL_PRICE = cannon_tower_constants_json[0].asInt();
    CannonTower::INITIAL_LEVEL_UP_PRICE = cannon_tower_constants_json[1].asInt();
    CannonTower::PRICE_COEFF = cannon_tower_constants_json[2].asDouble();
    CannonTower::INITIAL_DAMAGE = cannon_tower_constants_json[3].asInt();
    CannonTower::DAMAGE_COEFF = cannon_tower_constants_json[4].asDouble();
    CannonTower::ATTACK_SPEED = cannon_tower_constants_json[5].asInt();
    CannonTower::ATTACK_RANGE = cannon_tower_constants_json[6].asInt();
}
