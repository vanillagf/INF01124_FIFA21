#pragma once

#include "../Headers/head.hpp"

 struct Nodo{
    shared_ptr<Nodo> filho[prime];
    long sofifa_id;
    bool isEOW;

    Nodo();
    ~Nodo();
};

class Trie{      
    private:
        shared_ptr<Nodo> raiz;
        size_t words_total;

        void getIDs(Nodo* raiz, vector<long>& IDs);
        int getIDX(char c);

    public:
        Trie();
        ~Trie();
        void insert(string key, long sofifa_id);
        vector<long> search(string key);
};