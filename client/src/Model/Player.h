#ifndef AIC18_CLIENT_CPP_PLAYER_H
#define AIC18_CLIENT_CPP_PLAYER_H

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

    Player(int health, int money, int income, int beans_left, int storms_left);

    void set_health(int health);
    void set_money(int money);
    void set_income(int income);
    void set_beans_left(int beans_left);
    void set_storms_left(int storms_left);

    int get_health() const;
    int get_money() const;
    int get_income() const;
    int get_beans_left() const;
    int get_storms_left() const;

private:

    /// The amount of health this player has
    int m_health;

    /// The amount of money this player has
    int m_money;

    /// The current income for this player
    int m_income;

    /// Number of remaining unused beans
    int m_beans_left;

    /// Number of remaining unused storms
    int m_storms_left;

};

#endif // AIC18_CLIENT_CPP_PLAYER_H
