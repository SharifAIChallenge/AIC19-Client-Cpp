#include "AI.h"

#include <cstdlib>
#include <iostream>

//void AI::simple_turn(World* world) {
//    std::cout << "Turn = " << world->get_current_turn() << std::endl;
//
//    Player& my_information = world->get_my_information();
//    Player& enemy_information = world->get_enemy_information();
//
//    Map& attack_map = world->get_attack_map();
//    Map& defence_map = world->get_defence_map();
//
//    std::vector<Path*> attack_paths = world->get_attack_map_paths();
//    std::vector<Path*> defence_paths = world->get_defence_map_paths();
//
//    std::vector<Unit*> my_units = world->get_my_units();
//    std::vector<Unit*> enemy_units = world->get_enemy_units();
//
//    std::vector<Tower*> my_towers = world->get_my_towers();
//    std::vector<Tower*> visible_enemy_towers = world->get_visible_enemy_towers();
//
//    if (rand() % 2 == 0)
//        world->create_light_unit(rand() % attack_paths.size());
//    else
//        world->create_heavy_unit(rand() % attack_paths.size());
//
//    for (int i = 0; i < defence_map.get_width(); ++i)
//        for (int j = 0; j < defence_map.get_height(); ++j)
//            if (world->is_tower_constructible(i, j)) {
//                if (rand() % 2 == 0)
//                    world->create_archer_tower(1, i, j);
//                else
//                    world->create_cannon_tower(1, i, j);
//                break;
//            }
//
//    if (!world->get_my_towers().empty())
//        world->upgrade_tower(world->get_my_towers().front());
//
//    world->create_storm(rand() % defence_map.get_width(), rand() % defence_map.get_height());
//
//    if (!world->get_visible_enemy_towers().empty()) {
//        Tower* enemy_tower = world->get_visible_enemy_towers().front();
//        world->plant_bean(enemy_tower->get_location().get_x(), enemy_tower->get_location().get_y());
//    }
//}
//
//void AI::complex_turn(World* world) {
//    simple_turn(world);
//}
