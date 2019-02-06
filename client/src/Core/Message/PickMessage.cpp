#include <Utility/Logger.h>
#include "PickMessage.h"

PickMessage::PickMessage(Json::Value&& root)
        : Message(std::move(root))
{
    if (Message::get_name() != "pick")
        throw ParseError("Invalid pick message");
}

PickMessage::PickMessage(std::string&& json_form)
        : Message(std::move(json_form))
{
    if (Message::get_name() != "pick")
        throw ParseError("Invalid pick message");
}

void PickMessage::update_game(World* _game) {
    Json::Value root = Message::get_args()[0];

//    Logger::Get(LogLevel_INFO) << "getting root" << std::endl;
    //myHeroes:
    std::vector<Hero *> tmp_my_hero_list;
    Json::Value myHero_DATA = root["myHeroes"];
//    Logger::Get(LogLevel_INFO) << "myHero_DATA.size() " << myHero_DATA.size() << std::endl;
    for(int i = 0; i < myHero_DATA.size(); ++i){
        Hero* ptr_hero = new Hero();
//        Logger::Get(LogLevel_INFO) << "STEP1" << std::endl;
        ptr_hero->_id = myHero_DATA[i]["id"].asInt();
//        Logger::Get(LogLevel_INFO) << "Got myHero_DATA[\"id\"].asInt() " << ptr_hero->id() << std::endl;
//        Logger::Get(LogLevel_INFO) << "myHero_DATA[\"type\"].asString() " << myHero_DATA[i]["type"].asString() << std::endl;
        HeroName _hero = convert_heroName_from_string(myHero_DATA[i]["type"].asString());
//        Logger::Get(LogLevel_INFO) << "myHero_DATA[\"type\"].asString() " << myHero_DATA[i]["type"].asString() << std::endl;
        HeroConstants heroConstants = _game->getHeroConstants(_hero);
//        Logger::Get(LogLevel_INFO) << "STEP2" << std::endl;
        std::vector<Ability *> abilities;
        for(AbilityName abilityName:heroConstants.getAbilityNames())
        {
            Ability* newAbility = new Ability;
//            Logger::Get(LogLevel_INFO) << "STEP3" << std::endl;

            newAbility->_abilityConstants = _game->getAbilityConstants(abilityName);

            abilities.push_back(newAbility);
        }

//        Logger::Get(LogLevel_INFO) << "STEP4" << std::endl;

        ptr_hero->set_abilities(abilities);
        ptr_hero->_heroConstants = heroConstants;
        tmp_my_hero_list.push_back(ptr_hero);
    }
    _game->set_myHeroes(tmp_my_hero_list);
//    Logger::Get(LogLevel_INFO) << "getting set_myHeroes" << std::endl;
    //oppHeroes:
    std::vector<Hero *> tmp_opp_hero_list;
    Json::Value oppHero_DATA = root["oppHeroes"];
    for(int i = 0; i < oppHero_DATA.size(); ++i){
        Hero* ptr_hero = new Hero();

        ptr_hero->_id = oppHero_DATA[i]["id"].asInt();
        HeroName _hero = convert_heroName_from_string(oppHero_DATA[i]["type"].asString());
        HeroConstants heroConstants = _game->getHeroConstants(_hero);
        std::vector<Ability *> abilities;
        for(AbilityName abilityName:heroConstants.getAbilityNames())
        {
            Ability* newAbility = new Ability;

            newAbility->_abilityConstants = _game->getAbilityConstants(abilityName);

            abilities.push_back(newAbility);
        }

        ptr_hero->set_abilities(abilities);
        ptr_hero->_heroConstants = heroConstants;
        tmp_opp_hero_list.push_back(ptr_hero);
    }
    _game->set_oppHeroes(tmp_opp_hero_list);

    //currentTurn:
    _game->_currentTurn = root["currentTurn"].asInt();

//    Logger::Get(LogLevel_INFO) << "End of function" << std::endl;

}



