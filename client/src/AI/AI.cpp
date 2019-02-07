#include "AI.h"

#include <cstdlib>
#include <iostream>

using namespace std;


void AI::preProcess(World *world) {
    cerr << "preProcess\n";
}



void printLog(World *world) {
    cerr << world->getMyHeroes().size() << '\n';
    auto my_hero_vec = world->getMyHeroes();
    for (Hero *hero : my_hero_vec) {
        cerr << HeroName_to_string(hero->getName()) << endl;
    }
}

void printMap(World *world){
    cerr << "MAP:" << endl;
    for (vector<Cell *> _row : world->map().getCells()){
        for (Cell * _cell : _row){
            if(_cell->isWall())
                cerr << "#";
            else if(world->getMyHero(*_cell) != Hero::NULL_HERO)
                cerr << world->getMyHero(*_cell).getId();
            else if(world->getOppHero(*_cell) != Hero::NULL_HERO)
                cerr << world->getOppHero(*_cell).getId();
            else
                cerr << ".";
        }
        cerr << endl;
    }
}
int cnt = 0;

void AI::pick(World *world) {
    cerr << "pick\n";
    vector<Hero *> my_heroes = world->getMyHeroes();
    vector<Hero *> opp_heroes = world->getOppHeroes();

    cerr << "Lens: " << my_heroes.size() << ',' << opp_heroes.size() << endl;


    if(cnt == 0) {
        cerr << "SECNTRY\n";
        world->pickHero(SENTRY);
    }
    else if(cnt == 1) {
        world->pickHero(BLASTER);
        cerr << "BLAST\n";
    }
    else if(cnt == 2){
        cerr << "HEAL\n";
        world->pickHero(HEALER);
    }
    else{
        world->pickHero(GUARDIAN);
        cerr << "GURD\n";
    }
    cnt++;
    printLog(world);
}

void AI::move(World *world) {
    cerr << "move\n";
//    printLog(world);

    int target_row[4],target_column[4];
    target_row[0] = (world->map().getRowNum() * 1) / 4;
    target_column[0] = (world->map().getColumnNum() * 1) / 4;
    target_row[1] = (world->map().getRowNum() * 1) / 4;
    target_column[1] = (world->map().getColumnNum() * 3) / 4;
    target_row[2] = (world->map().getRowNum() * 3) / 4;
    target_column[2] = (world->map().getColumnNum() * 1) / 4;
    target_row[3] = (world->map().getRowNum() * 3) / 4;
    target_column[3] = (world->map().getColumnNum() * 3) / 4;


    vector<Hero *> my_heroes = world->getMyHeroes();
    int i=0;
    for(Hero * _hero : my_heroes){
        //Check status:
        cerr << _hero->getName() << "'s current HP is " << _hero->getCurrentHP() << endl;


        vector<Direction> dirs = world->getPathMoveDirections(_hero->getCurrentCell().getRow(), _hero->getCurrentCell().getColumn(),
                                                              target_row[i], target_column[i]);

        if(dirs.size() > 0) {
            cerr << Direction_to_string(dirs[0]) << endl;
            world->moveHero(*_hero, dirs[0]);
            cerr << i << " moved :D" << endl;
        } else {
            cerr << i << " not moving :(" << endl;
        }
        i++;
    }

    cerr << "---------locations---------" << endl;
    printMap(world);
    cerr << "---------------------------" << endl;

}

bool Attack(Hero* myHero, Hero* oppHero, World *world){


    for(Ability* _ability : myHero->getOffensiveAbilities()){
        if(world->manhattanDistance(myHero->getCurrentCell(),oppHero->getCurrentCell()) <= _ability->getRange()){
            world->castAbility(*myHero,*_ability,oppHero->getCurrentCell());
            return true;
        }
    }

    return true;

}

void AI::action(World *world) {
    cerr << "action\n";
    vector<Hero *> my_heroes = world->getMyHeroes();
    vector<Hero *> opp_heroes = world->getOppHeroes();

    cerr << "---Ability---" << endl;
    for(Hero* _hero : my_heroes){
        if(_hero->getName() == HeroName::HEALER){
            for(Ability* _ability : _hero->getAbilities()){
                cerr << abilityName_to_string(_ability->getName()) << "Lobbing: " << _ability->isLobbing() << endl;
            }
        }
    }
    cerr << "-------------" << endl;
}