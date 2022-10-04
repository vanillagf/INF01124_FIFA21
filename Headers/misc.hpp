#pragma once

#include "head.hpp"

namespace misc{
    string strtolower(const string &str);
    bool is_number(string& str);
    vector<string> splitstr(const string &str, char delimiter);
    vector<string> splitN(const string &str, string delimiter);
    vector<string> splitTags(const string& str);
    vector<long> intersection(vector<long>& a, vector<long>& b);
}


