#include <Utility/Logger.h>
#include "World.h"

World::World(EventQueue &event_queue): _event_queue(event_queue){

}


World::World(const World& _world): _event_queue(_world._event_queue) {

    this->_map = _world._map;
    this->_gameConstants = _world._gameConstants;
    this->set_abilityConstants(_world._abilityConstants);
    this->set_heroConstants(_world._heroConstants);
}


//----------------map------------------
void World::set_map(const Map &_map) {
    World::_map = _map;
}

Map &World::map() {
    return _map;
}
//------------gameConstants------------
const GameConstants &World::get_gameConstants() const {
    return _gameConstants;
}

void World::set_gameConstants(const GameConstants &_gameConstants) {
    World::_gameConstants = _gameConstants;
}

GameConstants &World::gameConstants() {
    return _gameConstants;
}
int World::AP() const{
    return _AP;
}
//--------------myScore----------------
int World::myScore() const {
    return _myScore;
}
//-------------oppScore----------------
int World::oppScore() const {
    return _oppScore;
}

World::~World() {
    _map._clear_cells();
    for (std::vector<Hero *>::iterator it = _myHeroes.begin() ; it != _myHeroes.end(); ++it){
        delete *it;
    }
    _myHeroes.clear();

    for (std::vector<Hero *>::iterator it = _oppHeroes.begin() ; it != _oppHeroes.end(); ++it){
        delete *it;
    }
    _oppHeroes.clear();

    for (std::vector<CastAbility *>::iterator it = _myCastAbilities.begin() ; it != _myCastAbilities.end(); ++it){
        delete *it;
    }
    _myCastAbilities.clear();

    for (std::vector<CastAbility *>::iterator it = _oppCastAbilities.begin() ; it != _oppCastAbilities.end(); ++it){
        delete *it;
    }
    _oppCastAbilities.clear();

    for (AbilityConstants * _abilityConst : _abilityConstants){
        delete _abilityConst;
    }
    _abilityConstants.clear();

    for (HeroConstants * _heroConst : _heroConstants){
        delete _heroConst;
    }
    _heroConstants.clear();


}

//logical functions:
Hero& World::getHero(int id) {
    for(std::vector<Hero *>::iterator it = _myHeroes.begin(); it != _myHeroes.end(); ++it){
        if(static_cast<const Hero *>(*it)->getId() == id){
            return **it;
        }
    }
    for(std::vector<Hero *>::iterator it = _oppHeroes.begin(); it != _oppHeroes.end(); ++it){
        if(static_cast<const Hero *>(*it)->getId() == id){
            return **it;
        }
    }
    return Hero::NULL_HERO;
}

Hero& World::getMyHero(const Cell &cell) {
    for(std::vector<Hero *>::iterator it = _myHeroes.begin(); it != _myHeroes.end(); ++it ){
        //This only checks the location of the cell
        if((*it)->getCurrentCell() == cell){
            return **it;
        }
    }
    return Hero::NULL_HERO;
}

Hero* World::getMyHero_ptr(const Cell &cell) {
    for(std::vector<Hero *>::iterator it = _myHeroes.begin(); it != _myHeroes.end(); ++it ){
        //This only checks the location of the cell
        if((*it)->getCurrentCell() == cell){
            return *it;
        }
    }
    return &Hero::NULL_HERO;
}

Hero& World::getMyHero(int cellRow, int cellColumn) {
    if(!_map.isInMap(cellRow,cellColumn))
        return Hero::NULL_HERO;

    for(std::vector<Hero *>::iterator it = _myHeroes.begin(); it != _myHeroes.end(); ++it ){
        //This only checks the location of the cell
        if((*it)->getCurrentCell().getRow() == cellRow &&
                (*it)->getCurrentCell().getColumn() == cellColumn){
            return **it;
        }
    }
    return Hero::NULL_HERO;
}

Hero& World::getOppHero(const Cell &cell) {
    for(std::vector<Hero *>::iterator it = _oppHeroes.begin(); it!= _oppHeroes.end(); ++it){
        //This only checks the location of the cell
        if((*it)->getCurrentCell() == cell){
            return **it;
        }
    }
    return Hero::NULL_HERO;
}

