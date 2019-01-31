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

GameConstants InitMessage::parse_gameConstants() {

    GameConstants output_gameConst;

    Json::Value root = Message::get_args()[0];

    Json::Value gameConsts_DATA = root["gameConstants"];

    output_gameConst.killScore() = gameConsts_DATA["killScore"].asInt();
    output_gameConst.objectiveZoneScore() = gameConsts_DATA["objectiveZoneScore"].asInt();
    output_gameConst.timeOut() = gameConsts_DATA["timeout"].asInt();
    output_gameConst.maxAP() = gameConsts_DATA["maxAP"].asInt();
    output_gameConst.maxTurns() = gameConsts_DATA["maxTurns"].asInt();

    return output_gameConst;
}

Map InitMessage::parse_map() {

    Json::Value root = Message::get_args()[0];

    Json::Value map_DATA = root["map"];
    Json::Value cellsList_DATA = map_DATA["cells"];

    std::vector<std::vector<Cell *>> tmpCellLists;

    for(int i = 0; i < cellsList_DATA.size(); ++i){
        std::vector<Cell *> tmpCellRow;
        for(int j = 0; j < cellsList_DATA[i].size(); ++j){
            Cell* cell_ptr = new Cell();
            cell_ptr->isWall() = cellsList_DATA[i][j]["isWall"].asBool();
            cell_ptr->isInMyRespawnZone() = cellsList_DATA[i][j]["isInMyRespawnZone"].asBool();
            cell_ptr->isInOppRespawnZone() = cellsList_DATA[i][j]["isInOppRespawnZone"].asBool();
            cell_ptr->isInObjectiveZone() = cellsList_DATA[i][j]["isInObjectiveZone"].asBool();
            cell_ptr->row() = cellsList_DATA[i][j]["row"].asInt();
            cell_ptr->column() = cellsList_DATA[i][j]["column"].asInt();

            tmpCellRow.push_back(cell_ptr);
        }
        tmpCellLists.push_back(tmpCellRow);
    }

    Map output_map(tmpCellLists);

    output_map.rowNum() = map_DATA["rowNum"].asInt();
    output_map.columnNum() = map_DATA["columnNum"].asInt();

    return output_map;
}

//HeroName InitMessage::give_HeroNameEnum(std::string HeroName) {
//    //TODO Update these based on the HeroName enum
//    if(HeroName == "Ruhollah")
//        return HeroName::HEALER;
//}
//
//AbilityName InitMessage::give_AbilityName(std::string AbilityName) {
//    //TODO Update these based on the AbilityName enum
//    if(AbilityName == "suicide")
//        return AbilityName::suicide;
//
//}

std::vector<HeroConstants *> InitMessage::parse_heroConstants() {
    std::vector<HeroConstants *> output_heroConst;

    Json::Value root = Message::get_args()[0];
    Json::Value HeroConst_DATA = root["heroConstants"];

    for(int i = 0; i < HeroConst_DATA.size(); ++i){
        HeroConstants* ptr_heroCons = new HeroConstants;
        ptr_heroCons->name() = convert_heroName_from_string(HeroConst_DATA[i]["name"].asString());

        Json::Value AbilityNames_DATA = HeroConst_DATA[i]["abilityNames"];
        std::vector<AbilityName> tmp_names;
        for(int j=0; j < AbilityNames_DATA.size(); ++j ){
            tmp_names.push_back(convert_abilityName_from_string(AbilityNames_DATA[j].asString()));
        }
        ptr_heroCons->set_abilityNames(tmp_names);

        ptr_heroCons->maxHP() = HeroConst_DATA[i]["maxAP"].asInt();
        ptr_heroCons->moveAPCost() = HeroConst_DATA[i]["moveAPCost"].asInt();
        ptr_heroCons->remainingRespawnTime() = HeroConst_DATA[i]["respawnTime"].asInt();

        output_heroConst.push_back(ptr_heroCons);
    }

    return output_heroConst;
}

std::vector<AbilityConstants *> InitMessage::parse_abilityConstants() {
    std::vector<AbilityConstants *> output_abilityConst;

    Json::Value root = Message::get_args()[0];
    Json::Value AbilityConst_DATA = root["abilityConstants"];//TODO check if it is NOT abilitiyConstants

    for(int i = 0; i < AbilityConst_DATA.size(); ++i){
        AbilityConstants* ptr_abilityCons = new AbilityConstants();

        ptr_abilityCons->abilityName() = convert_abilityName_from_string(AbilityConst_DATA[i]["name"].asString());
        ptr_abilityCons->type() = convert_abilityType_from_string(AbilityConst_DATA[i]["type"].asString());
        ptr_abilityCons->range() = AbilityConst_DATA[i]["range"].asInt();
        ptr_abilityCons->APCost() = AbilityConst_DATA[i]["APCost"].asInt();
        ptr_abilityCons->cooldown() = AbilityConst_DATA[i]["cooldown"].asInt();
        ptr_abilityCons->areaOfEffect() = AbilityConst_DATA[i]["areaOfEffect"].asInt();
        ptr_abilityCons->power() = AbilityConst_DATA[i]["power"].asInt();
        ptr_abilityCons->isLobbing() = AbilityConst_DATA[i]["isLobbing"].asBool();
        ptr_abilityCons->isPiercing() = AbilityConst_DATA[i]["isPiercing"].asBool();

        output_abilityConst.push_back(ptr_abilityCons);
    }

    return output_abilityConst;
}








