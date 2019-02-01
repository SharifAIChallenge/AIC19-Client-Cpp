#include "World.h"

World::World(EventQueue &event_queue): _event_queue(event_queue){

}


World::World(World &_world): _event_queue(_world._event_queue) {
    this->_gameConstants = _world._gameConstants;
    this->_abilityConstants = _world._abilityConstants;
    this->_map = _world._map;
    this->_heroConstants = _world._heroConstants;
}


//----------------map------------------
const Map &World::get_map() const {
    return _map;
}

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
int &World::AP() {
    return _AP;
}

int World::AP() const{
    return _AP;
}
//--------------myScore----------------
int &World::myScore() {
    return _myScore;
}

int World::myScore() const {
    return _myScore;
}
//-------------oppScore----------------
int &World::oppScore() {
    return _oppScore;
}

int World::oppScore() const {
    return _oppScore;
}

World::~World() {
    for (std::vector<Hero *>::iterator it = _myHeroes.begin() ; it != _myHeroes.end(); ++it){
        delete *it;
    }
    _myHeroes.clear();

    for (std::vector<Hero *>::iterator it = _oppHeroes.begin() ; it != _oppHeroes.end(); ++it){
        delete *it;
    }
    _oppHeroes.clear();

    for (std::vector<Hero *>::iterator it = _myDeadHeroes.begin() ; it != _myDeadHeroes.end(); ++it){
        delete *it;
    }
    _myDeadHeroes.clear();

    for (std::vector<Hero *>::iterator it = _oppDeadHeroes.begin() ; it != _oppDeadHeroes.end(); ++it){
        delete *it;
    }
    _oppDeadHeroes.clear();

    for (std::vector<CastAbility *>::iterator it = _myCastAbilities.begin() ; it != _myCastAbilities.end(); ++it){
        delete *it;
    }
    _myCastAbilities.clear();

    for (std::vector<CastAbility *>::iterator it = _oppCastAbilities.begin() ; it != _oppCastAbilities.end(); ++it){
        delete *it;
    }
    _oppCastAbilities.clear();

}
//logical functions:
Hero World::getHero(int id) {
    for(std::vector<Hero *>::iterator it = _myHeroes.begin(); it != _myHeroes.end(); ++it){
        if(static_cast<const Hero *>(*it)->id() == id){
            return **it;
        }
    }
    for(std::vector<Hero *>::iterator it = _oppHeroes.begin(); it != _oppHeroes.end(); ++it){
        if(static_cast<const Hero *>(*it)->id() == id){
            return **it;
        }
    }
    return Hero::NULL_HERO;
}

Hero World::getMyHero(Cell cell) {
    for(std::vector<Hero *>::iterator it = _myHeroes.begin(); it != _myHeroes.end(); ++it ){
        //This only checks the location of the cell
        if((*it)->currentCell() == cell){
            return **it;
        }
    }
    return Hero::NULL_HERO;
}


Hero World::getMyHero(int cellRow, int cellColumn) {
    if(!_map.isInMap(cellRow,cellColumn))
        return Hero::NULL_HERO;

    for(std::vector<Hero *>::iterator it = _myHeroes.begin(); it != _myHeroes.end(); ++it ){
        //This only checks the location of the cell
        if((*it)->currentCell().row() == cellRow &&
           (*it)->currentCell().row() == cellColumn){
            return **it;
        }
    }
    return Hero::NULL_HERO;
}

Hero World::getOppHero(Cell cell) {
    for(std::vector<Hero *>::iterator it = _oppHeroes.begin(); it!= _oppHeroes.end(); ++it){
        //This only checks the location of the cell
        if((*it)->currentCell() == cell){
            return **it;
        }
    }
    return Hero::NULL_HERO;
}

Hero World::getOppHero(int cellRow, int cellColumn) {
    if(!_map.isInMap(cellRow,cellColumn))
        return Hero::NULL_HERO;

    for(std::vector<Hero *>::iterator it = _oppHeroes.begin(); it!= _oppHeroes.end(); ++it){
        //This only checks the location of the cell
        if((*it)->currentCell().row() == cellRow &&
           (*it)->currentCell().row() == cellColumn){
            return **it;
        }
    }
    return Hero::NULL_HERO;
}

