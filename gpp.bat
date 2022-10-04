@echo off 
echo: & echo Compiling Program... & echo:
g++ --std=c++17 -o FIFA21 main.cpp Headers\misc.cpp Structures\database.cpp Structures\trie.cpp Structures\console.cpp

