#ifndef AIC19_CLIENT_CPP_MAP_H
#define AIC19_CLIENT_CPP_MAP_H


#include <vector>
#include "Cell.h"
#include <Utility/Utility.h>

class Map {
public:
    Map() = default;
    ~Map();

    Map(const Map& _map);
    Map operator=(const Map& _map);

    //This constructor initialises the vectors, not the row and column Nums
    Map(const std::vector<std::vector<Cell*>>& cells_grid);

//API:
    std::vector<std::vector<Cell*>>& getCells();
    Cell& getCell(int row, int column);
    bool isInMap(int row,int column);
    int getRowNum() const;
    int getColumnNum() const;
    std::vector<Cell*>& getMyRespawnZone();
    std::vector<Cell*>& getOppRespawnZone();
    std::vector<Cell*>& getObjectiveZone();

    std::vector<Cell*> _get_cells_list() const;
    void _set_cells(const std::vector<std::vector<Cell *>> &cells_grid);
    void _clear_cells();
    Cell* getCell_ptr(int row, int column);



private:

    int _rowNum;
    int _columnNum;

    std::vector<std::vector<Cell *>> _cells;
    std::vector<Cell *> _objectiveZone;
    std::vector<Cell *> _myRespawnZone;
    std::vector<Cell *> _oppRespawnZone;

    friend class TurnMessage;
    friend class InitMessage;

};


#endif //AIC19_CLIENT_CPP_MAP_H
