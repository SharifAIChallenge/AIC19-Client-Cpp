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

void PickMessage::update_game(World *_game) {
    Json::Value root = Message::get_args()[0];

    //myHeroes:
    std::vector<Hero *> tmp_my_hero_list;
    Json::Value myHero_DATA = root["myHeroes"];
    for(int i = 0; i < myHero_DATA.size(); ++i){
        Hero* ptr_hero = new Hero();

        ptr_hero->id() = myHero_DATA["id"].asInt();
        HeroName _hero = convert_heroName_from_string(myHero_DATA["typr"].asString());
        HeroConstants heroConstants = _game->getHeroConstants(_hero);
        std::vector<Ability *> abilities;
        for(AbilityName abilityName:heroConstants.get_abilityNames())
        {
            Ability* newAbility = new Ability;

            newAbility->abilityConstants() = _game->getAbilityConstants(abilityName);

            abilities.push_back(newAbility);
        }

        tmp_my_hero_list.push_back(ptr_hero);
    }
    _game->set_myHeroes(tmp_my_hero_list);//TODO should we use this function?!?!

    //oppHeroes:
    std::vector<Hero *> tmp_opp_hero_list;
    Json::Value oppHero_DATA = root["oppHeroes"];
    for(int i = 0; i < oppHero_DATA.size(); ++i){
        Hero* ptr_hero = new Hero();

        ptr_hero->id() = oppHero_DATA["id"].asInt();
        HeroName _hero = convert_heroName_from_string(oppHero_DATA["typr"].asString());
        HeroConstants heroConstants = _game->getHeroConstants(_hero);
        std::vector<Ability *> abilities;
        for(AbilityName abilityName:heroConstants.get_abilityNames())
        {
            Ability* newAbility = new Ability;

            newAbility->abilityConstants() = _game->getAbilityConstants(abilityName);

            abilities.push_back(newAbility);
        }//TODO maybe you wanta check this...

        tmp_opp_hero_list.push_back(ptr_hero);
    }
    _game->set_oppHeroes(tmp_opp_hero_list);//TODO should we use this function?!?!

    //currentTurn:
    _game->currentTurn() = root["currentTurn"].asInt();

}