Hero *World::getOppHero_ptr(const Cell &cell) {
    for(std::vector<Hero *>::iterator it = _oppHeroes.begin(); it!= _oppHeroes.end(); ++it){
        //This only checks the location of the cell
        if((*it)->getCurrentCell() == cell){
            return *it;
        }
    }
    return &Hero::NULL_HERO;
}

Hero& World::getOppHero(int cellRow, int cellColumn) {
    if(!_map.isInMap(cellRow,cellColumn))
        return Hero::NULL_HERO;

    for(std::vector<Hero *>::iterator it = _oppHeroes.begin(); it!= _oppHeroes.end(); ++it){
        //This only checks the location of the cell
        if((*it)->getCurrentCell().getRow() == cellRow &&
                (*it)->getCurrentCell().getColumn() == cellColumn){
            return **it;
        }
    }
    return Hero::NULL_HERO;
}

int World::manhattanDistance(const Cell &startCell,const Cell &endCell) {
    return abs(startCell.getRow() - endCell.getRow()) +
            abs(startCell.getColumn() - endCell.getColumn());
}

int World::manhattanDistance(int startCellRow, int startCellColumn, int endCellRow, int endCellColumn) {
    if(this->_map.isInMap(startCellRow,startCellColumn) && this->_map.isInMap(endCellRow,endCellColumn)){
        return abs(startCellRow - endCellRow) + abs(startCellColumn - endCellColumn);
    } else {
        return -1;
    }

}

//------------Algorithmic--------------

Cell& World::getNextCell(const Cell &cell, const Direction& direction) {
    switch (direction)
    {
        case Direction::UP:
            if (_map.isInMap(cell.getRow() - 1, cell.getColumn()))
                return _map.getCell(cell.getRow() - 1, cell.getColumn());
            else
                return Cell::NULL_CELL;
        case Direction::DOWN:
            if (_map.isInMap(cell.getRow() + 1, cell.getColumn()))
                return _map.getCell(cell.getRow() + 1, cell.getColumn());
            else
                return Cell::NULL_CELL;
        case Direction::LEFT:
            if (_map.isInMap(cell.getRow(), cell.getColumn() - 1))
                return _map.getCell(cell.getRow(), cell.getColumn() - 1);
            else
                return Cell::NULL_CELL;
        case Direction::RIGHT:
            if (_map.isInMap(cell.getRow(), cell.getColumn() + 1))
                return _map.getCell(cell.getRow(), cell.getColumn() + 1);
            else
                return Cell::NULL_CELL;
    }
    return Cell::NULL_CELL; // never happens
}

/**
     * This method calculates the cross product.
     * negative return value -> point1-point2 line is on the left side of point1-point3 line
     * zero return value -> the three points lie on the same line
     * positive return value -> point1-point2 line is on the right side of point1-point3 line
     *
     * @param x1
     * @param y1
     * @param x2
     * @param y2
     * @param x3
     * @param y3
     * @return
     */
int World::crossProduct(int x1, int y1, int x2, int y2, int x3, int y3)
{
    return (x2 - x1) * (y3 - y1) - (y2 - y1) * (x3 - x1);
}

/**
     * Checks the state of collision between the start cell to target cell line and cell square.
     * -1 -> doesn't pass through square at all
     * 0 -> passes through just one corner
     * 1 -> passes through the square
     *
     * @param startCell
     * @param targetCell
     * @param cell
     * @return
     */
int World::squareCollision(const Cell& startCell,const Cell& targetCell,const Cell& cell)
{
    bool hasNegative = false, hasPositive = false, hasZero = false;
    for (int row = 2 * cell.getRow(); row <= 2 * (cell.getRow() + 1); row += 2)
        for (int column = 2 * cell.getColumn(); column <= 2 * (cell.getColumn() + 1); column += 2)
        {
            int _crossProduct = crossProduct(2 * startCell.getRow() + 1, 2 * startCell.getColumn() + 1,
                                            2 * targetCell.getRow() + 1, 2 * targetCell.getColumn() + 1, row, column);
            if (_crossProduct < 0) hasNegative = true;
            else if (_crossProduct > 0) hasPositive = true;
            else hasZero = true;
        }
    if (hasNegative && hasPositive) return 1;
    if (hasZero) return 0;
    return -1;
}

