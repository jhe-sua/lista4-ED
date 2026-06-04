#ifndef GAME_HPP
#define GAME_HPP

#include <string>

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
};

#endif