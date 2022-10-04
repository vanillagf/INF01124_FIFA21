#pragma once

#include "../Headers/head.hpp"
#include "../Headers/index.hpp"
#include "../Structures/hashtable.hpp"
#include "../Structures/trie.hpp"
#include "../Structures/timer.hpp"

// Files
#define PLAYERS_CSV "./Data/players.csv"
#define RATING_CSV "./Data/rating.csv"
#define TAGS_CSV "./Data/tags.csv"

using namespace aria::csv;

class Database{
    private:
        HashTable<long, Player, players_total> Players_hashtable;
        HashTable<long, User, users_total> Users_hashtable;
        HashTable<string, Tag, tags_total> Tags_hashtable;
        HashTable<string, Position, positions_total/3> Positions_hashtable;
        Trie Names_Trie;

    public:
        Database();
        ~Database();

        void search_Player(string name);
        void search_User(long id);
        void search_Position(long N, string position);
        void search_Tags(const vector<string> &tags);

    private:
        void read_Players();
        void read_Ratings();
        void read_Tags();
        void setPositions();
};