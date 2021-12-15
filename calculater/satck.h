#ifndef SATCK_H
#define SATCK_H

#include <iostream>
using namespace std ;
//封装
//类
class stack {

public:
    //所封装的函数声明
    stack();
    int push(char* a,int top,char elem);
    int pop(char * a,int top);

};



#endif // SATCK_H
