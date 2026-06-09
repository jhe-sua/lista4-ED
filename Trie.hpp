#ifndef TRIE_HPP
#define TRIE_HPP

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
    ~TrieNode();

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
    void merge(std::vector<Game*>& games, int p, int q, int r);
    void mergeSort(std::vector<Game*>& games, int p, int r);
    
    // Para recuperação
    TrieNode* takeNode(std::string prefix);
    public:

    Trie();
    ~Trie();

    bool insert(Game* game);
    bool contains(std::string title);

    void recursiveDFS(std::vector<Game*>& games, TrieNode* node);
    std::vector<Game*> autocomplete(std::string prefix, int k);

    std::string toSearchKey(std::string text);

    void sortResults(std::vector<Game*>& games);

};

#endif // TRIE