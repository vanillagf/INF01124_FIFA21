#include "console.hpp"

Console::Console(Database &database) : database(database){
    Console::Run();
}

Console::~Console(){}

void Console::Run(){
    cout << "----------------------------------------------------------------------------------" << endl << endl;
    cout << "FIFA2021 Search Program" << endl << endl;
    Console::Help();
    cout << "----------------------------------------------------------------------------------" << endl << endl;
    while(true){
        cout << "> ";
        string prefix;
        bool flag = true;
        cin >> prefix;
        if(prefix == "$")
            flag = Command();
        else
            Console::Error(prefix, 0);
        
        if(!flag)
            break;
    }
}

bool Console::Command(){
    string command;
    getline(cin, command);
    if(command.length() < 1 || command.find_first_not_of(' ') == string::npos){
        Console::Error("", -1);
        return true;
    }
    
    vector<string> splited = misc::splitN(command, "''.,^` ");
    string option = misc::strtolower(splited[0]); 

    if(option == "?" || option == "h" || option == "help"){
        cout << endl;
        Console::Help();
        return true;
    }
    if(option == "player" || option == "user" || option == "top"){
        Console::Search(option, splited);
        return true;
    }
    if(option == "tags"){
        Console::Search(command);
        return true;
    }
    
    if(option == "x" || option == "exit"){
        return false;
    }

    Console::Error(option, 1);
    return true;
}

void Console::Search(string option, vector<string> args){
    if(option == "player"){
        if(args.size() < 2){
            Console::Error("", 2);
            return;
        }
        Timer timer("Player Search");
        string name = "";
        name += args[1];
        for(size_t i = 2; i < args.size(); ++i){
            name += (" " + args[i]);
        }
        
        if(args.size() > 1 && (name.length() - args[1].length()) > 5)
            name.pop_back();

        Console::Template(1);
        database.search_Player(name);
        cout << endl << endl;

        return;
    }

    if(option == "user"){
        if(args.size() < 2){
            Console::Error("", 2);
            return;
        }
        if(args.size() > 2){
            Console::Error("", 4);
            return;
        }
        if(!misc::is_number(args[1])){
            Console::Error(args[1], 3);
            return;
        }
        Timer timer("User Search");
        long user_id = stol(args[1], nullptr);
        Console::Template(0);
        database.search_User(user_id);
        cout << endl << endl;
        return;
    }

     if(option == "top"){
        if(args.size() < 3){
            Console::Error("", 2);
            return;
        }
        if(!misc::is_number(args[1])){
            Console::Error(args[1], 3);
            return;
        }
        Timer timer("Position Search");
        int N = stoi(args[1], nullptr);
        string position = args[2];
        Console::Template(1);
        if(N <= 0)
            return;
        database.search_Position(N, position);
        cout << endl << endl;
        return;
    }
}

void Console::Search(string args){
    vector<string> result = misc::splitTags(args);
    if(!result.size() || result.empty()){
        if(args.length() > 6)
            Console::Error("", 5);
        else
            Console::Error("", 2);
        return;
    }
    Timer timer("Tags Search");
    Console::Template(1);
    database.search_Tags(result);
    cout << endl << endl;
}

void Console::Help(){
    cout << "usage:" << endl;
    cout << "  $ <options>" << endl << endl;
    cout << "where options are:" << endl;
    cout << "  ?, h, help"; cout.width(width); cout << "display usage information" << endl;
    cout << "  player <name or prefix>"; cout.width(width+9); cout << "displays a list of players the name starts with" << endl;
    cout << "  user <userID>"; cout.width(width+13); cout << "displays a list of players the user rated" << endl;
    cout << "  top <N> '<position>'"; cout.width(width+8); cout << "displays the top N players of that position" << endl;
    cout << "  tags <list of tags>"; cout.width(width+19); cout << "displays the players associated with the list of tags" << endl;
    cout << "  x, exit"; cout.width(width-6); cout << "exit the program" << endl << endl << endl;
}

void Console::Error(string c, int f){
    string buff;
    switch (f){
    case 0: 
        cout << "'" << c << "' is a invalid prefix."; 
        getline(cin, buff);
        break;
    case 1:
        cout << "'" << c << "' is not recongnized as a command."; 
        break;
    case 2:
        cout << "too few arguments in the command call.";
        break;
    case 3:
        cout << c << " isn't a number.";
        break;
    case 4:
        cout << "too much arguments in the command call.";
        break;
    case 5:
        cout << "no valid command was informed.";
        break;
    default:
        cout << "command wasn't informed.";
        break;
    }
    cout << endl << endl;
}

void Console::Template(int f){
    cout << endl;
    cout << "sofifa_id"; cout.width(30); 
    cout << "name"; cout.width(40);
    switch(f){
        case 0:
            cout << "global_positions"; cout.width(15);
            cout << "count"; cout.width(16);
            cout << "rating";
            break;
        default:
            cout << "player_positions"; cout.width(15);
            cout << "rating"; cout.width(15);
            cout << "count"; 
            break;
    }
    cout << endl << endl;
}
