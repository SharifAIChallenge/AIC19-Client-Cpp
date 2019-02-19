#include <stdlib.h>
#include "AI.h"

using namespace std;

void printMap(World* world){
    Map map = world->map();
    for (int row = 0; row < map.getRowNum(); row++) {
        for (int column = 0; column < map.getColumnNum(); column++) {
            Cell cell = map.getCell(row, column);
            char cur;
            if (world->getMyHero(row, column) != Hero::NULL_HERO)
                cur = static_cast<char>('0' + world->getMyHero(row, column).getId() % 10);
            else if (world->getOppHero(row, column) != Hero::NULL_HERO)
                cur = static_cast<char>('0' + world->getOppHero(row, column).getId() % 10);
            else if (cell.isWall())
                cur = '#';
            else if (cell.isInVision())
                cur = '+';
            else
                cur = '.';
            cerr << cur << ' ';

        }
        cerr << endl;
    }
}

void AI::preProcess(World *world) {
    srand(time(0));
}

void AI::pick(World *world) {
    cerr << "-pick" << endl;
    static int cnt= 0;

    switch(cnt){
        case 0:
            world->pickHero(HeroName::BLASTER);
            break;
        case 1:
            world->pickHero(HeroName::GUARDIAN);
            break;
        case 2:
            world->pickHero(HeroName::HEALER);
            break;
        case 3:
            world->pickHero(HeroName::SENTRY);
            break;
        default:
            world->pickHero(HeroName::BLASTER);
    }
    cnt++;

}

bool WAR_IN_OBJECTIVE_ZONE = true;

int targetCellRow[4];
int targetCellColumn[4];

void AI::move(World *world) {
    cerr << "-move" << endl;
    static int targetRefreshPeriod = 0;

    if(targetRefreshPeriod <= 0){
        srand(time(0) + world->getMyHeroes()[0]->getId());//made this so we can test two clients with this exact AI code
        for (int i=0; i<4; ++i){
            if(WAR_IN_OBJECTIVE_ZONE) {
                std::vector<Cell *> obj_list = world->map().getObjectiveZone();

                Cell * targetCell = obj_list.at(rand() % obj_list.size());
                targetCellRow[i] = targetCell->getRow();
                targetCellColumn[i] = targetCell->getRow();
            } else {
                while (1) {
                    targetCellRow[i] = rand() % world->map().getRowNum();
                    targetCellColumn[i] = rand() % world->map().getColumnNum();

                    //Make sure the target is not a wall!
                    if (!world->map().getCell(targetCellRow[i], targetCellColumn[i]).isWall())
                        break;
                }
            }
        }
        targetRefreshPeriod = 10 * 6;// Change target locations after 20 complete moves
    } else
        targetRefreshPeriod--;

    vector<Hero *> my_heros = world->getMyHeroes();
    for(int i=0; i<4; ++i){
        vector<Direction> _dirs = world->getPathMoveDirections(my_heros[i]->getCurrentCell().getRow(),
                                                               my_heros[i]->getCurrentCell().getColumn(),
                                                               targetCellRow[i],
                                                               targetCellColumn[i]);
        if(_dirs.size() == 0)//ALWAYS check if there is a path to that target!!!!
            continue;
        world->moveHero(my_heros[i]->getId(),
                        _dirs[0]);
    }

}


void AI::action(World *world) {
    cerr << "-action" << endl;

    for(Hero* my_hero : world->getMyHeroes()){
        if(my_hero->getName() == HeroName::BLASTER){
            //Find the closest bombing target
            Cell bombing_cell = Cell::NULL_CELL;
            int min_dist = 10000;
            for(Hero* opp_hero : world->getOppHeroes()){
                if(opp_hero->getCurrentCell().isInVision())//if hero is seen
                {
                    if(min_dist > world->manhattanDistance(opp_hero->getCurrentCell(),
                                                           my_hero->getCurrentCell())){
                        min_dist = world->manhattanDistance(opp_hero->getCurrentCell(),
                                                            my_hero->getCurrentCell());
                        bombing_cell = opp_hero->getCurrentCell();
                    }
                }
            }
            //Perform the bombing
            if(bombing_cell != Cell::NULL_CELL) {
                world->castAbility(*my_hero, AbilityName::BLASTER_BOMB,bombing_cell);
            }
        } else if(my_hero->getName() == HeroName::GUARDIAN){
            //Find the closest attacking target
            Cell attack_cell = Cell::NULL_CELL;
            int min_dist = 10000;
            for(Hero* opp_hero : world->getOppHeroes()){
                if(opp_hero->getCurrentCell().isInVision())//if hero is seen
                {
                    if(min_dist > world->manhattanDistance(opp_hero->getCurrentCell(),
                                                           my_hero->getCurrentCell())){
                        min_dist = world->manhattanDistance(opp_hero->getCurrentCell(),
                                                            my_hero->getCurrentCell());
                        attack_cell = opp_hero->getCurrentCell();
                    }
                }
            }
            //Perform the attack
            if(attack_cell != Cell::NULL_CELL) {
                world->castAbility(*my_hero, AbilityName::GUARDIAN_ATTACK,attack_cell);
            }
        } else if(my_hero->getName() == HeroName::SENTRY){
            //Find the closest shooting target
            Cell shoot_cell = Cell::NULL_CELL;
            int min_dist = 10000;
            for(Hero* opp_hero : world->getOppHeroes()){
                if(opp_hero->getCurrentCell().isInVision())//if hero is seen
                {
                    if(min_dist > world->manhattanDistance(opp_hero->getCurrentCell(),
                                                           my_hero->getCurrentCell())){
                        min_dist = world->manhattanDistance(opp_hero->getCurrentCell(),
                                                            my_hero->getCurrentCell());
                        shoot_cell = opp_hero->getCurrentCell();
                    }
                }
            }
            //Perform the shooting
            if(shoot_cell != Cell::NULL_CELL) {
                world->castAbility(*my_hero, AbilityName::SENTRY_RAY,shoot_cell);
            }
        } else if(my_hero->getName() == HeroName::HEALER){
            //Find the closest healing target
            Cell target_heal_cell = Cell::NULL_CELL;
            int min_dist = 10000;
            for(Hero* _hero : world->getMyHeroes()){
                if(min_dist > world->manhattanDistance(_hero->getCurrentCell(), my_hero->getCurrentCell()) &&
                        _hero->getRemRespawnTime() == 0 &&
                        _hero->getCurrentHP() != _hero->getMaxHP()){
                    min_dist = world->manhattanDistance(_hero->getCurrentCell(),
                                                        my_hero->getCurrentCell());
                    target_heal_cell = _hero->getCurrentCell();
                }
            }
            //Do the attack
            if(target_heal_cell != Cell::NULL_CELL) {
                world->castAbility(*my_hero, AbilityName::HEALER_HEAL,target_heal_cell);
            }
        }
    }


    printMap(world);
}