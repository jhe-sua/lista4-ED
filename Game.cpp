#include "Game.hpp"

#include <iostream>

using namespace std;

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