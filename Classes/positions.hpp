#pragma once

#include "../Headers/head.hpp"

class Position{
        private:
        string position;
        vector<pair<long, float>> ids;

        public:
        Position(string position){
            this->position = position;
        }

        string getPos(){
            return position;
        }

        vector<pair<long, float>>& getIDs(){
            return ids;
        }

        void insert(long sofifa_id, float rating){
            for(auto& it : ids)
                if(it.first == sofifa_id)
                    return;
            ids.push_back(make_pair(sofifa_id, rating));
        }
};