bool World::isCloser(Cell currentCell, Cell targetCell, Cell nextCell)
{
    return manhattanDistance(nextCell, targetCell) <= manhattanDistance(currentCell, targetCell);
}

void World::dfs(Cell& currentCell, Cell& startCell, Cell& targetCell, std::unordered_map<Cell*, bool>& isSeen,
               std::vector<Cell *>& path, bool wallPiercing) {
    isSeen[&currentCell] = true;
    path.push_back(&currentCell);
    //make sure the "Direction" enum is not initialized!
    for (int dir = Direction::UP; dir <= Direction::RIGHT ; dir++ )//(Direction direction : Direction.values())
    {
        Direction direction = static_cast<Direction>(dir);
        Cell* nextCell = &getNextCell(currentCell, direction);
        if (*nextCell != Cell::NULL_CELL && isSeen.find(nextCell) == isSeen.end() && isCloser(currentCell, targetCell, *nextCell))
        {
            int collisionState = squareCollision(startCell, targetCell, *nextCell);
            if ((collisionState == 0 || collisionState == 1) && (nextCell->isWall() && !wallPiercing))
                return;
            if (collisionState == 1)
            {
                dfs(*nextCell, startCell, targetCell, isSeen, path, wallPiercing);
                return;
            }
        }
    }
    for (int dRow = -1; dRow <= 1; dRow += 2)
        for (int dColumn = -1; dColumn <= 1; dColumn += 2)
        {
            int newRow = currentCell.getRow() + dRow;
            int newColumn = currentCell.getColumn() + dColumn;
            Cell* nextCell = _map.getCell_ptr(newRow, newColumn);
            //Assumed isSeen.find(nextCell) == isSeen.end() means it's not found...
            if (*nextCell != Cell::NULL_CELL && isSeen.find(nextCell) == isSeen.end() && isCloser(currentCell, targetCell, *nextCell))
            {
                int collisionState = squareCollision(startCell, targetCell, *nextCell);
                if (collisionState == 0 || collisionState == 1 && (nextCell->isWall() && !wallPiercing))
                    return;
                if (collisionState == 1)
                {
                    dfs(*nextCell, startCell, targetCell, isSeen, path, wallPiercing);
                }
            }
        }

}

/**
     * Get all the cells that collide with the ray line in at least one non corner point, before reaching a wall.
     * If it hits a wall cell just in the corner, it would also stop too.
     *
     * @param startCell
     * @param targetCell
     * @return
     */
std::vector<Cell *> World::getRayCells(Cell &startCell, Cell &endCell, bool wallPiercing) {
    if(startCell == Cell::NULL_CELL || endCell == Cell::NULL_CELL){
        return std::vector<Cell *>{};
    }
    std::vector<Cell *> path;
    std::unordered_map<Cell*, bool> _isSeen;
    dfs(startCell,startCell,endCell,_isSeen,path,wallPiercing);
    return path;
}

std::vector<Cell *> World::getImpactCells(const AbilityName &abilityName,Cell &startCell,Cell &targetCell) {
    AbilityConstants abilityConstants = getAbilityConstants(abilityName);
    if (startCell == Cell::NULL_CELL || targetCell == Cell::NULL_CELL || abilityConstants == AbilityConstants::NULL_ABILITY_CONSTANTS ||
        (!abilityConstants.isLobbing() && startCell.isWall()) || startCell == targetCell)
    {
        return std::vector<Cell *>{&startCell};
    }

    std::vector<Cell *> impactCells;
    std::vector<Cell *> rayCells = getRayCells(startCell, targetCell, abilityConstants.isLobbing());
    Cell* lastCell = &Cell::NULL_CELL;
    for (std::vector<Cell *>::iterator cellIt = rayCells.begin(); cellIt !=rayCells.end(); ++cellIt) {

        if (manhattanDistance(startCell, **cellIt) > abilityConstants.getRange())
            break;
        lastCell = *cellIt;
        if(abilityConstants.isLobbing()){
            continue;
        }
        if ((getOppHero(**cellIt) != Hero::NULL_HERO && abilityConstants.getType() != AbilityType::DEFENSIVE)
            || (getMyHero(**cellIt) != Hero::NULL_HERO && abilityConstants.getType() == AbilityType::DEFENSIVE))
        {
            impactCells.push_back(*cellIt);
            if(!abilityConstants.isPiercing()) break;
        }
    }
    if (std::find(impactCells.begin(), impactCells.end(), lastCell)
        == impactCells.end())//does not contain!
    {
        impactCells.push_back(lastCell);
    }
    return impactCells;
}


