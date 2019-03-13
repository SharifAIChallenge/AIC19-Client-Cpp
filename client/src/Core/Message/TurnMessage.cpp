#include <Utility/Logger.h>
#include "TurnMessage.h"

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

void TurnMessage::update_game(World *_game) {
    Json::Value root = Message::get_args()[0];

    _game->_AP = root["AP"].asInt();
    _game->_myScore = root["myScore"].asInt();
    _game->_oppScore = root["oppScore"].asInt();
    _game->_currentPhase = convert_phase_from_string(root["currentPhase"].asString());
    _game->_currentTurn = root["currentTurn"].asInt();
    _game->_movePhaseNum = root["movePhaseNum"].asInt();
    _game->_maxOvertime = root["maxOvertime"].asInt();
    _game->_remainingOvertime = root["remainingOvertime"].asInt();

    //map cells:
    std::vector<std::vector<Cell *>> output_map_cells;
    Json::Value& map_cell_DATA = root["map"];

    for(Json::Value& _row : map_cell_DATA){
        std::vector<Cell *> tmp_cell_row;
        for(Json::Value& cell_DATA : _row){
            Cell* ptr_cell = new Cell();

            ptr_cell->_isWall = cell_DATA["isWall"].asBool();
            ptr_cell->_isInMyRespawnZone = cell_DATA["isInMyRespawnZone"].asBool();
            ptr_cell->_isInOppRespawnZone = cell_DATA["isInOppRespawnZone"].asBool();
            ptr_cell->_isInObjectiveZone = cell_DATA["isInObjectiveZone"].asBool();
            ptr_cell->_isInVision = cell_DATA["isInVision"].asBool();
            ptr_cell->_row = cell_DATA["row"].asInt();
            ptr_cell->_column = cell_DATA["column"].asInt();

            tmp_cell_row.push_back(ptr_cell);
        }
        output_map_cells.push_back(tmp_cell_row);
    }

    _game->map()._set_cells(output_map_cells);
    for (std::vector<Cell*> row : output_map_cells)
        for(Cell * cell:row)
            delete cell;

//    for(std::vector<Cell *> _row : _game->map().getCells()){
//        for(Cell * _cell : _row){
//            Logger::Get(LogLevel_DEBUG) << "GOT CELL IN: " << _cell->row() << ", "
//                                                           << _cell->column()
//                                                           << std::endl;
//        }
//    }
    //myHeros:
    std::vector<Hero *> output_heros;

    Json::Value& myHeroes_DATA = root["myHeroes"];

    for(int i = 0; i < myHeroes_DATA.size(); ++i){
        Json::Value& hero_DATA = myHeroes_DATA[i];
        Hero* output_hero = new Hero();

        output_hero->_id = hero_DATA["id"].asInt();
        output_hero->_currentHP = hero_DATA["currentHP"].asInt();

        output_hero->_heroConstants = _game->getHeroConstants(
                convert_heroName_from_string(hero_DATA["type"].asString()));

        //Cooldowns:
        std::vector<Ability *> _abilities_list;
        if(hero_DATA.isMember("cooldowns")) {
            Json::Value &cooldowns_DATA = hero_DATA["cooldowns"];
            for (int j = 0; j < cooldowns_DATA.size(); ++j) {
                AbilityName _ability = convert_abilityName_from_string(cooldowns_DATA[j]["name"].asString());

                Ability *newAbility = new Ability;

                newAbility->_abilityConstants = _game->getAbilityConstants(_ability);
                newAbility->_remCooldown = cooldowns_DATA[j]["remCooldown"].asInt();

                _abilities_list.push_back(newAbility);
            }
        } else {
            for(AbilityName abilityName:output_hero->_heroConstants.getAbilityNames()){
                Ability *newAbility = new Ability;

                newAbility->_abilityConstants = _game->getAbilityConstants(abilityName);
                newAbility->_remCooldown = -1;

                _abilities_list.push_back(newAbility);
            }
        }
        output_hero->set_abilities(_abilities_list);
        for(Ability* _ability:_abilities_list){
            delete _ability;
        }

        //currentCell:
        if(hero_DATA.isMember("currentCell")) {
            output_hero->_currentCell = _game->_map.getCell_ptr(hero_DATA["currentCell"]["row"].asInt(),
                                                                 hero_DATA["currentCell"]["column"].asInt());
        } else {
            output_hero->_currentCell = &Cell::NULL_CELL;
        }

        //recentPath:
        std::vector<Cell *> tmp_path;
        Json::Value& recent_path_DATA = hero_DATA["recentPath"];
        for(int j = 0; j < recent_path_DATA.size(); ++j){
            tmp_path.push_back(
                    _game->map().getCell_ptr(
                            recent_path_DATA[j]["row"].asInt(),
                            recent_path_DATA[j]["column"].asInt()
                    )
            );
        }
        output_hero->_recentPath = tmp_path;

        //respawnTime:
        output_hero->_remRespawnTime = hero_DATA["respawnTime"].asInt();

        output_heros.push_back(output_hero);
    }
    _game->set_myHeroes(output_heros);

    //oppHeroes:
    std::vector<Hero *> output_oppHeros;

    Json::Value& oppHeroes_DATA = root["oppHeroes"];

    for(int i = 0; i < oppHeroes_DATA.size(); ++i){
        Json::Value& hero_DATA = oppHeroes_DATA[i];
        Hero* output_hero = new Hero();

        output_hero->_id = hero_DATA["id"].asInt();
        output_hero->_currentHP = hero_DATA["currentHP"].asInt();
        output_hero->_heroConstants = _game->getHeroConstants(
                convert_heroName_from_string(hero_DATA["type"].asString()));

        //Cooldowns:
        std::vector<Ability *> _abilities_list;
        if(hero_DATA.isMember("cooldowns")) {
            Json::Value &cooldowns_DATA = hero_DATA["cooldowns"];
            for (int j = 0; j < cooldowns_DATA.size(); ++j) {
                AbilityName _ability = convert_abilityName_from_string(cooldowns_DATA[j]["name"].asString());

                Ability *newAbility = new Ability;

                newAbility->_abilityConstants = _game->getAbilityConstants(_ability);
                newAbility->_remCooldown = cooldowns_DATA[j]["remCooldown"].asInt();

                _abilities_list.push_back(newAbility);
            }
        } else {
            for(AbilityName abilityName:output_hero->_heroConstants.getAbilityNames()){
                Ability *newAbility = new Ability;

                newAbility->_abilityConstants = _game->getAbilityConstants(abilityName);
                newAbility->_remCooldown = -1;

                _abilities_list.push_back(newAbility);
            }
        }
        output_hero->set_abilities(_abilities_list);
        for(Ability* _ability:_abilities_list){
            delete _ability;
        }

        //currentCell:
        if(hero_DATA.isMember("currentCell")) {
            output_hero->_currentCell = _game->_map.getCell_ptr(hero_DATA["currentCell"]["row"].asInt(),
                                                                 hero_DATA["currentCell"]["column"].asInt());
        } else {
            output_hero->_currentCell = &Cell::NULL_CELL;
        }

        //recentPath:
        std::vector<Cell *> tmp_path;
        Json::Value& recent_path_DATA = hero_DATA["recentPath"];
        for(int j = 0; j < recent_path_DATA.size(); ++j){
            tmp_path.push_back(
                    _game->map().getCell_ptr(
                            recent_path_DATA[j]["row"].asInt(),
                            recent_path_DATA[j]["column"].asInt()
                    )
            );
        }
        output_hero->_recentPath = tmp_path;

        //respawnTime:
        output_hero->_remRespawnTime = hero_DATA["respawnTime"].asInt();

        output_oppHeros.push_back(output_hero);
    }
    _game->set_oppHeroes(output_oppHeros);

    //myCastAbilities:
    std::vector<CastAbility *> output_my_castAbility;

    Json::Value& myCAbility_LIST_DATA = root["myCastAbilities"];
    for(int i = 0; i < myCAbility_LIST_DATA.size(); ++i){
        Json::Value& myCAbility_DATA = myCAbility_LIST_DATA[i];
        CastAbility* ptr_CastAbility = new CastAbility();

        ptr_CastAbility->_casterId = myCAbility_DATA["casterId"].asInt();
        //targetHeroIds:
        for(int j = 0; j < myCAbility_DATA["targetHeroIds"].size(); ++j) {
            ptr_CastAbility->_targetHeroId.push_back(myCAbility_DATA["targetHeroIds"][j].asInt());
        }
        //startCell:
        if(myCAbility_DATA.isMember("startCell")) {
            ptr_CastAbility->_startCell = _game->map().getCell(
                    myCAbility_DATA["startCell"]["row"].asInt(),
                    myCAbility_DATA["startCell"]["column"].asInt()
            );
        } else {
            ptr_CastAbility->_startCell = Cell::NULL_CELL;
        }
        //endCell:
        if(myCAbility_DATA.isMember("endCell")) {
            ptr_CastAbility->_endCell = _game->map().getCell(
                    myCAbility_DATA["endCell"]["row"].asInt(),
                    myCAbility_DATA["endCell"]["column"].asInt()
            );
        } else {
            ptr_CastAbility->_endCell = Cell::NULL_CELL;
        }
        //abilityName:
        ptr_CastAbility->_abilityName = convert_abilityName_from_string(
                myCAbility_DATA["abilityName"].asString());

        output_my_castAbility.push_back(ptr_CastAbility);
    }
    _game->set_myCastAbilities(output_my_castAbility);

    //oppCastAbilities:
    std::vector<CastAbility *> output_opp_castAbility;

    Json::Value& oppCAbility_LIST_DATA = root["oppCastAbilities"];
    for(int i = 0; i < oppCAbility_LIST_DATA.size(); ++i){
        Json::Value& oppCAbility_DATA = oppCAbility_LIST_DATA[i];
        CastAbility* ptr_CastAbility = new CastAbility();

        ptr_CastAbility->_casterId = oppCAbility_DATA["casterId"].asInt();
        //targetHeroIds:
        for(int j = 0; j < oppCAbility_DATA["targetHeroIds"].size(); ++j) {
            ptr_CastAbility->_targetHeroId.push_back(oppCAbility_DATA["targetHeroIds"][j].asInt());
        }
        //startCell:
        if(oppCAbility_DATA.isMember("startCell")) {
            ptr_CastAbility->_startCell = _game->map().getCell(
                    oppCAbility_DATA["startCell"]["row"].asInt(),
                    oppCAbility_DATA["startCell"]["column"].asInt()
            );
        } else {
            ptr_CastAbility->_startCell = Cell::NULL_CELL;
        }
        //endCell:
        if(oppCAbility_DATA.isMember("endCell")) {
            ptr_CastAbility->_endCell = _game->map().getCell(
                    oppCAbility_DATA["endCell"]["row"].asInt(),
                    oppCAbility_DATA["endCell"]["column"].asInt()
            );
        } else {
            ptr_CastAbility->_endCell = Cell::NULL_CELL;
        }
        //abilityName:
        ptr_CastAbility->_abilityName = convert_abilityName_from_string(
                oppCAbility_DATA["abilityName"].asString());

        output_opp_castAbility.push_back(ptr_CastAbility);
    }
    _game->set_oppCastAbilities(output_opp_castAbility);

}





