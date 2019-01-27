//
// Created by dot_blue on 1/23/19.
//

#include "Game.h"
//----------------map------------------
const Map &Game::get_map() const {
    return _map;
}

void Game::set_map(const Map &_map) {
    Game::_map = _map;
}

Map &Game::map() {
    return _map;
}
//------------gameConstants------------
const GameConstants &Game::get_gameConstants() const {
    return _gameConstants;
}

void Game::set_gameConstants(const GameConstants &_gameConstants) {
    Game::_gameConstants = _gameConstants;
}

GameConstants &Game::gameConstants() {
    return _gameConstants;
}
////------------abilityConstants---------
//const AbilityConstants &Game::get_abilityConstants() const {
//    return _abilityConstants;
//}
//
//void Game::set_abilityConstants(const AbilityConstants &_abilityConstants) {
//    Game::_abilityConstants = _abilityConstants;
//}
//
//AbilityConstants &Game::abilityConstants() {
//    return _abilityConstants;
//}
////--------------heroConstants----------
//const HeroConstants &Game::get_heroConstants() const {
//    return _heroConstants;
//}
//
//void Game::set_heroConstants(const HeroConstants &_heroConstants) {
//    Game::_heroConstants = _heroConstants;
//}
//
//HeroConstants &Game::heroConstants() {
//    return _heroConstants;
//}
//-----------------AP------------------
int Game::get_AP() const {
    return _AP;
}

void Game::set_AP(int _AP) {
    Game::_AP = _AP;
}

int &Game::AP() {
    return _AP;
}
//----------------score----------------
int Game::get_score() const {
    return _score;
}

void Game::set_score(int _score) {
    Game::_score = _score;
}

int &Game::score() {
    return _score;
}

Game::~Game() {
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

    for (std::vector<Cell *>::iterator it = _brokenWalls.begin() ; it != _brokenWalls.end(); ++it){
        delete *it;
    }
    _brokenWalls.clear();

    for (std::vector<Cell *>::iterator it = _createdWalls.begin() ; it != _createdWalls.end(); ++it){
        delete *it;
    }
    _createdWalls.clear();

}
//logical functions:
Hero Game::getHero(int id) {
    for(std::vector<Hero *>::iterator it = _myHeroes.begin(); it != _myHeroes.end(); ++it){
        if((*it)->get_id() == id){
            return **it;
        }
    }
    for(std::vector<Hero *>::iterator it = _oppHeroes.begin(); it != _oppHeroes.end(); ++it){
        if((*it)->get_id() == id){
            return **it;
        }
    }
    return Hero::NULL_HERO;
}

Hero Game::getMyHero(Cell cell) {
    for(std::vector<Hero *>::iterator it = _myHeroes.begin(); it != _myHeroes.end(); ++it ){
        //This only checks the location of the cell
        if((*it)->get_currentCell() == cell){
            return **it;
        }
    }
    return Hero::NULL_HERO;
}


Hero Game::getMyHero(int cellRow, int cellColumn) {
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

Hero Game::getOppHero(Cell cell) {
    for(std::vector<Hero *>::iterator it = _oppHeroes.begin(); it!= _oppHeroes.end(); ++it){
        //This only checks the location of the cell
        if((*it)->get_currentCell() == cell){
            return **it;
        }
    }
    return Hero::NULL_HERO;
}

Hero Game::getOppHero(int cellRow, int cellColumn) {
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

int Game::manhattanDistance(Cell startCell, Cell endCell) {
    return abs(startCell.row() - endCell.row()) +
            abs(startCell.column() - endCell.column());
}

int Game::manhattanDistance(int startCellRow, int startCellColumn, int endCellRow, int endCellColumn) {
    if(this->_map.isInMap(startCellRow,startCellColumn) && this->_map.isInMap(endCellRow,endCellColumn)){
        return abs(startCellRow - endCellRow) + abs(startCellColumn - endCellColumn);
    } else {
        return -1;
    }

}

//------------Algorithmic--------------

Cell Game::getNextCell(const Cell &cell, const Direction& direction) {
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
int Game::crossProduct(int x1, int y1, int x2, int y2, int x3, int y3)
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
int Game::squareCollision(const Cell& startCell,const Cell& targetCell,const Cell& cell)
{
    bool hasNegative = false, hasPositive = false, hasZero = false;
    for (int row = 2 * cell.row(); row <= 2 * (cell.row() + 1); row += 2)
        for (int column = 2 * cell.column(); column <= 2 * (cell.column() + 1); column += 2)
        {
            int crossProduct = crossProduct(2 * startCell.row() + 1, 2 * startCell.column() + 1,
                                            2 * targetCell.row() + 1, 2 * targetCell.column() + 1, row, column);
            if (crossProduct < 0) hasNegative = true;
            else if (crossProduct > 0) hasPositive = true;
            else hasZero = true;
        }
    if (hasNegative && hasPositive) return 1;
    if (hasZero) return 0;
    return -1;
}

bool Game::isCloser(Cell currentCell, Cell targetCell, Cell nextCell)
{
    return manhattanDistance(nextCell, targetCell) <= manhattanDistance(currentCell, targetCell);
}

void Game::dfs(Cell& currentCell, const Cell& startCell, const Cell& targetCell, std::unordered_map<Cell, bool>& isSeen,
               std::vector<Cell *>& path) {
    isSeen[currentCell] = true;
    path.push_back(&currentCell);
    //TODO make sure the Direction enum is not initialized!
    for (int dir = Direction::UP; dir != Direction::RIGHT; dir++ )//(Direction direction : Direction.values())
    {
        Direction direction = static_cast<Direction>(dir);
        Cell nextCell = getNextCell(currentCell, direction);
        if (nextCell != Cell::NULL_CELL && isSeen.find(nextCell) == isSeen.end() && isCloser(currentCell, targetCell, nextCell))
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
            //TODO: assumed isSeen.find(nextCell) == isSeen.end() means it's not found...
            if (nextCell != Cell::NULL_CELL && isSeen.find(nextCell) == isSeen.end() && isCloser(currentCell, targetCell, nextCell))
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
std::vector<Cell *> Game::getRayCells(Cell startCell, Cell endCell) {
    std::vector<Cell *> path;
    std::unordered_map<Cell, bool> _isSeen;
    dfs(startCell,startCell,endCell,_isSeen,path);
    return path;
}

std::vector<Cell *> Game::getImpactCells(AbilityName abilityName, Cell startCell, Cell targetCell) {
    AbilityConstants abilityConstants = getAbilityConstants(abilityName);
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
    if (std::find(impactCells.begin(), impactCells.end(), &lastCell) != impactCells.end())//does not contain!
        impactCells.push_back(lastCell);
    return impactCells;
}


Cell Game::getImpactCell(AbilityName abilityName, Cell startCell, Cell targetCell) {
    std::vector<Cell *> impactCells = getImpactCells(abilityName, startCell, targetCell);
    return *(impactCells.back());
}


Cell Game::getImpactCell(Ability ability, Cell startCell, Cell targetCell) {
    return Cell();
}



//--------------private----------------
AbilityConstants Game::getAbilityConstants(AbilityName abilityName) {
    for (AbilityConstants * abilityConstants : this->_abilityConstants)
    {
        if (abilityConstants->abilityName() == abilityName)
        {
            return *abilityConstants;
        }
    }
    return AbilityConstants::NULL_ABILITY_CONSTANTS;
}