Cell World::getImpactCell(AbilityName abilityName, Cell &startCell, Cell &targetCell) {
    std::vector<Cell *> impactCells = getImpactCells(abilityName, startCell, targetCell);
//    if()
    return *(impactCells.back());
}


Cell World::getImpactCell(Ability ability, Cell &startCell, Cell &targetCell) {
    return getImpactCell(ability.getAbilityConstants().getName(), startCell, targetCell);
}

Cell World::getImpactCell(Ability ability, int startCellRow, int startCellColumn, int endCellRow, int endCellColumn) {
    if (!_map.isInMap(startCellRow, startCellColumn) || !_map.isInMap(endCellRow, endCellColumn))
        return Cell::NULL_CELL;
    return getImpactCell(ability.getAbilityConstants().getName(), _map.getCell(startCellRow, startCellColumn),
                         _map.getCell(endCellRow, endCellColumn));
}

Cell World::getImpactCell(AbilityName abilityName, int startCellRow, int startCellColumn, int endCellRow,
                         int endCellColumn) {
    if (!_map.isInMap(startCellRow, startCellColumn) || !_map.isInMap(endCellRow, endCellColumn))
        return Cell::NULL_CELL;
    return getImpactCell(abilityName, _map.getCell(startCellRow, startCellColumn), _map.getCell(endCellRow,
                                                                                              endCellColumn));
}

bool World::isInVision(Cell &startCell, Cell &endCell) {
    if (startCell == Cell::NULL_CELL || endCell == Cell::NULL_CELL ||
            startCell.isWall() || endCell.isWall())
        return false;
    std::vector<Cell *> rayCells = getRayCells(startCell, endCell);
    if(rayCells.size() == 0)
        return false;
    Cell lastCell = *(rayCells.back());
    return lastCell == endCell;
}

bool World::isInVision(int startCellRow, int startCellColumn, int endCellRow, int endCellColumn) {
    if (!_map.isInMap(startCellRow, startCellColumn) || !_map.isInMap(endCellRow, endCellColumn))
        return false;
    return isInVision(_map.getCell(startCellRow, startCellColumn), _map.getCell(endCellRow, endCellColumn));
}

//--------------private----------------
AbilityConstants World::getAbilityConstants(AbilityName abilityName) {
    for (AbilityConstants * abilityConstants : this->_abilityConstants)
    {
        if (abilityConstants->getName() == abilityName)
        {
            return *abilityConstants;
        }
    }
    return AbilityConstants::NULL_ABILITY_CONSTANTS;
}


HeroConstants World::getHeroConstants(HeroName heroName) {
    for (HeroConstants * heroConstants : this->_heroConstants)
    {
        if(heroConstants->getName() == heroName){
            return *heroConstants;
        }
    }
    return HeroConstants::NULL_HERO_CONSTANT;
}

