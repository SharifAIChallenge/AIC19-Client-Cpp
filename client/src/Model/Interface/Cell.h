#ifndef AIC19_CLIENT_CPP_CELL_H
#define AIC19_CLIENT_CPP_CELL_H


class Cell {
public:
    Cell() = default;
    ~Cell() = default;

    Cell(bool _isNull);

    Cell(const Cell&) = default;
    Cell& operator=(const Cell&) = default;

    Cell(Cell&&) = default;
    Cell& operator=(Cell&&) = default;

//    Cell& operator==(const Cell);

    bool& isWall();
    bool isWall() const;

    bool& isInMyRespawnZone();
    bool isInMyRespawnZone() const;

    bool& isInOppRespawnZone();
    bool isInOppRespawnZone() const;

    bool& isInObjectiveZone();
    bool isInObjectiveZone() const;

    bool& isInVision();
    bool isInvision() const;

    int& row();
    int row() const;

    int& column();
    int column() const;

    bool inThisPosition(int row, int column) const;
    bool operator==(const Cell _cell) const;
    bool operator!=(const Cell _cell) const;

private:
    bool _isWall;
    bool _isInMyRespawnZone;
    bool _isInOppRespawnZone;
    bool _isInObjectiveZone;
    bool _isInVision;

    int _row;
    int _column;

    bool isNull = false;

public:
    static Cell NULL_CELL;
};


#endif //AIC19_CLIENT_CPP_CELL_H
