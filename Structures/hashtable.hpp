#pragma once

#include "../Headers/head.hpp"
#include "../Headers/index.hpp"
#include "sort.hpp"

template<typename T, typename C, size_t N>
class HashTable{
    public:
       using HashNode = pair<T, C>;
       using HashArray = vector<HashNode>;

    private:
        size_t size = 0;
        size_t M = 0;
        unique_ptr<HashArray[]> Nodes;

    public:
        // Constructor
        HashTable(){
            M = N;
            Nodes = unique_ptr<HashArray[]>(new HashArray[M]);
        }
        // Destructor
        ~HashTable(){}

        // Get functions
        size_t getSize(){
            return size;
        }
        size_t getMaxsize(){
            return M;
        }

        // Hash Functions
         
        // Hash for sofifa_id
        size_t hash(long key) const{
            return (key * prime) % M;
        }
        // Hash for Names
        size_t hash(string key) const{
            size_t h = 0;
            for(size_t i = 0; i < key.length(); ++i)
                if(key[i] != ' ')
                    h = (prime*h+key[i]) % M ;
            return h;
        }
        // Hash insert()
        typename HashArray::iterator insert(const HashNode &node){
            size_t idx = hash(node.first);
            Nodes[idx].push_back(node);
            ++size;
            return Nodes[idx].end()-1;
        }
        // Hash emplace()
        template<typename... Args>
        typename HashArray::iterator emplace(T key, Args&&... args){
            size_t idx = hash(key);
            Nodes[idx].emplace_back(key, forward<Args>(args)...);
            ++size;
            return Nodes[idx].end()-1;
        }
        // Hash find() 
        pair<typename HashArray::iterator, bool> find(T key){
            size_t idx = hash(key);
            for(auto it = Nodes[idx].begin(); it != Nodes[idx].end(); ++it)
                if(it->first == key)
                    return {it, true};
            return {end(), false};
        }
        // Hash end()
        typename HashArray::iterator end(){
            return Nodes[M-1].end();
        }

        void sortPos(){
            for(size_t i = 0; i < M; ++i){
                for(auto j = Nodes[i].begin(); j != Nodes[i].end(); ++j){
                    sort::sort(j->second.getIDs(), 0, j->second.getIDs().size()-1);
                }
            }
        }
};