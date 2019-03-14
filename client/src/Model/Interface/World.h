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
    Map& getMap();


    void set_gameConstants(const GameConstants &_gameConstants);
    const GameConstants &get_gameConstants() const;
    GameConstants& gameConstants();

    void set_abilityConstants(const std::vector<AbilityConstants *> &_abilityConstants);
    void set_heroConstants(const std::vector<HeroConstants *> &_heroConstants);


    int AP() const;
    int myScore() const;
    int oppScore() const;

    int& currentTurn();
    int currentTurn() const;

//    int& movePhaseNum();
    int movePhaaseNum() const;

//    Phase& currentPhase();
    Phase currentPhase() const;

    // The user of the below functions shouldn't
    // delete the elements in the list
    void set_myCastAbilities(std::vector<CastAbility *> _myCAbility);
    std::vector<CastAbility *> getMyCastAbilities() const;

    void set_oppCastAbilities(std::vector<CastAbility *> _oppCAbility);
    std::vector<CastAbility *> getOppCastAbilities() const;

    // For all Cell type inputs we will have another method with row-column inputs
    // For all hero id inputs we will have another method with Hero object
    // For all Ability Object inputs we will have another method with AbilityName enum
    Hero& getHero(int id);
    Hero& getMyHero(const Cell &cell);
    Hero& getMyHero(int cellRow, int cellColumn);
    Hero* getMyHero_ptr(const Cell &cell);
    Hero& getOppHero(const Cell &cell);
    Hero& getOppHero(int cellRow, int cellColumn);
    Hero* getOppHero_ptr(const Cell &cell);


    std::vector<Cell *> getRayCells(Cell &startCell, Cell &endCell, bool wallPiercing = false);
    std::vector<Cell *> getImpactCells(const AbilityName &abilityName,Cell &startCell, Cell &targetCell);
    Cell getImpactCell(AbilityName abilityName, Cell &startCell, Cell &targetCell);
    Cell getImpactCell(AbilityName abilityName, int startCellRow, int startCellColumn, int endCellRow,
                       int endCellColumn);
    Cell getImpactCell(Ability ability, Cell &startCell, Cell &targetCell);
    Cell getImpactCell(Ability ability, int startCellRow, int startCellColumn, int endCellRow, int endCellColumn);


    std::vector<Direction> getPathMoveDirections(Cell &startCell, Cell &endCell);
    std::vector<Direction> getPathMoveDirections(int startCellRow, int startCellColumn, int endCellRow, int endCellColumn);
    std::vector<Direction> getPathMoveDirections(Cell &startCell, Cell &endCell, std::vector<Cell *> _avoidingCells);
    std::vector<Direction> getPathMoveDirections(int startCellRow, int startCellColumn, int endCellRow, int endCellColumn, std::vector<Cell *> _avoidingCells);


    int manhattanDistance(const Cell &startCell,const Cell &endCell);
    int manhattanDistance(int startCellRow, int startCellColumn, int endCellRow, int endCellColumn);
    bool isInVision(Cell &startCell, Cell &endCell);
    bool isInVision(int startCellRow, int startCellColumn, int endCellRow, int endCellColumn);
    bool isAccessible(int row, int column);
    bool isAccessible(const Cell& cell);

    void castAbility(int heroId, AbilityName abilityName, int targetCellRow, int targetCellColumn);
    void castAbility(int heroId, AbilityName abilityName,const Cell &targetCell);
    void castAbility(int heroId, Ability ability, int targetCellRow, int targetCellColumn);
    void castAbility(int heroId, Ability ability,const Cell &targetCell);
    void castAbility(const Hero &hero, AbilityName abilityName, int targetCellRow, int targetCellColumn);
    void castAbility(const Hero &hero, AbilityName abilityName,const Cell &targetCell);
    void castAbility(const Hero &hero, Ability ability, int targetCellRow, int targetCellColumn);
    void castAbility(const Hero &hero, Ability ability,const Cell &targetCell);


    void moveHero(int id, Direction direction);
    void moveHero(const Hero &hero, Direction direction);

    void pickHero(HeroName heroName);

    void initData();


    std::vector<Hero *> getMyHeroes() const;
    std::vector<Hero *> getOppHeroes() const;
    std::vector<Hero *> getMyDeadHeroes() const;
    std::vector<Hero *> getOppDeadHeroes() const;

    std::vector<AbilityConstants *> getAbilityConstants() const;
    std::vector<HeroConstants *> getHeroConstants() const;

    /**
     * Returns all the heroes an ability will affect, if we cast it from a specified cell to another.
     * For OFFENSIVE or DODGE abilities it will return enemy heroes,
     * and for DEFENSIVE abilities it will return ally heroes in cells around the ability's impact cell
     * (If they are in ability's AOE).
     *
     * @param abilityName Name of the ability we want to cast
     * @param startCell   The cell we want to cast from
     * @param targetCell  The cell we are aiming to
     * @return
     */
    std::vector<Hero *> getAbilityTargets(AbilityName abilityName, Cell &startCell, Cell &targetCell);
    std::vector<Hero *> getAbilityTargets(Ability ability, Cell &startCell, Cell &targetCell);
    std::vector<Hero *> getAbilityTargets(AbilityName abilityName, int startCellRow, int startCellColumn,
                                          int targetCellRow, int targetCellColumn);
    std::vector<Hero *> getAbilityTargets(Ability ability, int startCellRow, int startCellColumn, int targetCellRow,
                                          int targetCellColumn);

    int getAP();
    int getMyScore();
    int getOppScore();
    int getCurrentTurn();
    Phase getCurrentPhase();
    int getMaxScore();
    int getMaxAP();
    int getMaxTurns();
    int getKillScore();
    int getObjectiveZoneScore();
    int getMovePhaseNum();
    int getMaxOvertime();
    int getRemainingOvertime();
    int getMaxScoreDiff();
    int getInitOvertime();
    int getTotalMovePhases();




private:
    Map _map;
    GameConstants _gameConstants;
    std::vector<AbilityConstants *> _abilityConstants;
    std::vector<HeroConstants *> _heroConstants;

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
    int _movePhaseNum;
    int _maxOvertime;
    int _remainingOvertime;
    Phase _currentPhase;

    EventQueue& _event_queue;

    AbilityConstants getAbilityConstants(AbilityName abilityName);

    HeroConstants getHeroConstants(HeroName heroName);

    std::vector<Cell *> getCellsInAOE(const Cell &impactCell, int AOE);
    std::vector<Hero *> getMyHeroesInCells(std::vector<Cell *> cells);
    std::vector<Hero *> getOppHeroesInCells(std::vector<Cell *> cells);

    //This function will also handle the _myDeadHeroes
    void set_myHeroes(std::vector<Hero *> _heroes);
    //This function will also handle the _myDeadHeroes
    void set_oppHeroes(std::vector<Hero *> _heroes);

    friend class InitMessage;
    friend class TurnMessage;
    friend class PickMessage;


    //algorithmics:
    Cell& getNextCell(const Cell& cell,const Direction& direction);
    int crossProduct(int x1, int y1, int x2, int y2, int x3, int y3);
    int squareCollision(const Cell& startCell,const Cell& targetCell,const Cell& cell);
    bool isCloser(Cell currentCell, Cell targetCell, Cell nextCell);
    void dfs(Cell& currentCell, Cell& startCell, Cell& targetCell, std::unordered_map<Cell*, bool>& isSeen,
             std::vector<Cell *>& path, bool wallPiercing = false);

    inline bool isInCells(const Cell& _cell,std::vector<Cell *> _cellList);

};


#endif //AIC19_CLIENT_CPP_GAME_H
