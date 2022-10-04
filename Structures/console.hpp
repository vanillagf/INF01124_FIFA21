#pragma once

#include "../Headers/head.hpp"
#include "../Structures/database.hpp"

class Console{
    public:
        Console(Database& database);
        ~Console();
        void Run();
        bool Command();
        void Search(string args);
        void Search(string option, vector<string> args);
        void Help();
        void Error(string c, int f);
        void Template(int f);
    private:
        Database& database;
        int width = 41;
};