#pragma once

#include "../Headers/head.hpp"

class User{
    private:
        long user_id;
        vector<pair<long, float>> ratings;
    public:
        User(long user_id, vector<pair<long, float>> &&ratings){
            this->user_id = user_id;
            this->ratings = move(ratings);
        }
        User(long user_id){
            this->user_id = user_id;
        }

        long getUserID(){
            return user_id;
        }

        vector<pair<long, float>> getRatings(){
            return ratings;
        }

        template<typename... Args>
        void emplace_back(Args&&... args){
            ratings.emplace_back(forward<Args>(args)...);
        }

        void user_Template(Player& p, float& r){
            cout << p.getSofifaID(); cout.width(50+(6 - to_string(p.getSofifaID()).length()));
            cout << p.getName(); cout.width(23);
            cout << p.getRatingAvrg(); cout.width(15);
            cout << p.getCount(); cout.width(16);
            cout << r << endl;
        }
};