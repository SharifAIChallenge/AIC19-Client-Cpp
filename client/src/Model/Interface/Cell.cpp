//
// Created by dot_blue on 1/23/19.
//

#include "Cell.h"


Cell::Cell(bool _isNull): isNull(_isNull) {}
//---------------wall------------------
bool &Cell::isWall() {
    return _isWall;
}

bool Cell::isWall() const {
    return _isWall;
}

//----------InMyRespawnZone------------
bool &Cell::isInMyRespawnZone() {
    return _isInMyRespawnZone;
}

bool Cell::isInMyRespawnZone() const {
    return _isInMyRespawnZone;
}

//----------InOppRespawnZone-----------
bool &Cell::isInOppRespawnZone() {
    return _isInOppRespawnZone;
}

bool Cell::isInOppRespawnZone() const {
    return _isInOppRespawnZone;
}

//-----------InObjectiveZone-----------
bool &Cell::isInObjectiveZone() {
    return _isInObjectiveZone;
}

bool Cell::isInObjectiveZone() const {
    return _isInObjectiveZone;
}

//--------------InVision---------------
bool &Cell::isInVision() {
    return _isInVision;
}

bool Cell::isInvision() const {
    return _isInVision;
}
//---------------row-------------------
int &Cell::row() {
    return _row;
}

int Cell::row() const {
    return _row;
}
//--------------column-----------------
int &Cell::column() {
    return _column;
}

int Cell::column() const {
    return _column;
}

bool Cell::inThisPosition(int row, int column) const{
    return this->_row == row && this->_column == column;
}

bool Cell::operator==(const Cell _cell) const{
    return this->inThisPosition(_cell.row(),_cell.column()) &&
            (this->isNull == _cell.isNull);
}

bool Cell::operator!=(const Cell _cell) const {
    return !(*this == _cell);
}

Cell Cell::NULL_CELL(true);



