#include "GamesDatabase.hpp"
#include <cstdlib>
#include <algorithm>
#include "Trie.hpp"

#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{

    if (argc != 3) {
        cout << "Usage: ./app k prefix" << endl;
        return 1;
    }

    int numMaxSuggestions = atoi(argv[1]);
    string prefix = argv[2];

    numMaxSuggestions = max(numMaxSuggestions, 0);
    numMaxSuggestions = min(numMaxSuggestions, numberOfGames);

    Trie trie = Trie();

    vector<Game*> autocom;
    
    for (int i = 0; i < numberOfGames; i++)
    {
        trie.insert(&games[i]);
    }

    autocom = trie.autocomplete(prefix, numMaxSuggestions);

    if (autocom.size() == 0)
    {
        cout << "No results found" << endl;
        return 0;
    }
    

    for (Game* g : autocom)
    {
        cout << *g << endl;
    }

    return 0;
}