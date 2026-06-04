#ifndef TRIE
#define TRIE

#include <string>
#include <vector>
#include "Game.hpp"

#define ALPHABET_SIZE 36

class TrieNode
{

public:

    TrieNode* children[ALPHABET_SIZE];
    bool isEndOfTitle;
    Game* game;

    TrieNode();
    ~TrieNode() = default;
};


class Trie
{
    
private:
    
    TrieNode* root;
    
    // Para a busca e a inserção
    int charToIndex(char c);
    std::string toUpperCase(std::string text);
    std::string removeSpaces(std::string text);

    // Para a ordenação
    bool lessGame(Game* g1, Game* g2);
    void merge(vector<Game*>*, int p, int q, int r);
    void mergeSort(vector<Game*>*, int p, int q, int r);

    int charToIndex(char c);
public:

    Trie();
    ~Trie();

    bool insert(Game* game);
    bool contains(std::string title);

    std::vector<Game*> autocomplete(std::string prefix, int k);

    std::string toSearchKey(std::string text);

    void sortResults(std::vector<Game*>& games);

};

#endif // TRIE