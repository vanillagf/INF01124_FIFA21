#pragma once

#include "../Headers/head.hpp"

using namespace chrono;

class Timer{
    private:
        system_clock::time_point start, end;
        duration<double> duration;
        string title;
    public:
        Timer(){
            start = system_clock::now();
        }

        Timer(string title){
            start = system_clock::now();
            this->title = title;
        }

        ~Timer(){
            streamsize ss = cout.precision();
            end = system_clock::now();
            duration = end-start;
            cout << setprecision(2);
            cout << title << " took " << duration.count() << " seconds" << endl << endl;
            cout << setprecision(ss);
        }      
};
