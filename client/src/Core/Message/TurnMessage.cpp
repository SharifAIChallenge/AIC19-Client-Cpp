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

    _game->myScore() = root["myScore"].asInt();
    _game->oppScore() = root["oppScore"].asInt();
    _game->currentPhase() = convert_phase_from_string(root["currentPhase"].asString());
    _game->currentTurn() = root["currentTurn"].asInt();
    //TODO movePhaseNum should be added here

    //map cells:
    std::vector<std::vector<Cell *>> output_map_cells;
    Json::Value& map_cell_DATA = root["map"];

    for(Json::Value& _row : map_cell_DATA){
        std::vector<Cell *> tmp_cell_row;
        for(Json::Value& cell_DATA : _row){
            Cell* ptr_cell = new Cell();

            ptr_cell->isWall() = cell_DATA["isWall"].asBool();
            ptr_cell->isInMyRespawnZone() = cell_DATA["isInMyRespawnZone"].asBool();
            ptr_cell->isInOppRespawnZone() = cell_DATA["isInOppRespawnZone"].asBool();
            ptr_cell->isInObjectiveZone() = cell_DATA["isInObjectiveZone"].asBool();
            ptr_cell->row() = cell_DATA["row"].asInt();
            ptr_cell->column() = cell_DATA["column"].asInt();

            tmp_cell_row.push_back(ptr_cell);
        }
        output_map_cells.push_back(tmp_cell_row);
    }

    _game->map().set_cells(output_map_cells);

