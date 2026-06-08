#include "Game.hpp"

#include <iostream>

using namespace std;

Game::Game()
    : title{""}, description{""}, popularity{0}
{}

Game::Game(string t, string d, int p)
    : title{t}, description{d}, popularity{p}
{}

string Game::getTitle()
{
    return title;
}

string Game::getShortDescription()
{
    return description;
}

int Game::getPopularity()
{
    return popularity;
}

string Game::getTitle() const
{
    return title;
}

string Game::getShortDescription() const
{
    return description;
}

int Game::getPopularity() const
{
    return popularity;
}

ostream& operator<<(ostream& os, const Game& game)
{
    os << "[" << game.getTitle();
    os << " | " << game.getShortDescription();
    os << " | " << game.getPopularity() << "]";

    return os;
}