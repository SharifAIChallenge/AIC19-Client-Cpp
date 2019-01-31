#include "Map.h"


Map::Map(const std::vector<std::vector<Cell *>> &cells_grid) {
    this->set_cells(cells_grid);
}

//--------------rowNum-----------------
int &Map::rowNum() {
    return _rowNum;
}

int Map::rowNum() const {
    return _rowNum;
}

//------------columnNum----------------
int &Map::columnNum() {
    return _columnNum;
}

int Map::columnNum() const {
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

    for (std::vector<Cell *>::iterator it = _objectiveZone.begin() ; it != _objectiveZone.end(); ++it)
    {
        delete (*it);
    }
    _objectiveZone.clear();

    for (std::vector<Cell *>::iterator it = _myRespawnZone.begin() ; it != _myRespawnZone.end(); ++it)
    {
        delete (*it);
    }
    _myRespawnZone.clear();

    for (std::vector<Cell *>::iterator it = _oppRespawnZone.begin() ; it != _oppRespawnZone.end(); ++it)
    {
        delete (*it);
    }
    _oppRespawnZone.clear();

}

Cell Map::getCell(int row, int column) {//TODO::TEST check if row and column is in the write place
    return *_cells[row][column];
}

bool Map::isInMap(int row, int column) {
    return (0 <= row && row < _rowNum) &&
            (0 <= column && column < _columnNum);
}

void Map::clear_cells() {
    for (Cell* cell : get_cells_list())
        delete cell;
    this->_cells.clear();

}

std::vector<Cell *> Map::get_cells_list() const {
    return flatten_list(this->_cells);
}

void Map::set_cells(const std::vector<std::vector<Cell *>> &cells_grid) {
    clear_cells();
    this->_cells = cells_grid;

    std::vector<Cell *> cell_list = this->get_cells_list();
    for(std::vector<Cell *>::iterator it = cell_list.begin(); it != cell_list.end(); ++it){
        if((*it)->isInMyRespawnZone())
            this->_myRespawnZone.push_back(*it);
        if((*it)->isInOppRespawnZone())
            this->_oppRespawnZone.push_back(*it);
        if((*it)->isInObjectiveZone())
            this->_objectiveZone.push_back(*it);
    }
}

Cell *Map::getCell_ptr(int row, int column) {//TODO check row and column...
    return _cells[row][column];
}



