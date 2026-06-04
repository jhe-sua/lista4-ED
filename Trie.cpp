#include "Trie.hpp"
#include <iostream>

using namespace std;

TrieNode::TrieNode()
{
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        children[i] = nullptr;
    }

    isEndOfTitle = false;
    game = nullptr;
}

Trie::Trie()
    : root(new TrieNode())
{}

Trie::~Trie()
{
    delete root;
}

bool Trie::insert(Game* game)
{
    TrieNode* current = root;
    string key = toSearchKey(game->getTitle());
    int i;

    for (size_t nivel = 0; nivel < key.size(); nivel++)
    {
        i = charToIndex(key[nivel]);
        if (current->children[i] == nullptr)
        {
            current->children[i] = new TrieNode();
        }

        current = current->children[i]; 
    }

    current->game = game;
    current->isEndOfTitle = true;
    return true;
}

bool Trie::contains(string title)
{
    TrieNode* current = root;
    string key = toSearchKey(title);
    int i;

    for (size_t nivel = 0; nivel < key.size(); nivel++)
    {
        i = charToIndex(key[nivel]);
        if (current->children[i] == nullptr) return false;
        current = current->children[i]; 
    }

    return current->isEndOfTitle;
}

TrieNode* Trie::takeNode(string prefix)
{
    TrieNode* current = root;
    string key = toSearchKey(prefix);
    int i;

    for (size_t nivel = 0; nivel < key.size(); nivel++)
    {
        i = charToIndex(key[nivel]);
        if (current->children[i] == nullptr) return nullptr;
        current = current->children[i]; 
    }

    return current;   
}

vector<Game*> Trie::autocomplete(string prefix, int k)
{
    vector<Game*> games;
    if (k <= 0) return games;
    
    TrieNode* current = takeNode(prefix);
    if (current == nullptr) return games;
    
    vector<TrieNode*> fila;

    size_t index = 0;
    int ng = 0;

    fila.push_back(current);
    
    if (current->isEndOfTitle){
        games.push_back(current->game);
        ++ng;
    }

    while (index < fila.size() && ng < k)
    {
        current = fila[index++];

        for (TrieNode* child : current->children)
        {
            if (child != nullptr)
            {   
                fila.push_back(child);

                if (child->isEndOfTitle)
                {
                    games.push_back(child->game);
                    ++ng;

                    if (ng >= k) break;
                }
            }
        }
    }

    sortResults(games);
    return games;
}

int Trie::charToIndex(char c)
{
    if (c >= '0' && c <= '9')
    {
        return c - '0';
    }
    else if (c >= 'A' && c <= 'Z')
    {
        return c - 'A' + 10;
    }
    return -1;
}


string Trie::toUpperCase(string text)
{
    for (char& c : text)
    {
        if (c >= 'a' && c <= 'z')
        {
            c -= 'a' - 'A';
        }
    }

    return text;
}

string Trie::removeSpaces(string text)
{
    for (size_t i = 0; i < text.size();)
    {
        if (text[i] == ' ')
        {
            text.erase(i, 1);
        }
        else
        {
            i++;
        }
    }
    return text;
}

string Trie::toSearchKey(string text)
{
    text = toUpperCase(text);
    text = removeSpaces(text);

    return text;
}

/// @brief determina a antecedencia de um jogo em relação a outro
/// @param g1 game a ser comparado
/// @param g2 game comparador
/// @return @c true se g1 < g2 @c false se g2 < g1
bool Trie::lessGame(Game* g1, Game* g2)
{
    if (g1->getPopularity() != g2->getPopularity())
    {
        return g1->getPopularity() < g2->getPopularity();
    }
    
    return toSearchKey(g1->getTitle()) <= toSearchKey(g2->getTitle());
}

void Trie::merge(vector<Game*>& games, int b, int o, int q)
{   
    int nl = o - b + 1; int nr = q - o;
    Game** left = new Game*[nl]; Game** right = new Game*[nr];

    for (int i = 0; i < nl; i++){
        left[i] = games[i + b];
    }

    for (int i = 0; i < nr; i++){
        right[i] = games[i + o + 1];
    }
    
    int l = 0, r = 0, i = b;
    while (l < nl && r < nr)
    {
        if (lessGame(left[l], right[r]))
        {
            games[i++] = right[r++];
        }
        else
        {
            games[i++] = left[l++];
        } 
    }

    while (l < nl){  // right estourou
        games[i++] = left[l++];
    }

    while (r < nr){ // left estourou
        games[i++] = right[r++];
    }
    
    delete[] left;
    delete[] right;
}

void Trie::mergeSort(vector<Game*>& games, int p, int q)
{   
    int o;
    if (p < q)
    {
        o = (p+q)/2;
        mergeSort(games, p, o);
        mergeSort(games, o+1, q);
        merge(games, p, o, q);
    }
}

void Trie::sortResults(vector<Game*> &games)
{
    int lenght = games.size();
    mergeSort(games, 0, lenght -1);
}