#include <Utility/Logger.h>
#include "InitMessage.h"


InitMessage::InitMessage(Json::Value&& root)
        : Message(std::move(root))
{
    if (Message::get_name() != "init")
        throw ParseError("Invalid init message");
}

InitMessage::InitMessage(std::string&& json_form)
        : Message(std::move(json_form))
{
    if (Message::get_name() != "init")
        throw ParseError("Invalid init message");
}


void InitMessage::update_world(World *_world) {

    Json::Value root = Message::get_args()[0];

    Logger::Get(LogLevel_INFO) << "Starting init Message parse..." << std::endl;

    Json::Value& map_DATA = root["map"];
    Json::Value& cellsList_DATA = map_DATA["cells"];

    std::vector<std::vector<Cell *>> tmpCellLists;

    for(Json::Value& _row : cellsList_DATA){
        std::vector<Cell *> tmpCellRow;
        for(Json::Value& cellsList_DATA : _row){
            tmpCellRow.push_back(new Cell());
            Cell* cell_ptr = tmpCellRow.back();
            cell_ptr->_isWall = cellsList_DATA["isWall"].asBool();
            cell_ptr->_isInMyRespawnZone = cellsList_DATA["isInMyRespawnZone"].asBool();
            cell_ptr->_isInOppRespawnZone = cellsList_DATA["isInOppRespawnZone"].asBool();
            cell_ptr->_isInObjectiveZone = cellsList_DATA["isInObjectiveZone"].asBool();
            cell_ptr->_row = cellsList_DATA["row"].asInt();
            cell_ptr->_column = cellsList_DATA["column"].asInt();

        }
        tmpCellLists.push_back(tmpCellRow);
    }

    _world->_map._rowNum = map_DATA["rowNum"].asInt();
    _world->_map._columnNum = map_DATA["columnNum"].asInt();
    _world->_map._set_cells(tmpCellLists);

    for(std::vector<Cell *> _row : tmpCellLists){
        for(Cell* _cell : _row){
            delete _cell;
        }
    }


    GameConstants output_gameConst;

    Json::Value& gameConsts_DATA = root["gameConstants"];

    output_gameConst._killScore = gameConsts_DATA["killScore"].asInt();
    output_gameConst._objectiveZoneScore = gameConsts_DATA["objectiveZoneScore"].asInt();
    output_gameConst._maxAP = gameConsts_DATA["maxAP"].asInt();
    output_gameConst._maxTurns = gameConsts_DATA["maxTurns"].asInt();
    output_gameConst._preprocessTimeout = gameConsts_DATA["preprocessTimeout"].asInt();
    output_gameConst._firstMoveTimeout = gameConsts_DATA["firstMoveTimeout"].asInt();
    output_gameConst._normalTimeout = gameConsts_DATA["normalTimeout"].asInt();
    output_gameConst._maxScore = gameConsts_DATA["maxScore"].asInt();
    output_gameConst._initOvertime = gameConsts_DATA["initOvertime"].asInt();
    output_gameConst._maxScoreDiff = gameConsts_DATA["maxScoreDiff"].asInt();
    output_gameConst._totalMovePhases = gameConsts_DATA["totalMovePhases"].asInt();

    _world->_gameConstants = output_gameConst;

    Json::Value& HeroConst_DATA = root["heroConstants"];

    for(Json::Value& HeroConst : HeroConst_DATA){
        Json::Value& AbilityNames_DATA = HeroConst["abilityNames"];

        _world->_heroConstants.push_back(new HeroConstants);
        HeroConstants* ptr_heroCons = _world->_heroConstants.back();

        ptr_heroCons->_name = convert_heroName_from_string(HeroConst["name"].asString());

        std::vector<AbilityName> tmp_names;
        for(Json::Value& AbilityName : AbilityNames_DATA){
            tmp_names.push_back(convert_abilityName_from_string(AbilityName.asString()));
        }
        ptr_heroCons->_abilityNames = tmp_names;

        ptr_heroCons->_maxHP = HeroConst["maxHP"].asInt();
        ptr_heroCons->_moveAPCost = HeroConst["moveAPCost"].asInt();
        ptr_heroCons->_remainingRespawnTime = HeroConst["respawnTime"].asInt();

    }

    Json::Value& AbilityConst_DATA = root["abilityConstants"];

    int i = 0;
    for(Json::Value& _abilityConstant : AbilityConst_DATA){
        _world->_abilityConstants.push_back(new AbilityConstants());
        AbilityConstants* ptr_abilityCons = _world->_abilityConstants.back();
//
//        i++;
//
//        for(std::vector<Cell *> _row : _world->get_map().getCells()){
//            for(Cell * _cell : _row){
//                Logger::Get(LogLevel_TRACE) <<i<< "OUT+:: _cell->_row: " << _cell->row()
//                                            << ", " << _cell->column()  << std::endl;
//            }
//        }
        ptr_abilityCons->_abilityName = convert_abilityName_from_string(_abilityConstant["name"].asString());
        ptr_abilityCons->_type = convert_abilityType_from_string(_abilityConstant["type"].asString());
        ptr_abilityCons->_range = _abilityConstant["range"].asInt();
        ptr_abilityCons->_APCost = _abilityConstant["APCost"].asInt();
        ptr_abilityCons->_cooldown = _abilityConstant["cooldown"].asInt();
        ptr_abilityCons->_areaOfEffect = _abilityConstant["areaOfEffect"].asInt();
        ptr_abilityCons->_power = _abilityConstant["power"].asInt();
        ptr_abilityCons->_isLobbing = _abilityConstant["isLobbing"].asBool();
        ptr_abilityCons->_isPiercing = _abilityConstant["isPiercing"].asBool();


//        Logger::Get(LogLevel_INFO) << "\"name\": " << _abilityConstant["name"].asString();
//        Logger::Get(LogLevel_INFO) << "\"isLobbing\": " << _abilityConstant["isLobbing"].asBool() << std::endl;
    }

}








