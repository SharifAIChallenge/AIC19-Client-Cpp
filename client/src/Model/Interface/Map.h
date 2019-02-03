#ifndef AIC19_CLIENT_CPP_MAP_H
#define AIC19_CLIENT_CPP_MAP_H


#include <vector>
#include "Cell.h"
#include <Utility/Utility.h>

class Map {
public:
    Map() = default;
    ~Map();
    void delete_Cells();//Calling the destructors of the Cells


    //This constructor initialises the vectors, not the row and column Nums
    Map(const std::vector<std::vector<Cell*>>& cells_grid);

    Map operator=(const Map& _map);

    int& rowNum();
    int rowNum() const;

    int& columnNum();
    int columnNum() const;


    Cell getCell(int row, int column);

    bool isInMap(int row,int column);

    void clear_cells();

    void set_cells(const std::vector<std::vector<Cell*>>& cells_grid);

    std::vector<Cell*> get_cells_list() const;

    std::vector<std::vector<Cell*>> get_cell_2D_vector();

private:

    int _rowNum;
    int _columnNum;

    std::vector<std::vector<Cell *>> _cells;
    std::vector<Cell *> _objectiveZone;
    std::vector<Cell *> _myRespawnZone;
    std::vector<Cell *> _oppRespawnZone;

    Cell* getCell_ptr(int row, int column);
    friend class TurnMessage;

};


#endif //AIC19_CLIENT_CPP_MAP_H
