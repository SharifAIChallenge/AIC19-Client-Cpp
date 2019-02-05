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

//GameConstants InitMessage::parse_gameConstants() {
//
//    GameConstants output_gameConst;
//
//    Json::Value root = Message::get_args()[0];
//
//    Json::Value gameConsts_DATA = root["gameConstants"];
//
//    output_gameConst.killScore() = gameConsts_DATA["killScore"].asInt();
//    output_gameConst.objectiveZoneScore() = gameConsts_DATA["objectiveZoneScore"].asInt();
//    output_gameConst.timeOut() = gameConsts_DATA["timeout"].asInt();
//    output_gameConst.maxAP() = gameConsts_DATA["maxAP"].asInt();
//    output_gameConst.maxTurns() = gameConsts_DATA["maxTurns"].asInt();
//
//    return output_gameConst;
//}
//
//Map InitMessage::parse_map() {
//
//    Json::Value root = Message::get_args()[0];
//
//    Json::Value map_DATA = root["map"];
//    Json::Value cellsList_DATA = map_DATA["cells"];
//
//    std::vector<std::vector<Cell *>> tmpCellLists;
//
//    for(int i = 0; i < cellsList_DATA.size(); ++i){
//        std::vector<Cell *> tmpCellRow;
//        for(int j = 0; j < cellsList_DATA[i].size(); ++j){
//            Cell* cell_ptr = new Cell();
//            cell_ptr->isWall() = cellsList_DATA[i][j]["isWall"].asBool();
//            cell_ptr->isInMyRespawnZone() = cellsList_DATA[i][j]["isInMyRespawnZone"].asBool();
//            cell_ptr->isInOppRespawnZone() = cellsList_DATA[i][j]["isInOppRespawnZone"].asBool();
//            cell_ptr->isInObjectiveZone() = cellsList_DATA[i][j]["isInObjectiveZone"].asBool();
//            cell_ptr->row() = cellsList_DATA[i][j]["row"].asInt();
//            cell_ptr->column() = cellsList_DATA[i][j]["column"].asInt();
//
//            tmpCellRow.push_back(cell_ptr);
//        }
//        tmpCellLists.push_back(tmpCellRow);
//    }
//
//    Map output_map(tmpCellLists);
//
//    for(std::vector<Cell *> _row : tmpCellLists){
//        for(Cell* _cell : _row){
//            delete _cell;
//        }
//    }
//
//
//    output_map.rowNum() = map_DATA["rowNum"].asInt();
//    output_map.columnNum() = map_DATA["columnNum"].asInt();
//
//    return output_map;
//}
//
//
//std::vector<HeroConstants *> InitMessage::parse_heroConstants() {
//    std::vector<HeroConstants *> output_heroConst;
//
//    Json::Value root = Message::get_args()[0];
//    Json::Value HeroConst_DATA = root["heroConstants"];
//
//    for(int i = 0; i < HeroConst_DATA.size(); ++i){
//        HeroConstants* ptr_heroCons = new HeroConstants;
//        ptr_heroCons->name() = convert_heroName_from_string(HeroConst_DATA[i]["name"].asString());
//
//        Json::Value AbilityNames_DATA = HeroConst_DATA[i]["abilityNames"];
//        std::vector<AbilityName> tmp_names;
//        for(int j=0; j < AbilityNames_DATA.size(); ++j ){
//            tmp_names.push_back(convert_abilityName_from_string(AbilityNames_DATA[j].asString()));
//        }
//        ptr_heroCons->set_abilityNames(tmp_names);
//
//        ptr_heroCons->maxHP() = HeroConst_DATA[i]["maxAP"].asInt();
//        ptr_heroCons->moveAPCost() = HeroConst_DATA[i]["moveAPCost"].asInt();
//        ptr_heroCons->remainingRespawnTime() = HeroConst_DATA[i]["respawnTime"].asInt();
//
//        output_heroConst.push_back(ptr_heroCons);
//    }
//
//    return output_heroConst;
//}
//
//std::vector<AbilityConstants *> InitMessage::parse_abilityConstants() {
//    std::vector<AbilityConstants *> output_abilityConst;
//
//    Json::Value root = Message::get_args()[0];
//    Json::Value AbilityConst_DATA = root["abilityConstants"];
//
//    for(int i = 0; i < AbilityConst_DATA.size(); ++i){
//        AbilityConstants* ptr_abilityCons = new AbilityConstants();
//
//        ptr_abilityCons->abilityName() = convert_abilityName_from_string(AbilityConst_DATA[i]["name"].asString());
//        ptr_abilityCons->type() = convert_abilityType_from_string(AbilityConst_DATA[i]["type"].asString());
//        ptr_abilityCons->range() = AbilityConst_DATA[i]["range"].asInt();
//        ptr_abilityCons->APCost() = AbilityConst_DATA[i]["APCost"].asInt();
//        ptr_abilityCons->cooldown() = AbilityConst_DATA[i]["cooldown"].asInt();
//        ptr_abilityCons->areaOfEffect() = AbilityConst_DATA[i]["areaOfEffect"].asInt();
//        ptr_abilityCons->power() = AbilityConst_DATA[i]["power"].asInt();
//        ptr_abilityCons->isLobbing() = AbilityConst_DATA[i]["isLobbing"].asBool();
//        ptr_abilityCons->isPiercing() = AbilityConst_DATA[i]["isPiercing"].asBool();
//
//        output_abilityConst.push_back(ptr_abilityCons);
//    }
//
//    return output_abilityConst;
//}

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
            Cell* cell_ptr = tmpCellRow.back();//TODO cont from here
            cell_ptr->isWall() = cellsList_DATA["isWall"].asBool();
            cell_ptr->isInMyRespawnZone() = cellsList_DATA["isInMyRespawnZone"].asBool();
            cell_ptr->isInOppRespawnZone() = cellsList_DATA["isInOppRespawnZone"].asBool();
            cell_ptr->isInObjectiveZone() = cellsList_DATA["isInObjectiveZone"].asBool();
            cell_ptr->row() = cellsList_DATA["row"].asInt();
            cell_ptr->column() = cellsList_DATA["column"].asInt();

        }
        tmpCellLists.push_back(tmpCellRow);
    }

    _world->_map.rowNum() = map_DATA["rowNum"].asInt();
    _world->_map.columnNum() = map_DATA["columnNum"].asInt();
    _world->_map.set_cells(tmpCellLists);

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

    _world->_gameConstants = output_gameConst;

    Json::Value& HeroConst_DATA = root["heroConstants"];

    for(Json::Value& HeroConst : HeroConst_DATA){
        Json::Value& AbilityNames_DATA = HeroConst["abilityNames"];

        _world->_heroConstants.push_back(new HeroConstants);
        HeroConstants* ptr_heroCons = _world->_heroConstants.back();

        ptr_heroCons->name() = convert_heroName_from_string(HeroConst["name"].asString());

        std::vector<AbilityName> tmp_names;
        for(Json::Value& AbilityName : AbilityNames_DATA){
            tmp_names.push_back(convert_abilityName_from_string(AbilityName.asString()));
        }
        ptr_heroCons->set_abilityNames(tmp_names);

        ptr_heroCons->maxHP() = HeroConst["maxAP"].asInt();
        ptr_heroCons->moveAPCost() = HeroConst["moveAPCost"].asInt();
        ptr_heroCons->remainingRespawnTime() = HeroConst["respawnTime"].asInt();

    }

    Json::Value& AbilityConst_DATA = root["abilityConstants"];

    int i = 0;
    for(Json::Value& _abilityConstant : AbilityConst_DATA){
        _world->_abilityConstants.push_back(new AbilityConstants());
        AbilityConstants* ptr_abilityCons = _world->_abilityConstants.back();
//
//        i++;
//
//        for(std::vector<Cell *> _row : _world->get_map().get_cell_2D_vector()){
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
    }

}








