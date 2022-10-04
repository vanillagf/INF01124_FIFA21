#pragma once

#include "../Headers/head.hpp"

class Tag{
    private:
        string tag;
        vector<long> ids;
    public:
        Tag(string tag){
            this->tag = tag;
        }

        string getTag(){
            return tag;
        }

        vector<long> getIDS(){
            return ids;
        }

        void insert(long sofifa_id){
            for(auto& it : ids)
                if(it == sofifa_id)
                    return;
            ids.push_back(sofifa_id);
        }
        
};