std::vector<Direction> World::getPathMoveDirections(Cell &startCell, Cell &endCell)
{
    if (startCell == endCell || startCell.isWall() || endCell.isWall() ||
            startCell == Cell::NULL_CELL || endCell == Cell::NULL_CELL){
        return std::vector<Direction>{};
    }
    // saves parent cell and direction to go from parent cell to current cell
    std::map<Cell*, std::pair<Cell*, Direction>> lastMoveInfo;
    Cell* bfsQueue[_map.getRowNum() * _map.getColumnNum() + 10];
    int queueHead = 0, queueTail = 0;

    lastMoveInfo.insert(std::pair<Cell*, std::pair<Cell*, Direction>>
                                (&startCell, std::pair<Cell*, Direction>(&Cell::NULL_CELL , NULL_DIRECTION)));
    bfsQueue[queueTail++] = &startCell;

    while (queueHead != queueTail)
    {
        Cell* currentCell = bfsQueue[queueHead++];
        if (*currentCell == endCell)
        {
            std::vector<Direction> directions;
            while (*currentCell != startCell)
            {
                directions.push_back(lastMoveInfo[currentCell].second);
                currentCell = lastMoveInfo[currentCell].first;
            }
            std::reverse(directions.begin(), directions.end());
            return directions;
        }
        for (int direction = UP; direction <= RIGHT; direction++)
        {
            Cell *nextCell = &getNextCell(*currentCell, static_cast<Direction>(direction));
            if (*nextCell != Cell::NULL_CELL && isAccessible(*nextCell) && (lastMoveInfo.find(nextCell)==lastMoveInfo.end()))
            {
                lastMoveInfo.insert(std::pair<Cell*, std::pair<Cell*, Direction>>(
                        nextCell, std::pair<Cell*, Direction>(currentCell, static_cast<Direction>(direction))));
                bfsQueue[queueTail++] = nextCell;
            }
        }
    }
    return std::vector<Direction>{};
}


std::vector<Direction>
World::getPathMoveDirections(int startCellRow, int startCellColumn, int endCellRow, int endCellColumn) {
    if(_map.isInMap(startCellRow,startCellColumn) && _map.isInMap(startCellRow,startCellColumn)){
        return getPathMoveDirections(
                this->_map.getCell(startCellRow,startCellColumn),
                this->_map.getCell(endCellRow,endCellColumn));
    }
    return std::vector<Direction>{};
}


bool World::isAccessible(int cellRow, int cellColumn) {
    if (!_map.isInMap(cellRow, cellColumn))
        return false;
    return !_map.getCell(cellRow, cellColumn).isWall();
}

bool World::isAccessible(const Cell &cell) {
    return !cell.isWall();
}

int &World::currentTurn() {
    return _currentTurn;
}

int World::currentTurn() const {
    return _currentTurn;
}

int World::movePhaaseNum() const {
    return _movePhaseNum;
}

Phase World::currentPhase() const {
    return _currentPhase;
}

void World::set_myHeroes(std::vector<Hero *> _heroes) {
    for(std::vector<Hero *>::iterator it = this->_myHeroes.begin();
            it != this->_myHeroes.end(); ++it){
        delete *it;
    }
    _myHeroes.clear();
    for(std::vector<Hero *>::iterator it = this->_myDeadHeroes.begin();
            it != this->_myDeadHeroes.end(); ++it){
        delete *it;
    }
    _myDeadHeroes.clear();

    _myHeroes = _heroes;
    for(std::vector<Hero *>::iterator it = _heroes.begin();
        it != _heroes.end(); ++it){
        if((*it)->getCurrentHP() == 0){
            this->_myDeadHeroes.push_back(*it);
        }
    }
}

void World::set_oppHeroes(std::vector<Hero *> _heroes) {
    for(std::vector<Hero *>::iterator it = this->_oppHeroes.begin();
            it != this->_oppHeroes.end(); ++it){
        delete *it;
    }
    _oppHeroes.clear();
    for(std::vector<Hero *>::iterator it = this->_oppDeadHeroes.begin();
            it != this->_oppDeadHeroes.end(); ++it){
        delete *it;
    }
    _oppDeadHeroes.clear();

    _oppHeroes = _heroes;
    for(std::vector<Hero *>::iterator it = _heroes.begin();
        it != _heroes.end(); ++it){
        if((*it)->getCurrentHP() == 0){
            _oppDeadHeroes.push_back(*it);
        }
    }
}

void World::set_myCastAbilities(std::vector<CastAbility *> _myCAbility) {
    for(std::vector<CastAbility *>::iterator it = this->_myCastAbilities.begin();
            it != this->_myCastAbilities.end(); ++it){
        delete *it;
    }

    this->_myCastAbilities = _myCAbility;
}

std::vector<CastAbility *> World::getMyCastAbilities() const {
    return _myCastAbilities;
}

