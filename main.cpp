#include "GamesDatabase.hpp"
#include "Trie.hpp"

#include <iostream>

using namespace std;

int main()
{
    Trie autocom = Trie();

    string teste = "EL 1 2 2 pepeee2SA1SD";

    teste = autocom.toSearchKey(teste);
    cout << teste << endl;

    return 0;
}