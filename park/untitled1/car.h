#ifndef CAR_H
#define CAR_H
#include <ctime>
#include <iostream>
#include <cstdio>
#include<math.h>
#include <string>
#include <Windows.h>

#include <fstream>
using namespace std ;

class car {
public:
        car();
    int  rnum();
    int cartime;
    clock_t starttime;
    void setStarttime();
    void settime();
    string plate;
    string returnBd();
    int pk;
    void setPk(int pk);
    string  car_plate();
    string msg1();
    string msg2();
    string msg3();
};

#endif // CAR_H
