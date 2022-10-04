#include "database.hpp"

Database::Database(){
    system("cls");
    Timer timer("Database Initialization");
    read_Players();
    read_Ratings();
    read_Tags();
    setPositions();
}

Database::~Database(){}

void Database::read_Players(){
    ifstream players(PLAYERS_CSV);
    CsvParser parser(players);

    for(auto it = ++parser.begin(); it != parser.end(); ++it){
        auto& row = (*it);
        long sofifa_id = stol(row[0], nullptr);
        auto& name = row[1];
        vector<string> positions = misc::splitstr(row[2], ',');
        Players_hashtable.emplace(sofifa_id, Player{sofifa_id, name, positions});
        this->Names_Trie.insert(misc::strtolower(name), sofifa_id);
    }
    players.close();
}

void Database::read_Ratings(){
    ifstream ratings(RATING_CSV);
    CsvParser parser(ratings);

    for(auto it = ++parser.begin(); it != parser.end(); ++it){
        auto& row = (*it);
        long user_id = stol(row[0], nullptr);
        long sofifa_id = stol(row[1], nullptr);
        float rating = stof(row[2], nullptr);
    
        auto [player_it, player_found] = Players_hashtable.find(sofifa_id);
        auto [user_it, user_found] = Users_hashtable.find(user_id);

        if(player_found)
            player_it->second.addRating(rating);
        if(!user_found)
            user_it = Users_hashtable.emplace(user_id, user_id);
        
        user_it->second.emplace_back(sofifa_id, rating);
    }
    ratings.close();
}

void Database::read_Tags(){
    ifstream tags(TAGS_CSV);
    CsvParser parser(tags);

    for(auto it = ++parser.begin(); it != parser.end(); ++it){
        auto& row = (*it);
        long sofifa_id = stol(row[1], nullptr);
        auto &tag = row[2];
        
        auto [tag_it, tag_found] = Tags_hashtable.find(tag);

        if(!tag_found)
            tag_it = Tags_hashtable.emplace(tag, tag);
        tag_it->second.insert(sofifa_id);
    }
    tags.close();
}

void Database::setPositions(){
    ifstream players(PLAYERS_CSV);
    CsvParser parser(players);

    for(auto it = ++parser.begin(); it != parser.end(); ++it){
        auto& row = (*it);
        long sofifa_id = stol(row[0], nullptr);

        auto [player_it, player_found] = Players_hashtable.find(sofifa_id);

        if(!player_found)
            throw;

        auto count = player_it->second.getCount();

        // Mudar para 1000 quando for rating.csv e para 5(?) quando for minirating.csv
        if(count < 1000)
            continue;

        float rating = player_it->second.getRatingAvrg();
        auto positions = player_it->second.getPositions();

        for(auto &&pos : positions){
            auto[position_it, position_found] = Positions_hashtable.find(pos);
            if(!position_found)
                position_it = Positions_hashtable.emplace(pos, pos);
            position_it->second.insert(sofifa_id, rating);
        }
    }
    Positions_hashtable.sortPos();
    players.close();
}

void Database::search_Player(string name){
    auto ids = this->Names_Trie.search(misc::strtolower(name));
    for(auto&& sofifa_id : ids){
        auto [player_it, player_found] = Players_hashtable.find(sofifa_id);
        
        if(!player_found)
            throw;
        player_it->second.player_Template();
    }
}

void Database::search_User(long user_id){
    auto [user_it, user_found] = Users_hashtable.find(user_id);

    if(!user_found){
        cout << "User not found" << endl;
        return;
    }

    auto ratings = user_it->second.getRatings();
    sort::sort(ratings, 0, ratings.size()-1);

    int it = 1;
    for(auto& rating : ratings){
        if(it > 20)
            break;

        auto [player_it, player_found] = Players_hashtable.find(rating.first);
        
        if(!player_found)
            throw;

        user_it->second.user_Template(player_it->second, rating.second);   
        ++it;
    }
}

void Database::search_Position(long N, string position){
    auto [position_it, position_found] = Positions_hashtable.find(position);

    if(!position_found){
        cout << "Position '" << position << "' not found." << endl;
        return;
    }

    auto& sofifa_ids = position_it->second.getIDs();
    sort::sort(sofifa_ids, 0, sofifa_ids.size()-1);

    int i = 1;
    for(auto it = sofifa_ids.begin(); it != sofifa_ids.end(); ++it){
        if(i > N)
            break;

        auto [player_it, player_found] = Players_hashtable.find(it->first);

        if(!player_found)
            throw;

        player_it->second.player_Template();
        ++i;
    } 
}

void Database::search_Tags(const vector<string> &tags){
    vector<long> result;
    bool first = true;

    for(auto&& tag : tags){
        auto [tag_it, tag_found] = Tags_hashtable.find(tag);

        if(!tag_found){
            cout << "Tag '" << tag << "' not found." << endl;
            return;
        }

        auto sofifa_ids = tag_it->second.getIDS();
        
        std::sort(sofifa_ids.begin(), sofifa_ids.end());

        if(first){
            result = sofifa_ids;
            first = false;
            continue;
        }

        vector<long> temp = misc::intersection(result, sofifa_ids);
        
        if(temp.size() == 0){
            cout << "No matches found." << endl;
            return;
        }
        result = temp;
    }

    for(auto&& id : result){
        auto [player_it, player_found] = Players_hashtable.find(id);

        if(!player_found)
            throw;

        player_it->second.player_Template();
    }
}