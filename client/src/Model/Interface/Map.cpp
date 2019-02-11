#include <Utility/Logger.h>
#include "Map.h"


Map::Map(const std::vector<std::vector<Cell *>> &cells_grid) {
    this->_set_cells(cells_grid);
}

//--------------rowNum-----------------
int Map::getRowNum() const {
    return _rowNum;
}

//------------columnNum----------------
int Map::getColumnNum() const {
    return _columnNum;
}

Map::~Map() {

    for (std::vector<std::vector<Cell *>>::iterator it = _cells.begin() ; it != _cells.end(); ++it)
    {
        for(std::vector<Cell *>::iterator p = it->begin() ; p != it->end(); ++p ) {
            delete (*p);
        }
        it->clear();
    }
    _cells.clear();

}

Cell& Map::getCell(int row, int column) {
    if(!isInMap(row,column))
        return Cell::NULL_CELL;
    return *(_cells[row][column]);
}

bool Map::isInMap(int row, int column) {
    return (0 <= row && row < _rowNum) &&
            (0 <= column && column < _columnNum);
}

void Map::_clear_cells() {
    for (Cell* cell : _get_cells_list())
        delete cell;
    this->_cells.clear();
    this->_myRespawnZone.clear();
    this->_oppRespawnZone.clear();
    this->_objectiveZone.clear();

}

std::vector<Cell *> Map::_get_cells_list() const {
    return flatten_list(this->_cells);
}

void Map::_set_cells(const std::vector<std::vector<Cell *>> &cells_grid) {//Allocate a new memory!!!
    this->_clear_cells();

    for(std::vector<Cell *> _row : cells_grid){
        std::vector<Cell *> tmp_cell_row;
        for(Cell * _cell : _row) {
            Cell * tmp_cell_ptr = new Cell(*_cell);
            tmp_cell_row.push_back(tmp_cell_ptr);
        }
        this->_cells.push_back(tmp_cell_row);
    }

//    this->_cells = cells_grid;

    std::vector<Cell *> cell_list = this->_get_cells_list();
    for(std::vector<Cell *>::iterator it = cell_list.begin(); it != cell_list.end(); ++it){
        if((*it)->isInMyRespawnZone())
            this->_myRespawnZone.push_back(*it);
        if((*it)->isInOppRespawnZone())
            this->_oppRespawnZone.push_back(*it);
        if((*it)->isInObjectiveZone())
            this->_objectiveZone.push_back(*it);
    }
}

Cell *Map::getCell_ptr(int row, int column) {
    if(!isInMap(row,column))
        return &Cell::NULL_CELL;
    return _cells[row][column];
}

Map::Map(const Map &_map) {

    this->_set_cells(_map._cells);
    this->_rowNum = _map._rowNum;
    this->_columnNum = _map._columnNum;
}

Map Map::operator=(const Map& _map) {

    this->_set_cells(_map._cells);
    this->_rowNum = _map._rowNum;
    this->_columnNum = _map._columnNum;

    return *this;
}

std::vector<std::vector<Cell *>>& Map::getCells() {
    return this->_cells;
}

std::vector<Cell *> &Map::getMyRespawnZone() {
    return this->_myRespawnZone;
}

std::vector<Cell *> &Map::getOppRespawnZone() {
    return this->_oppRespawnZone;
}

std::vector<Cell *> &Map::getObjectiveZone() {
    return this->_objectiveZone;
}





