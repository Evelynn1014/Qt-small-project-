#ifndef STACKDO_H
#define STACKDO_H

#include <iostream>
#include <cstdio>
#include<math.h>
using namespace std ;

class stackDo {
public:
       stackDo();
    int pushc(char* a,int top,char elem);
    int pushd(double* a,int top,double elem);
    int popc(char * a,int top);
    int popd(double * a,int top);
    long double stringToDouble(string num);
    double logab(double a,double b);
};

#endif // STACKDO_H
