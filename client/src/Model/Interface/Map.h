#ifndef AIC18_CLIENT_CPP_MAP_H
#define AIC18_CLIENT_CPP_MAP_H


#include <vector>
#include "Cell.h"

class Map {
public:
    Map() = delete;//TODO we have to write something with inputs
    ~Map();

    void set_rowNum(int _rowNum);
    int get_rowNum() const;
    int& rowNum();
    int rowNum() const;

    void set_columnNum(int _columnNum);
    int get_columnNum() const;
    int& columnNum();
    int columnNum() const;

    Cell getCell(int row, int column);

    bool isInMap(int row,int column);

private:

    int _rowNum;
    int _columnNum;

    std::vector<std::vector<Cell *>> _cells;
    std::vector<Cell *> _objectiveZone;
    std::vector<Cell *> _myRespawnZone;
    std::vector<Cell *> _oppRespawnZone;

};


#endif //AIC18_CLIENT_CPP_MAP_H