//    for(std::vector<Cell *> _row : _game->map().get_cell_2D_vector()){
//        for(Cell * _cell : _row){
//            Logger::Get(LogLevel_DEBUG) << "GOT CELL IN: " << _cell->row() << ", "
//                                                           << _cell->column()
//                                                           << std::endl;
//        }
//    }
    //myHeros:
    std::vector<Hero *> output_heros;

    Json::Value& myHeros_DATA = root["myHeroes"];

    for(int i = 0; i < myHeros_DATA.size(); ++i){
        Json::Value& hero_DATA = myHeros_DATA[i];
        Hero* output_hero = new Hero();

        output_hero->id() = hero_DATA["id"].asInt();
        output_hero->currentHP() = hero_DATA["currentHP"].asInt();
        output_hero->heroConstants().name() = convert_heroName_from_string(hero_DATA["type"].asString());

        //Cooldowns:
        std::vector<Ability *> _abilities_list;
        Json::Value& cooldowns_DATA = hero_DATA["cooldowns"];
        for (int j = 0; j < cooldowns_DATA.size(); ++j){
            AbilityName _ability = convert_abilityName_from_string(cooldowns_DATA[j]["name"].asString());

            Ability* newAbility = new Ability;

            newAbility->abilityConstants() = _game->getAbilityConstants(_ability);
            newAbility->remCooldown() = cooldowns_DATA[j]["remCooldown"].asInt();

            _abilities_list.push_back(newAbility);
        }
        output_hero->set_abilities(_abilities_list);

        //currentCell:
        output_hero->currentCell().row() = hero_DATA["currentCell"]["row"].asInt();
        output_hero->currentCell().column() = hero_DATA["currentCell"]["column"].asInt();

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
        output_hero->set_recentPath(tmp_path);

        //respawnTime:
        output_hero->respawnTime() = hero_DATA["respawnTime"].asInt();

        output_heros.push_back(output_hero);
    }
    _game->set_myHeroes(output_heros);

    //oppHeroes:
    std::vector<Hero *> output_oppHeros;

    Json::Value& oppHeros_DATA = root["oppHeroes"];

    for(int i = 0; i < oppHeros_DATA.size(); ++i){
        Json::Value& hero_DATA = oppHeros_DATA[i];
        Hero* output_hero = new Hero();

        output_hero->id() = hero_DATA["id"].asInt();
        output_hero->currentHP() = hero_DATA["currentHP"].asInt();
        output_hero->heroConstants().name() = convert_heroName_from_string(hero_DATA["type"].asString());

        //Cooldowns:
        std::vector<Ability *> _abilities_list;
        Json::Value& cooldowns_DATA = hero_DATA["cooldowns"];
        for (int j = 0; j < cooldowns_DATA.size(); ++j){
            AbilityName _ability = convert_abilityName_from_string(cooldowns_DATA[j]["name"].asString());

            Ability* newAbility = new Ability;

            newAbility->abilityConstants() = _game->getAbilityConstants(_ability);
            newAbility->remCooldown() = cooldowns_DATA[j]["remCooldown"].asInt();

            _abilities_list.push_back(newAbility);
        }
        output_hero->set_abilities(_abilities_list);

        //currentCell:
        output_hero->currentCell().row() = hero_DATA["currentCell"]["row"].asInt();
        output_hero->currentCell().column() = hero_DATA["currentCell"]["column"].asInt();

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
        output_hero->set_recentPath(tmp_path);

        //respawnTime:
        output_hero->respawnTime() = hero_DATA["respawnTime"].asInt();

        output_oppHeros.push_back(output_hero);
    }
    _game->set_oppHeroes(output_oppHeros);

    //myCastedAbilities:
    std::vector<CastAbility *> output_my_castAbility;

    Json::Value& myCAbility_LIST_DATA = root["myCastedAbilities"];
    for(int i = 0; i < myCAbility_LIST_DATA.size(); ++i){
        Json::Value& myCAbility_DATA = myCAbility_LIST_DATA[i];
        CastAbility* ptr_CastAbility = new CastAbility();

        ptr_CastAbility->casterId() = myCAbility_DATA["casterId"].asInt();
        //targetHeroIds:
        for(int j = 0; j < myCAbility_DATA["targetHeroIds"].size(); ++j) {
            ptr_CastAbility->targetHeroId().push_back(myCAbility_DATA["targetHeroIds"][j].asInt());
        }
        //startCell:
        ptr_CastAbility->startCell() = _game->map().getCell(
                myCAbility_DATA["startCell"]["row"].asInt(),
                myCAbility_DATA["startCell"]["column"].asInt()
            );
        //endCell:
        ptr_CastAbility->startCell() = _game->map().getCell(
                myCAbility_DATA["endCell"]["row"].asInt(),
                myCAbility_DATA["endCell"]["column"].asInt()
        );
        //abilityName:
        ptr_CastAbility->abilityName() = convert_abilityName_from_string(
                myCAbility_DATA["abilityName"].asString());

        output_my_castAbility.push_back(ptr_CastAbility);
    }
    _game->set_myCastAbilities(output_my_castAbility);

    //oppCastedAbilities:
    std::vector<CastAbility *> output_opp_castAbility;

    Json::Value& oppCAbility_LIST_DATA = root["oppCastedAbilities"];
    for(int i = 0; i < oppCAbility_LIST_DATA.size(); ++i){
        Json::Value& oppCAbility_DATA = oppCAbility_LIST_DATA[i];
        CastAbility* ptr_CastAbility = new CastAbility();

        ptr_CastAbility->casterId() = oppCAbility_DATA["casterId"].asInt();
        //targetHeroIds:
        for(int j = 0; j < oppCAbility_DATA["targetHeroIds"].size(); ++j) {
            ptr_CastAbility->targetHeroId().push_back(oppCAbility_DATA["targetHeroIds"][j].asInt());
        }
        //startCell:
        ptr_CastAbility->startCell() = _game->map().getCell(
                oppCAbility_DATA["startCell"]["row"].asInt(),
                oppCAbility_DATA["startCell"]["column"].asInt()
        );
        //endCell:
        ptr_CastAbility->startCell() = _game->map().getCell(
                oppCAbility_DATA["endCell"]["row"].asInt(),
                oppCAbility_DATA["endCell"]["column"].asInt()
        );
        //abilityName:
        ptr_CastAbility->abilityName() = convert_abilityName_from_string(
                oppCAbility_DATA["abilityName"].asString());

        output_opp_castAbility.push_back(ptr_CastAbility);
    }
    _game->set_oppCastAbilities(output_opp_castAbility);

}





