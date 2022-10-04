#include "misc.hpp"

namespace misc{

    string strtolower(const string &str){
        string aux = str;
        for(auto&& c : aux)
            c = tolower(c);
        return aux;
    }

    bool is_number(string& str){
        for(size_t i = 0; i < str.length(); ++i)
            if(isdigit(str[i]))
                return true;
        return false;
    }

    vector<string> splitstr(const string &str, char delimiter){
        size_t start = 0, end;
        string sub;
        vector<string> result;

        while((end = str.find(delimiter, start)) != string::npos){
            sub = str.substr(start, end-start);
            start = end+1;
            if(str[start] == ' ')
                ++start;
            result.push_back(sub);
        }
        result.push_back(str.substr(start));
        return result;
    }

    vector<string> splitN(const string& str, string delimiter){
        string sub;
        vector<string> result, temp;
        temp = splitstr(str, delimiter[0]);
        for(size_t i = 1; i < delimiter.length(); ++i){
            string sub = "";
            for(auto& i : temp)
                sub.append(i+' ');
            temp = splitstr(sub, delimiter[i]);
        }
        for(auto& i : temp)
            if(i.find_first_not_of(' ') != string::npos)
                result.push_back(i);
        return result;
    }

    vector<string> splitTags(const string& str){
        int ac = 0;
        vector<string> splited = misc::splitstr(str, '\'');
        vector<string> result;
        
        for(auto& i : str)
            if(i == '\'')
                ++ac;

        for(size_t i = 0; i < splited.size(); ++i){
            if(i%2 != 0)
                result.push_back(splited[i]);            
        }

        if(ac%2 != 0)
            result.pop_back();

        for(auto& i : result)
            if(i.find_first_not_of(' ') != string::npos)
                return result;

        return {};
    }

    vector<long> intersection(vector<long>& a, vector<long>& b){
        vector<long> result;
        set_intersection(a.begin(), a.end(), b.begin(), b.end(), 
                        back_inserter(result));
        return result;
    }

}