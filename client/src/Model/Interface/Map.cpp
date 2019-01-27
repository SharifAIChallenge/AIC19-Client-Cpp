#include "Map.h"
//--------------rowNum-----------------
int Map::get_rowNum() const {
    return _rowNum;
}

void Map::set_rowNum(int _rowNum) {
    Map::_rowNum = _rowNum;
}

int &Map::rowNum() {
    return _rowNum;
}

int Map::rowNum() const {
    return _rowNum;
}

//------------columnNum----------------
int Map::get_columnNum() const {
    return _columnNum;
}

void Map::set_columnNum(int _columnNum) {
    Map::_columnNum = _columnNum;
}

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

