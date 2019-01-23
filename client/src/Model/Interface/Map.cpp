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

