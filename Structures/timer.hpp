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
            
            if(duration.count() < 1){
                cout.setf(ios::fixed);
                cout << setprecision(0);
                float ms = duration.count() *1000.0f;
                cout << title << " took " << ms << " ms" << endl << endl;
                cout.unsetf(ios_base::showbase);
            }else{
                cout << setprecision(2);
                cout << title << " took " << duration.count() << " seconds" << endl << endl;
            }
            cout << setprecision(ss);
        }      
};
