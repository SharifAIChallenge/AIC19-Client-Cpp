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

int targetCellRow[4];
int targetCellColumn[4];

void AI::move(World *world) {
    cerr << "-move" << endl;
    static int targetRefreshPeriod = 0;

    if(targetRefreshPeriod <= 0){
        srand(time(0) + world->getMyHeroes()[0]->getId());//made this so we can test two clients with this exact AI code
        for (int i=0; i<4; ++i){
            while(1){
                targetCellRow[i] = rand() % world->map().getRowNum();
                targetCellColumn[i] = rand() % world->map().getColumnNum();

                //Make sure the target is not a wall!
                if(!world->map().getCell(targetCellRow[i], targetCellColumn[i]).isWall())
                    break;
            }
        }
        targetRefreshPeriod = 20 * 6;// Change target locations after 20 complete moves
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
            //Find the closest attacking target
            Cell target_attack_cell = Cell::NULL_CELL;
            int min_dist = 10000;
            for(Hero* opp_hero : world->getOppHeroes()){
                if(opp_hero->getCurrentCell().isInVision())//if hero is seen
                {
                    if(min_dist > world->manhattanDistance(opp_hero->getCurrentCell(),
                                                                   my_hero->getCurrentCell())){
                        min_dist = world->manhattanDistance(opp_hero->getCurrentCell(),
                                                            my_hero->getCurrentCell());
                        target_attack_cell = opp_hero->getCurrentCell();
                    }
                }
            }

            //Do the attack
            if(target_attack_cell == Cell::NULL_CELL) {
                world->castAbility(*my_hero, AbilityName::BLASTER_ATTACK,target_attack_cell);
            }
        }
    }


    printMap(world);
}