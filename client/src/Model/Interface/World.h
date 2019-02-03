#ifndef AIC19_CLIENT_CPP_GAME_H
#define AIC19_CLIENT_CPP_GAME_H

#include "Map.h"
#include "GameConstants.h"
#include "AbilityConstants.h"
#include "HeroConstants.h"
#include "Hero.h"
#include "CastAbility.h"
#include <cstdlib>
#include <unordered_map>
#include <algorithm>
#include <map>
#include <Core/EventQueue.h>
#include <Core/Message/CreatePickMessage.h>
#include <Core/Message/CreateCastMessage.h>
#include <Core/Message/CreateMoveMessage.h>

class World {
public:

    World() = default;
    ~World();//delete the vector items...

    World(EventQueue& event_queue);

    World(const World& _world);//Copy constructor
    //Getter & Setters:

    void set_map(const Map &_map);
    Map& map();


    void set_gameConstants(const GameConstants &_gameConstants);
    const GameConstants &get_gameConstants() const;
    GameConstants& gameConstants();

//    void set_abilityConstants(const AbilityConstants &_abilityConstants);
//    const AbilityConstants &get_abilityConstants() const;
//    AbilityConstants& abilityConstants();
//
//    void set_heroConstants(const HeroConstants &_heroConstants);
//    const HeroConstants &get_heroConstants() const;
//    HeroConstants& heroConstants();

    void set_abilityConstants(const std::vector<AbilityConstants *> &_abilityConstants);
    void set_heroConstants(const std::vector<HeroConstants *> &_heroConstants);


    int& AP();
    int AP() const;


    int& myScore();
    int myScore() const;

    int& oppScore();
    int oppScore() const;

    int& currentTurn();
    int currentTurn() const;

    Phase& currentPhase();
    Phase currentPhase() const;

    void set_myCastAbilities(std::vector<CastAbility *> _myCAbility);
    std::vector<CastAbility *> get_myCastAbilities() const;

    void set_oppCastAbilities(std::vector<CastAbility *> _oppCAbility);
    std::vector<CastAbility *> get_oppCastAbilities() const;

    // For all Cell type inputs we will have another method with row-column inputs
    // For all hero id inputs we will have another method with Hero object
    // For all Ability Object inputs we will have another method with AbilityName enum

    Hero getHero(int id);
    Hero getMyHero(Cell cell);
    Hero getMyHero(int cellRow, int cellColumn);
    Hero getOppHero(Cell cell);
    Hero getOppHero(int cellRow, int cellColumn);

    //algorithmics:
    Cell getNextCell(const Cell& cell,const Direction& direction);
    int crossProduct(int x1, int y1, int x2, int y2, int x3, int y3);
    int squareCollision(const Cell& startCell,const Cell& targetCell,const Cell& cell);
    bool isCloser(Cell currentCell, Cell targetCell, Cell nextCell);
    void dfs(Cell& currentCell, Cell& startCell, Cell& targetCell, std::unordered_map<Cell*, bool>& isSeen,
             std::vector<Cell *>& path);

    // Get all the cells that collide with the ray line in at least one non corner point,
    // before reaching a wall. If it hits a wall cell just in the corner,
    // it would also stop too. should we implement this?


    std::vector<Cell *> getRayCells(Cell startCell, Cell endCell);
    std::vector<Cell *> getImpactCells(AbilityName abilityName, Cell startCell, Cell targetCell);
    Cell getImpactCell(AbilityName abilityName, Cell startCell, Cell targetCell);
    Cell getImpactCell(AbilityName abilityName, int startCellRow, int startCellColumn, int endCellRow,
                       int endCellColumn);
    Cell getImpactCell(Ability ability, Cell startCell, Cell targetCell);
    Cell getImpactCell(Ability ability, int startCellRow, int startCellColumn, int endCellRow, int endCellColumn);


    std::vector<Direction> getPathMoveDirections(Cell startCell, Cell endCell);
    std::vector<Direction> getPathMoveDirections(int startCellRow, int startCellColumn, int endCellRow, int endCellColumn);

    int manhattanDistance(Cell startCell, Cell endCell);
    int manhattanDistance(int startCellRow, int startCellColumn, int endCellRow, int endCellColumn);
    bool isInVision(Cell startCell, Cell endCell);
    bool isInVision(int startCellRow, int startCellColumn, int endCellRow, int endCellColumn);
    bool isAccessible(int row, int column);

    void castAbility(int heroId, AbilityName abilityName, int targetCellRow, int targetCellColumn);
    void castAbility(int heroId, AbilityName abilityName, Cell targetCell);
    void castAbility(int heroId, Ability ability, int targetCellRow, int targetCellColumn);
    void castAbility(int heroId, Ability ability, Cell targetCell);
    void castAbility(const Hero hero, AbilityName abilityName, int targetCellRow, int targetCellColumn);
    void castAbility(Hero hero, AbilityName abilityName, Cell targetCell);
    void castAbility(Hero hero, Ability ability, int targetCellRow, int targetCellColumn);
    void castAbility(Hero hero, Ability ability, Cell targetCell);


    void moveHero(int id, std::vector<Direction> direction);//TODO sekall asked me to put this "TODO"
    void pickHero(HeroName heroName);

    void initData();

private:

    Map _map;
    GameConstants _gameConstants;
    std::vector<AbilityConstants *> _abilityConstants;
    std::vector<HeroConstants *> _heroConstants;

    //TODO its better to implement a get function
    // returning an array for these vectors
    std::vector<Hero *> _myHeroes;
    std::vector<Hero *> _oppHeroes;
    std::vector<Hero *> _myDeadHeroes;
    std::vector<Hero *> _oppDeadHeroes;

    std::vector<CastAbility *> _myCastAbilities;
    std::vector<CastAbility *> _oppCastAbilities;

    int _AP;
    int _myScore;
    int _oppScore;
    int _currentTurn;

    Phase _currentPhase;

    EventQueue& _event_queue;

    AbilityConstants getAbilityConstants(AbilityName abilityName);

    HeroConstants getHeroConstants(HeroName heroName);

    //This function will also handle the _myDeadHeroes
    void set_myHeroes(std::vector<Hero *> _heroes);
    //This function will also handle the _myDeadHeroes
    void set_oppHeroes(std::vector<Hero *> _heroes);

    friend class InitMessage;
    friend class TurnMessage;
    friend class PickMessage;

};


#endif //AIC19_CLIENT_CPP_GAME_H