void World::set_oppCastAbilities(std::vector<CastAbility *> _oppCAbility) {
    for(std::vector<CastAbility *>::iterator it = this->_oppCastAbilities.begin();
        it != this->_oppCastAbilities.end(); ++it){
        delete *it;
    }

    this->_oppCastAbilities = _oppCAbility;
}

std::vector<CastAbility *> World::getOppCastAbilities() const {
    return _oppCastAbilities;
}

void World::moveHero(int id, Direction direction) {

    _event_queue.push(
            CreateMoveMessage(id, Direction_to_string(direction), this->_currentTurn, this->_movePhaseNum)
    );
}


void World::moveHero(const Hero &hero, Direction direction) {

    _event_queue.push(
            CreateMoveMessage(hero.getId(), Direction_to_string(direction), this->_currentTurn, this->_movePhaseNum)
    );
}

void World::pickHero(HeroName heroName) {

    _event_queue.push(CreatePickMessage(HeroName_to_string(heroName), this->_currentTurn));
}

void World::castAbility(int heroId, AbilityName abilityName, int targetCellRow, int targetCellColumn) {

    _event_queue.push(
            CreateCastMessage(
                    heroId,
                    AbilityName_to_string(abilityName),
                    targetCellRow,
                    targetCellColumn,
                    this->_currentTurn));
}

void World::castAbility(int heroId, AbilityName abilityName,const Cell &targetCell) {
    castAbility(heroId,abilityName, targetCell.getRow(), targetCell.getColumn());
}

void World::castAbility(int heroId, Ability ability, int targetCellRow, int targetCellColumn) {
    castAbility(heroId, ability.getName(),targetCellRow,targetCellColumn);
}

void World::castAbility(int heroId, Ability ability,const Cell &targetCell) {
    castAbility(heroId, ability.getName(), targetCell.getRow(), targetCell.getColumn());
}

void World::castAbility(const Hero &hero, Ability ability,const Cell &targetCell) {
    castAbility(hero.getId(), ability.getName(), targetCell.getRow(), targetCell.getColumn());
}

void World::castAbility(const Hero &hero, AbilityName abilityName, int targetCellRow, int targetCellColumn) {
    castAbility(hero.getId(),abilityName,targetCellRow,targetCellColumn);
}

void World::castAbility(const Hero &hero, AbilityName abilityName,const Cell &targetCell) {
    castAbility(hero.getId(),abilityName, targetCell.getRow(), targetCell.getColumn());
}

void World::castAbility(const Hero &hero, Ability ability, int targetCellRow, int targetCellColumn) {
    castAbility(hero.getId(), ability.getName(),targetCellRow,targetCellColumn);
}

void World::initData() {
    this->_AP = this->_gameConstants.getMaxAP();
    this->_myScore = 0;
    this->_oppScore = 0;
    this->_currentTurn = 0;
    this->_movePhaseNum = 0;
    this->_currentPhase = Phase::PICK;
}

void World::set_abilityConstants(const std::vector<AbilityConstants *> &_abilityConstants) {
    //Clear the past values:
    for (AbilityConstants * _abilityConst : this->_abilityConstants){
        delete _abilityConst;
    }
    this->_abilityConstants.clear();
    //Write the data
    for(AbilityConstants * _abilityConst : _abilityConstants){
        AbilityConstants * tmp_abilityConst = new AbilityConstants(*_abilityConst);
        this->_abilityConstants.push_back(tmp_abilityConst);
    }
}

void World::set_heroConstants(const std::vector<HeroConstants *> &_heroConstants) {
    //Clear the past values:
    for (HeroConstants * _heroConst : this->_heroConstants){
        delete _heroConst;
    }
    this->_heroConstants.clear();
    //Write the data
    for(HeroConstants * _heroConst : _heroConstants){
        HeroConstants * tmp_heroConst = new HeroConstants(*_heroConst);
        this->_heroConstants.push_back(tmp_heroConst);
    }
}

Map &World::getMap() {
    return this->_map;
}

std::vector<AbilityConstants *> World::getAbilityConstants() const {
    return _abilityConstants;
}

std::vector<HeroConstants *> World::getHeroConstants() const {
    return _heroConstants;
}

int World::getAP() {
    return _AP;
}

int World::getMyScore() {
    return _myScore;
}

