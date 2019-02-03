#include <Utility/Logger.h>
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



//    for (std::vector<Cell *>::iterator it = _objectiveZone.begin() ; it != _objectiveZone.end(); ++it)
//    {
//        delete (*it);
//    }
//    _objectiveZone.clear();
//
//    for (std::vector<Cell *>::iterator it = _myRespawnZone.begin() ; it != _myRespawnZone.end(); ++it)
//    {
//        delete (*it);
//    }
//    _myRespawnZone.clear();
//
//    for (std::vector<Cell *>::iterator it = _oppRespawnZone.begin() ; it != _oppRespawnZone.end(); ++it)
//    {
//        delete (*it);
//    }
//    _oppRespawnZone.clear();

}


void Map::delete_Cells() {
    for (std::vector<std::vector<Cell *>>::iterator it = _cells.begin() ; it != _cells.end(); ++it)
    {
        for(std::vector<Cell *>::iterator p = it->begin() ; p != it->end(); ++p ) {
            delete (*p);
        }
        it->clear();
    }
    _cells.clear();
}


Cell Map::getCell(int row, int column) {
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

void Map::set_cells(const std::vector<std::vector<Cell *>> &cells_grid) {//Allocate a new memory!!!
    this->clear_cells();

    for(std::vector<Cell *> _row : cells_grid){
        std::vector<Cell *> tmp_cell_row;
//        for(Cell * _cell : _row){
//            Cell* tmp_cell = new Cell(*_cell);
//            Logger::Get(LogLevel_TRACE) << "tmp_cell->_row: " << tmp_cell->row() << std::endl;
//            Logger::Get(LogLevel_TRACE) << "_cell->_row: " << _cell->row()  << std::endl;
//
//            tmp_cell_row.push_back(tmp_cell);
//        }
        this->_cells.push_back(tmp_cell_row);
    }

//    this->_cells = cells_grid;

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

Cell *Map::getCell_ptr(int row, int column) {
    return _cells[row][column];
}

Map Map::operator=(const Map& _map) {

//    Logger::Get(LogLevel_TRACE) << "oper =" << std::endl;
    this->set_cells(_map._cells);
    this->_rowNum = _map._rowNum;
    this->_columnNum = _map._columnNum;

    return *this;
}

std::vector<std::vector<Cell *>> Map::get_cell_2D_vector() {
    return this->_cells;
}



