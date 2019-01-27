//
// Created by dot_blue on 1/23/19.
//

#ifndef AIC18_CLIENT_CPP_CELL_H
#define AIC18_CLIENT_CPP_CELL_H


class Cell {
public:
    Cell() = default;
    ~Cell() = default;

    Cell(const Cell&) = default;
    Cell& operator=(const Cell&) = default;

    Cell(Cell&&) = default;
    Cell& operator=(Cell&&) = default;

//    Cell& operator==(const Cell);

    void set_Wall(bool _isWall);
    bool is_Wall() const;
    bool& isWall();
    bool isWall() const;

    void set_InMyRespawnZone(bool _isInMyRespawnZone);
    bool is_InMyRespawnZone() const;
    bool& isInMyRespawnZone();
    bool isInMyRespawnZone() const;

    void set_InOppRespawnZone(bool _isInOppRespawnZone);
    bool is_InOppRespawnZone() const;
    bool& isInOppRespawnZone();
    bool isInOppRespawnZone() const;

    void set_InObjectiveZone(bool _isInObjectiveZone);
    bool is_InObjectiveZone() const;
    bool& isInObjectiveZone();
    bool isInObjectiveZone() const;

    void set_InVision(bool _isInVision);
    bool is_InVision() const;
    bool& isInVision();
    bool isInvision() const;

    void set_row(int _row);
    int get_row() const;
    int& row();
    int row() const;

    void set_column(int _column);
    int get_column() const;
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
public:
    static Cell NULL_CELL;
};


#endif //AIC18_CLIENT_CPP_CELL_H
