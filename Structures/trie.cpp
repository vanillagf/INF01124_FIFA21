#include "trie.hpp"

Nodo::Nodo(){
    for(size_t i = 0; i < alphabet_size; ++i)
        this->filho[i] = shared_ptr<Nodo>();
    this->isEOW = false;
}

Nodo::~Nodo(){}

Trie::Trie(){
    this->raiz = shared_ptr<Nodo>(new Nodo);
    this->words_total = 0;
}

Trie::~Trie(){}

void Trie::getIDs(Nodo* raiz, vector<long>& IDs){
    if(!raiz)
        return;
    for(size_t i = 0; i < alphabet_size; ++i){
        getIDs(raiz->filho[i].get(), IDs);
        if(raiz->filho[i] && raiz->filho[i]->isEOW)
            IDs.push_back(raiz->filho[i]->sofifa_id);
    }
} 

int Trie::getIDX(char c){
    switch(c){
        case '\"':
            return alphabet_size - 5;
        case ' ':
            return alphabet_size - 4;
        case '.':
            return alphabet_size - 3; 
        case '-':
            return alphabet_size - 2; 
        case '\'':
            return alphabet_size - 1;
        default:
            int idx = c - 'a';
        
            if(idx < 0 || idx > 26)
                return -1;
            return idx;
    }
}

void Trie::insert(string key, long sofifa_id){
    shared_ptr<Nodo> temp = this->raiz;
    for(size_t i = 0; i < key.length(); ++i){
        int idx = this->getIDX(key[i]);
        if(idx == -1)
            throw;
        if(!temp->filho[idx])
            temp->filho[idx] = shared_ptr<Nodo>(new Nodo);
        temp = temp->filho[idx];
    }
    this->words_total++;
    temp->isEOW = true;
    temp->sofifa_id = sofifa_id;
    return;
}

vector<long> Trie::search(string key){
    shared_ptr<Nodo> temp = this->raiz;
    vector<long> result;

    for(size_t i = 0; i < key.length(); ++i){
        int idx = this->getIDX(key[i]);
        if(idx == -1 || !temp->filho[idx])
            return {};
        temp = temp->filho[idx];
    } 
    getIDs(temp.get(), result);
    return result;
}