int World::manhattanDistance(Cell startCell, Cell endCell) {
    return abs(startCell.row() - endCell.row()) +
            abs(startCell.column() - endCell.column());
}

int World::manhattanDistance(int startCellRow, int startCellColumn, int endCellRow, int endCellColumn) {
    if(this->_map.isInMap(startCellRow,startCellColumn) && this->_map.isInMap(endCellRow,endCellColumn)){
        return abs(startCellRow - endCellRow) + abs(startCellColumn - endCellColumn);
    } else {
        return -1;
    }

}

//------------Algorithmic--------------

Cell World::getNextCell(const Cell &cell, const Direction& direction) {
    switch (direction)
    {
        case Direction::UP:
            if (_map.isInMap(cell.row() - 1, cell.column()))
                return _map.getCell(cell.row() - 1, cell.column());
            else
                return Cell::NULL_CELL;
        case Direction::DOWN:
            if (_map.isInMap(cell.row() + 1, cell.column()))
                return _map.getCell(cell.row() + 1, cell.column());
            else
                return Cell::NULL_CELL;
        case Direction::LEFT:
            if (_map.isInMap(cell.row(), cell.column() - 1))
                return _map.getCell(cell.row(), cell.column() - 1);
            else
                return Cell::NULL_CELL;
        case Direction::RIGHT:
            if (_map.isInMap(cell.row(), cell.column() + 1))
                return _map.getCell(cell.row(), cell.column() + 1);
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
    for (int row = 2 * cell.row(); row <= 2 * (cell.row() + 1); row += 2)
        for (int column = 2 * cell.column(); column <= 2 * (cell.column() + 1); column += 2)
        {
            int _crossProduct = crossProduct(2 * startCell.row() + 1, 2 * startCell.column() + 1,
                                            2 * targetCell.row() + 1, 2 * targetCell.column() + 1, row, column);
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
               std::vector<Cell *>& path) {
    isSeen[&currentCell] = true;
    path.push_back(&currentCell);
    //make sure the "Direction" enum is not initialized!
    for (int dir = Direction::UP; dir <= Direction::RIGHT ; dir++ )//(Direction direction : Direction.values())
    {
        Direction direction = static_cast<Direction>(dir);
        Cell nextCell = getNextCell(currentCell, direction);
        if (nextCell != Cell::NULL_CELL && isSeen.find(&nextCell) == isSeen.end() && isCloser(currentCell, targetCell, nextCell))
        {
            int collisionState = squareCollision(startCell, targetCell, nextCell);
            if ((collisionState == 0 || collisionState == 1) && nextCell.isWall())
                return;
            if (collisionState == 1)
            {
                dfs(nextCell, startCell, targetCell, isSeen, path);
                return;
            }
        }
    }
    for (int dRow = -1; dRow <= 1; dRow += 2)
        for (int dColumn = -1; dColumn <= 1; dColumn += 2)
        {
            int newRow = currentCell.row() + dRow;
            int newColumn = currentCell.column() + dColumn;
            Cell nextCell = Cell::NULL_CELL;
            if (_map.isInMap(newRow, newColumn)) nextCell = _map.getCell(newRow, newColumn);
            //Assumed isSeen.find(nextCell) == isSeen.end() means it's not found...
            if (nextCell != Cell::NULL_CELL && isSeen.find(&nextCell) == isSeen.end() && isCloser(currentCell, targetCell, nextCell))
            {
                int collisionState = squareCollision(startCell, targetCell, nextCell);
                if (collisionState == 0 || collisionState == 1 && nextCell.isWall())
                    return;
                if (collisionState == 1)
                {
                    dfs(nextCell, startCell, targetCell, isSeen, path);
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
std::vector<Cell *> World::getRayCells(Cell startCell, Cell endCell) {
    std::vector<Cell *> path;
    std::unordered_map<Cell*, bool> _isSeen;
    dfs(startCell,startCell,endCell,_isSeen,path);
    return path;
}

std::vector<Cell *> World::getImpactCells(AbilityName abilityName, Cell startCell, Cell targetCell) {
    const AbilityConstants abilityConstants = getAbilityConstants(abilityName);
    if (abilityConstants.isLobbing())
    {
        std::vector<Cell *> targetCellVec{&targetCell};
        return targetCellVec;
    }
    if (startCell.isWall() || startCell == targetCell)
    {
        std::vector<Cell *> startCellVec{&startCell};
        return startCellVec;
    }
    std::vector<Cell *> impactCells;
    std::vector<Cell *> rayCells = getRayCells(startCell, targetCell);
    Cell* lastCell = &Cell::NULL_CELL;
    for (std::vector<Cell *>::iterator cellIt = rayCells.begin(); cellIt !=rayCells.end(); ++cellIt) {

        if (manhattanDistance(startCell, **cellIt) > abilityConstants.range())
            break;
        lastCell = *cellIt;
        if ((getOppHero(**cellIt) != Hero::NULL_HERO && !(abilityConstants.type() == AbilityType::HEAL))
            || (getMyHero(**cellIt) != Hero::NULL_HERO && abilityConstants.type() == AbilityType::HEAL))
        {
            impactCells.push_back(*cellIt);
            if (!abilityConstants.isPiercing()) break;
        }
    }
    if (std::find(impactCells.begin(),
                  impactCells.end(), lastCell)
        != impactCells.end())//does not contain!
        impactCells.push_back(lastCell);
    return impactCells;
}


Cell World::getImpactCell(AbilityName abilityName, Cell startCell, Cell targetCell) {
    std::vector<Cell *> impactCells = getImpactCells(abilityName, startCell, targetCell);
    return *(impactCells.back());
}


Cell World::getImpactCell(Ability ability, Cell startCell, Cell targetCell) {
    return getImpactCell(ability.getAbilityConstants().getAbilityName(), startCell, targetCell);
}

Cell World::getImpactCell(Ability ability, int startCellRow, int startCellColumn, int endCellRow, int endCellColumn) {
    if (!_map.isInMap(startCellRow, startCellColumn) || !_map.isInMap(endCellRow, endCellColumn))
        return Cell::NULL_CELL;
    return getImpactCell(ability.getAbilityConstants().getAbilityName(), _map.getCell(startCellRow, startCellColumn),
                         _map.getCell(endCellRow, endCellColumn));
}

Cell World::getImpactCell(AbilityName abilityName, int startCellRow, int startCellColumn, int endCellRow,
                         int endCellColumn) {
    if (!_map.isInMap(startCellRow, startCellColumn) || !_map.isInMap(endCellRow, endCellColumn))
        return Cell::NULL_CELL;
    return getImpactCell(abilityName, _map.getCell(startCellRow, startCellColumn), _map.getCell(endCellRow,
                                                                                              endCellColumn));
}

bool World::isInVision(Cell startCell, Cell endCell) {
    if (startCell.isWall() || endCell.isWall())
        return false;
    std::vector<Cell *> rayCells = getRayCells(startCell, endCell);
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
        if (abilityConstants->getAbilityName() == abilityName)
        {
            return *abilityConstants;
        }
    }
    return AbilityConstants::NULL_ABILITY_CONSTANTS;
}


HeroConstants World::getHeroConstants(HeroName heroName) {
    for (HeroConstants * heroConstants : this->_heroConstants)
    {
        if(heroConstants->name() == heroName){
            return *heroConstants;
        }
    }
    return HeroConstants::NULL_HERO_CONSTANT;
}

std::vector<Direction> World::getPathMoveDirections(Cell& startCell, Cell& endCell)
{
    if (startCell == endCell || startCell.isWall() || endCell.isWall()){
        std::vector<Direction> vec = {};
        return vec;
    }

    // saves parent cell and direction to go from parent cell to current cell
    std::map<Cell*, std::pair<Cell, Direction>> lastMoveInfo;
    Cell* bfsQueue = new Cell[_map.rowNum() * _map.columnNum() + 10];
    int queueHead = 0, queueTail = 0;

    lastMoveInfo.insert(std::pair<Cell*, std::pair<Cell, Direction>>
                                (&startCell, std::pair<Cell, Direction>(Cell::NULL_CELL , NULL_DIRECTION)));
    bfsQueue[queueTail++] = startCell;

    while (queueHead != queueTail)
    {
        Cell currentCell = bfsQueue[queueHead++];
        if (currentCell == endCell)
        {
            std::vector<Direction> directions;
            while (currentCell != startCell)
            {
                directions.insert(directions.end(), lastMoveInfo[&currentCell].second);
                currentCell = lastMoveInfo[&currentCell].first;
            }
            reverse(directions.begin(), directions.end());
            return directions;
        }
        for (int direction = UP; direction <= RIGHT; direction++)
        {
            Cell nextCell = getNextCell(currentCell, static_cast<Direction>(direction));
            if (nextCell != Cell::NULL_CELL && !lastMoveInfo.count(&nextCell))
            {
                lastMoveInfo.insert(std::pair<Cell*,
                        std::pair<Cell, Direction>>(&nextCell,
                                                    std::pair<Cell, Direction>(currentCell, static_cast<Direction>(direction))));
                bfsQueue[queueTail++] = nextCell;
            }
        }
    }
    std::vector<Direction> vec = {};
    return vec;
}

bool World::isAccessible(int cellRow, int cellColumn) {
    if (!_map.isInMap(cellRow, cellColumn))
        return false;
    return !_map.getCell(cellRow, cellColumn).isWall();
}

int &World::currentTurn() {
    return _currentTurn;
}

int World::currentTurn() const {
    return _currentTurn;
}

Phase &World::currentPhase() {
    return _currentPhase;
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

    _oppDeadHeroes = _heroes;
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

std::vector<CastAbility *> World::get_myCastAbilities() const {
    return _myCastAbilities;
}

void World::set_oppCastAbilities(std::vector<CastAbility *> _oppCAbility) {
    for(std::vector<CastAbility *>::iterator it = this->_oppCastAbilities.begin();
        it != this->_oppCastAbilities.end(); ++it){
        delete *it;
    }

    this->_oppCastAbilities = _oppCAbility;
}

std::vector<CastAbility *> World::get_oppCastAbilities() const {
    return _oppCastAbilities;
}

void World::moveHero(int id, std::vector<Direction> directions) {
    Json::Value directionJsonVals;
    for(int i = 0; i < directions.size(); i++){
        directionJsonVals.append(std::to_string(directions[i]));
    }
    _event_queue.push(CreateMoveMessage(id,directionJsonVals));
}

void World::pickHero(HeroName heroName) {

    _event_queue.push(CreatePickMessage(HeroName_to_string(heroName)));
}

void World::castAbility(int heroId, AbilityName abilityName, int targetCellRow, int targetCellColumn) {

    _event_queue.push(
            CreateCastMessage(
                    heroId,
                    abilityName_to_string(abilityName),
                    targetCellRow,
                    targetCellColumn));
}

void World::importInitData(InitMessage &_initMessage) {

    this->_map = _initMessage.parse_map();
    this->_gameConstants = _initMessage.parse_gameConstants();
    this->_heroConstants = _initMessage.parse_heroConstants();
    this->_abilityConstants = _initMessage.parse_abilityConstants();

    this->_currentTurn = 0;
    this->_currentPhase = Phase::PICK;
    this->_myScore = 0;
    this->_oppScore = 0;
    this->_AP = this->_gameConstants.get_maxAP();

}
//
//void World::importPickData(PickMessage &_pickMessage) {
//    _pickMessage.update_game(this);
//}
//
//void World::importTurnData(TurnMessage &_turnMessage) {
//    _turnMessage.update_game(this);
//
//}











