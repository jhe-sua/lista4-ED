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
            current->children[i] == new TrieNode();
        }

        current = current->children[i]; 
    }

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

vector<Game*> Trie::autocomplete(string prefix, int k)
{

}

int Trie::charToIndex(char c)
{
    if (c >= '48' && c <= '57')
    {
        return c - '0';
    }
    else if (c >= '65' && c <= '90')
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

bool Trie::lessGame(Game* g1, Game* g2)
{
    if (g1->getPopularity() != g2->getPopularity())
    {
        return g1->getPopularity() < g2->getPopularity();
    }
    
    return toSearchKey(g1->getTitle()) < toSearchKey(g2->getTitle());
}

void Trie::sortResults(vector<Game*> &games)
{
    
}