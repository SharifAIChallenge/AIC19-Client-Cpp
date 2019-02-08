#ifndef AIC19_CLIENT_CPP_CELL_H
#define AIC19_CLIENT_CPP_CELL_H



class Cell {
public:
    Cell() = default;
    ~Cell() = default;

    Cell(bool _isNull);

    Cell(const Cell&);
    Cell& operator=(const Cell&);

    Cell(Cell&&);
    Cell& operator=(Cell&&);

//API:
    int getRow() const;
    int getColumn() const;
    bool isWall() const;
    bool isInMyRespawnZone() const;
    bool isInOppRespawnZone() const;
    bool isInObjectiveZone() const;
    bool isInVision() const;

    bool inThisPosition(int row, int column) const;
    bool operator==(const Cell &_cell) const;
    bool operator!=(const Cell &_cell) const;

private:
    bool _isWall;
    bool _isInMyRespawnZone;
    bool _isInOppRespawnZone;
    bool _isInObjectiveZone;
    bool _isInVision;
    int _row;
    int _column;

    friend class InitMessage;
    friend class TurnMessage;

    bool isNull = false;

public:
    static Cell NULL_CELL;
};


#endif //AIC19_CLIENT_CPP_CELL_H