int World::getOppScore() {
    return _oppScore;
}

int World::getCurrentTurn() {
    return _currentTurn;
}

Phase World::getCurrentPhase() {
    return _currentPhase;
}

int World::getMaxScore() {
    return _gameConstants.getMaxScore();
}

int World::getMaxAP() {
    return _gameConstants.getMaxAP();
}

int World::getMaxTurns() {
    return _gameConstants.getMaxTurns();
}

int World::getKillScore() {
    return _gameConstants.getKillScore();
}

int World::getObjectiveZoneScore() {
    return _gameConstants.getObjectiveZoneScore();
}

int World::getMovePhaseNum() {
    return _movePhaseNum;
}

int World::getMaxOvertime() {
    return _maxOvertime;
}

int World::getRemainingOvertime() {
    return _remainingOvertime;
}


std::vector<Hero *> World::getMyHeroes() const {
    return _myHeroes;
}

std::vector<Hero *> World::getOppHeroes() const {
    return _oppHeroes;
}

std::vector<Hero *> World::getMyDeadHeroes() const {
    return _myDeadHeroes;
}

std::vector<Hero *> World::getOppDeadHeroes() const {
    return _oppDeadHeroes;
}

std::vector<Hero *> World::getAbilityTargets(AbilityName abilityName, Cell &startCell, Cell &targetCell) {
    AbilityConstants abilityConstants = getAbilityConstants(abilityName);
    if (abilityConstants == AbilityConstants::NULL_ABILITY_CONSTANTS ||
            startCell == Cell::NULL_CELL || targetCell == Cell::NULL_CELL) {
        return std::vector<Hero *>{};
    }
    std::vector<Cell *> impactCells = getImpactCells(abilityName, startCell, targetCell);
    std::vector<Cell *> affectedCells{};
    if(impactCells.size() > 1){
        affectedCells.insert(affectedCells.end(),impactCells.begin(),impactCells.end());
    } else {
        affectedCells = getCellsInAOE(*impactCells.back(),
                                                          abilityConstants.getAreaOfEffect());
    }
    if (abilityConstants.getType() == AbilityType::DEFENSIVE) {
        return getMyHeroesInCells(affectedCells);
    } else {
        return getOppHeroesInCells(affectedCells);
    }
}

std::vector<Hero *> World::getAbilityTargets(Ability ability, Cell &startCell, Cell &targetCell) {
    if (ability == Ability::NULL_ABILITY) {
        return std::vector<Hero *>{};
    }
    return getAbilityTargets(ability.getName(), startCell, targetCell);
}

std::vector<Hero *>
World::getAbilityTargets(AbilityName abilityName, int startCellRow, int startCellColumn, int targetCellRow,
                         int targetCellColumn) {
    if (!_map.isInMap(startCellRow, startCellColumn) || !_map.isInMap(targetCellRow, targetCellColumn))
        return std::vector<Hero *>{};
    return getAbilityTargets(abilityName,
                             _map.getCell(startCellRow, startCellColumn),
                             _map.getCell(targetCellRow, targetCellColumn));
}

std::vector<Hero *> World::getAbilityTargets(Ability ability, int startCellRow, int startCellColumn, int targetCellRow,
                                             int targetCellColumn) {
    if (ability == Ability::NULL_ABILITY || !_map.isInMap(startCellRow, startCellColumn) || !_map.isInMap(targetCellRow, targetCellColumn))
        return std::vector<Hero *>{};
    return getAbilityTargets(ability.getName(),
                             _map.getCell(startCellRow, startCellColumn),
                             _map.getCell(targetCellRow, targetCellColumn));

}

std::vector<Cell *> World::getCellsInAOE(const Cell &impactCell, int AOE) {
    if (impactCell == Cell::NULL_CELL) {
        return std::vector<Cell *>{};
    }
    std::vector<Cell *> cells;
    for (int row = impactCell.getRow() - AOE; row <= impactCell.getRow() + AOE; row++) {
        for (int col = impactCell.getColumn() - AOE; col <= impactCell.getColumn() + AOE; col++) {
            if (!_map.isInMap(row, col)) continue;
            Cell* cell = _map.getCell_ptr(row, col);
            if (manhattanDistance(impactCell, *cell) <= AOE)
                cells.push_back(cell);
        }
    }
    return cells;
}

