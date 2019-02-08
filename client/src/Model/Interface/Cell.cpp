#include "Cell.h"


Cell::Cell(bool _isNull): isNull(_isNull) {
    if(_isNull){
        this->_column = -1;
        this->_row = -1;
    }
}


Cell::Cell(const Cell & _cell) {
    this->_column = _cell._column;
    this->_row = _cell._row;

    this->_isInVision = _cell._isInVision;
    this->_isWall = _cell._isWall;
    this->_isInMyRespawnZone = _cell._isInMyRespawnZone;
    this->_isInOppRespawnZone = _cell._isInOppRespawnZone;
    this->_isInObjectiveZone = _cell._isInObjectiveZone;

    this->isNull = _cell.isNull;
}

Cell &Cell::operator=(const Cell & _cell) {
    this->_column = _cell._column;
    this->_row = _cell._row;

    this->_isInVision = _cell._isInVision;
    this->_isWall = _cell._isWall;
    this->_isInMyRespawnZone = _cell._isInMyRespawnZone;
    this->_isInOppRespawnZone = _cell._isInOppRespawnZone;
    this->_isInObjectiveZone = _cell._isInObjectiveZone;

    this->isNull = _cell.isNull;

    return *this;
}

Cell::Cell(Cell && _cell) {
    this->_column = _cell._column;
    this->_row = _cell._row;

    this->_isInVision = _cell._isInVision;
    this->_isWall = _cell._isWall;
    this->_isInMyRespawnZone = _cell._isInMyRespawnZone;
    this->_isInOppRespawnZone = _cell._isInOppRespawnZone;
    this->_isInObjectiveZone = _cell._isInObjectiveZone;

    this->isNull = _cell.isNull;
}

Cell &Cell::operator=(Cell && _cell) {
    this->_column = _cell._column;
    this->_row = _cell._row;

    this->_isInVision = _cell._isInVision;
    this->_isWall = _cell._isWall;
    this->_isInMyRespawnZone = _cell._isInMyRespawnZone;
    this->_isInOppRespawnZone = _cell._isInOppRespawnZone;
    this->_isInObjectiveZone = _cell._isInObjectiveZone;

    this->isNull = _cell.isNull;

    return *this;
}


//---------------wall------------------
bool Cell::isWall() const {
    return _isWall;
}

//----------InMyRespawnZone------------
bool Cell::isInMyRespawnZone() const {
    return _isInMyRespawnZone;
}

//----------InOppRespawnZone-----------
bool Cell::isInOppRespawnZone() const {
    return _isInOppRespawnZone;
}

//-----------InObjectiveZone-----------
bool Cell::isInObjectiveZone() const {
    return _isInObjectiveZone;
}

//--------------InVision---------------
bool Cell::isInVision() const {
    return _isInVision;
}
//---------------row-------------------
int Cell::getRow() const {
    return _row;
}
//--------------column-----------------
int Cell::getColumn() const {
    return _column;
}

bool Cell::inThisPosition(int row, int column) const{
    return this->_row == row && this->_column == column;
}

bool Cell::operator==(const Cell &_cell) const{
    return this->inThisPosition(_cell.getRow(), _cell.getColumn()) &&
            (this->isNull == _cell.isNull);
}

bool Cell::operator!=(const Cell &_cell) const {
    return !(*this == _cell);
}

Cell Cell::NULL_CELL(true);



