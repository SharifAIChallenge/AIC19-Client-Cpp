//
// Created by dot_blue on 1/23/19.
//

#include "Cell.h"
//---------------wall------------------
bool Cell::is_Wall() const {
    return _isWall;
}

void Cell::set_Wall(bool _isWall) {
    Cell::_isWall = _isWall;
}

bool &Cell::isWall() {
    return _isWall;
}

bool Cell::isWall() const {
    return _isWall;
}

//----------InMyRespawnZone------------
bool Cell::is_InMyRespawnZone() const {
    return _isInMyRespawnZone;
}

void Cell::set_InMyRespawnZone(bool _isInMyRespawnZone) {
    Cell::_isInMyRespawnZone = _isInMyRespawnZone;
}

bool &Cell::isInMyRespawnZone() {
    return _isInMyRespawnZone;
}

bool Cell::isInMyRespawnZone() const {
    return _isInMyRespawnZone;
}

//----------InOppRespawnZone-----------
bool Cell::is_InOppRespawnZone() const {
    return _isInOppRespawnZone;
}

void Cell::set_InOppRespawnZone(bool _isInOppRespawnZone) {
    Cell::_isInOppRespawnZone = _isInOppRespawnZone;
}

bool &Cell::isInOppRespawnZone() {
    return _isInOppRespawnZone;
}

bool Cell::isInOppRespawnZone() const {
    return _isInOppRespawnZone;
}

//-----------InObjectiveZone-----------
bool Cell::is_InObjectiveZone() const {
    return _isInObjectiveZone;
}

void Cell::set_InObjectiveZone(bool _isInObjectiveZone) {
    Cell::_isInObjectiveZone = _isInObjectiveZone;
}

bool &Cell::isInObjectiveZone() {
    return _isInObjectiveZone;
}

bool Cell::isInObjectiveZone() const {
    return _isInObjectiveZone;
}

//--------------InVision---------------
bool Cell::is_InVision() const {
    return _isInVision;
}

void Cell::set_InVision(bool _isInVision) {
    Cell::_isInVision = _isInVision;
}

bool &Cell::isInVision() {
    return _isInVision;
}

bool Cell::isInvision() const {
    return _isInVision;
}
//---------------row-------------------
int Cell::get_row() const {
    return _row;
}

void Cell::set_row(int _row) {
    Cell::_row = _row;
}

int &Cell::row() {
    return _row;
}

int Cell::row() const {
    return _row;
}
//--------------column-----------------
int Cell::get_column() const {
    return _column;
}

void Cell::set_column(int _column) {
    Cell::_column = _column;
}

int &Cell::column() {
    return _column;
}

int Cell::column() const {
    return _column;
}