std::vector<Hero *> World::getMyHeroesInCells(std::vector<Cell *> cells) {
    if (cells.empty()) {
        return std::vector<Hero *>{};
    }
    std::vector<Hero *> heroes;
    for (Cell* cell : cells) {
        Hero* hero = getMyHero_ptr(*cell);
        if (*hero != Hero::NULL_HERO) {
            heroes.push_back(hero);
        }
    }
    return heroes;
}

std::vector<Hero *> World::getOppHeroesInCells(std::vector<Cell *> cells) {
    if (cells.empty()) {
        return std::vector<Hero *>{};
    }
    std::vector<Hero *> heroes;
    for (Cell* cell : cells) {
        Hero* hero = getOppHero_ptr(*cell);
        if (*hero != Hero::NULL_HERO) {
            heroes.push_back(hero);
        }
    }
    return heroes;
}

bool World::isInCells(const Cell &_cell, std::vector<Cell *> _cellList) {
    for(Cell * sampleCell : _cellList){
        if(_cell == *sampleCell)
            return true;
    }
    return false;
}

std::vector<Direction>
World::getPathMoveDirections(Cell &startCell, Cell &endCell, std::vector<Cell *> _avoidingCells) {

    if (startCell == endCell || startCell.isWall() || endCell.isWall() ||
        startCell == Cell::NULL_CELL || endCell == Cell::NULL_CELL ||
            isInCells(startCell,_avoidingCells) || isInCells(endCell,_avoidingCells)){
        return std::vector<Direction>{};
    }
    // saves parent cell and direction to go from parent cell to current cell
    std::map<Cell*, std::pair<Cell*, Direction>> lastMoveInfo;
    Cell* bfsQueue[_map.getRowNum() * _map.getColumnNum() + 10];
    int queueHead = 0, queueTail = 0;

    lastMoveInfo.insert(std::pair<Cell*, std::pair<Cell*, Direction>>
                                (&startCell, std::pair<Cell*, Direction>(&Cell::NULL_CELL , NULL_DIRECTION)));
    bfsQueue[queueTail++] = &startCell;

    while (queueHead != queueTail)
    {
        Cell* currentCell = bfsQueue[queueHead++];
        if (*currentCell == endCell)
        {
            std::vector<Direction> directions;
            while (*currentCell != startCell)
            {
                directions.push_back(lastMoveInfo[currentCell].second);
                currentCell = lastMoveInfo[currentCell].first;
            }
            std::reverse(directions.begin(), directions.end());
            return directions;
        }
        for (int direction = UP; direction <= RIGHT; direction++)
        {
            Cell *nextCell = &getNextCell(*currentCell, static_cast<Direction>(direction));
            if (*nextCell != Cell::NULL_CELL &&
                    isAccessible(*nextCell) &&
                    (lastMoveInfo.find(nextCell)==lastMoveInfo.end()) &&
                    !isInCells(*nextCell,_avoidingCells))
            {
                lastMoveInfo.insert(std::pair<Cell*, std::pair<Cell*, Direction>>(
                        nextCell, std::pair<Cell*, Direction>(currentCell, static_cast<Direction>(direction))));
                bfsQueue[queueTail++] = nextCell;
            }
        }
    }
    return std::vector<Direction>{};
}

std::vector<Direction>
World::getPathMoveDirections(int startCellRow, int startCellColumn, int endCellRow, int endCellColumn,
                             std::vector<Cell *> _avoidingCells) {

    if(_map.isInMap(startCellRow,startCellColumn) && _map.isInMap(startCellRow,startCellColumn)){
        return getPathMoveDirections(
                this->_map.getCell(startCellRow,startCellColumn),
                this->_map.getCell(endCellRow,endCellColumn),
                _avoidingCells);
    }
    return std::vector<Direction>{};
}

int World::getMaxScoreDiff() {
    return _gameConstants.getMaxScoreDiff();
}

int World::getInitOvertime() {
    return _gameConstants.getInitOvertime();
}

int World::getTotalMovePhases() {
    return _gameConstants.getTotalMovePhases();
}



