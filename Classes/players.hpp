#pragma once

#include "../Headers/head.hpp"

class Player{
    private:
        long sofifa_id;
        string name;
        vector<string> positions;
        float rating = 0;
        size_t count = 0;

    public:
        Player(long sofifa_id, string name, vector<string> positions){
            this->sofifa_id = sofifa_id;
            this->name = name;
            this->positions = positions;
        }

        long getSofifaID(){
            return sofifa_id;
        }

        string getName(){
            return name;
        }

        size_t getCount(){
            return count;
        }

        vector<string> getPositions(){
            return positions;
        }

        float getRatingAvrg(){
            if(!count)
                return 0;
            else
                return rating/count;
        }

        void addRating(float rating){
            this->rating += rating;
            ++count;
        }

        string postostr(){
            string str = "";
            size_t i;
            for(i = 0; i < positions.size()-1; ++i)
                str += positions[i] + ", ";
            str += positions[i];
            return str;
        }

        void player_Template(){    
            cout << sofifa_id; cout.width(50+(6 - to_string(sofifa_id).length()));
            cout << name; cout.width(23);
            cout << postostr(); cout.width(15);
            cout << getRatingAvrg(); cout.width(15);
            cout << count << endl;
        }
};
