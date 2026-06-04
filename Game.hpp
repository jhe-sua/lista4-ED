#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>

class Game {
public:
    std::string title;
    std::string description;
    int popularity;

    Game();
    Game(std::string t, std::string d, int p);
    ~Game() = default;

    std::string getTitle();
    std::string getShortDescription();
    int getPopularity();

    // para printar
    std::string getTitle() const;
    std::string getShortDescription() const;
    int getPopularity() const;

    friend std::ostream& operator<<(std::ostream& os, const Game& game);
};

#endif