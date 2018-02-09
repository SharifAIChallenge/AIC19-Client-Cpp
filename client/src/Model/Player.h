#ifndef AIC18_CLIENT_CPP_PLAYER_H
#define AIC18_CLIENT_CPP_PLAYER_H

#include <iostream>

/**
 * Identifier for the two players
 */
enum Owner {
    ME = 0,
    ENEMY = 1
};

/**
 * Information about a player in game
 */
class Player {
public:

    Player() = default;
    ~Player() = default;

    Player(const Player&) = default;
    Player& operator=(const Player&) = default;

    Player(Player&&) = default;
    Player& operator=(Player&&) = default;

    /**
     * Construct a player from its initial parameters
     */
    Player(int strength, int money, int income, int beans_left, int storms_left);

    void set_strength(int strength);
    int get_strength() const;

    void set_money(int money);
    int get_money() const;

    void set_income(int income);
    int get_income() const;

    void set_beans_left(int beans_left);
    int get_beans_left() const;

    void set_storms_left(int storms_left);
    int get_storms_left() const;

    friend std::ostream& operator<< (std::ostream& output, const Player& player);

private:

    /// The amount of strength this player has
    int m_strength;

    /// The amount of money this player has (set to zero for enemy)
    int m_money;

    /// The current income for this player (set to zero for enemy)
    int m_income;

    /// Number of remaining unused beans
    int m_beans_left;

    /// Number of remaining unused storms
    int m_storms_left;

};

#endif // AIC18_CLIENT_CPP_PLAYER_H
