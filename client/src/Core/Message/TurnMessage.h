#ifndef AIC18_CLIENT_CPP_TURN_MESSAGE_H
#define AIC18_CLIENT_CPP_TURN_MESSAGE_H

#include <Model/World.h>
#include "Message.h"

class TurnMessage final : public Message {
public:

    explicit TurnMessage(Json::Value&& root);

    explicit TurnMessage(std::string&& json_form);

    void parse_my_units(Map& attack_map, const std::vector<Path*>& paths);

    void parse_enemy_units(Map& defence_map, const std::vector<Path*>& paths);

    void parse_my_towers(Map& defence_map);

    void parse_enemy_towers(Map& attack_map);

    Player parse_my_information();

    Player parse_enemy_information();

    std::vector<Unit*> parse_dead_units(World& world);

    std::vector<Unit*> parse_passed_units(World& world);

    std::vector<Tower*> parse_destroyed_towers(World& world);

    std::vector<BeanEvent*> parse_bean_events();

    std::vector<StormEvent*> parse_storm_events();

};

#endif // AIC18_CLIENT_CPP_TURN_MESSAGE_H
