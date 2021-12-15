//20301107 Jiayao Liu 2021.10.5
#include "stackDo.h"

using namespace std;

stackDo::stackDo(){

}
//push operater

int stackDo::pushc(char* a,int top,char elem){
    ++top;
    a[top]=elem;
     printf("push %c\t\n",a[top]);
    return top;
}
//push number

int stackDo::pushd(double* a,int top,double elem){
    ++top;
    a[top]=elem;

    printf("push %lf\t\n",a[top]);
    return top;
}

//push operater
int stackDo::popc(char * a,int top){
    if (top==-1) {
        printf("null");
        return -1;
    }
    printf("pop %c\t\n",a[top]);
    top--;
    return top;
}

//pop number
int stackDo::popd(double * a,int top){
    if (top==-1) {
        printf("null");
        return -1;
    }
    printf("pop %lf\t\n",a[top]);
    top--;
    return top;
}

//string to double(type)
long double stackDo::stringToDouble(string num)
{
    bool minus = false;      //标记是否是负数
    string real = num;       //real表示num的绝对值
    if (num.at(0) == '-')
    {
        minus = true;
        real = num.substr(1, num.size()-1);
    }

    char c;
    int i = 0;
    long double result = 0.0 , dec = 10.0;
    bool isDec = false;       //标记是否有小数
    long long int size = real.size();
    while(i < size)
    {
        c = real.at(i);
        if (c == '.')
        {//包含小数
            isDec = true;
            i++;
            continue;
        }
        if (!isDec)
        {
            result = result*10 + c - '0';
        }
        else
        {//识别小数点之后都进入这个分支
            result = result + (c - '0')/dec;
            dec *= 10;
        }
        i++;
    }

    if (minus == true) {
        result = -result;
    }

    return result;
}

//calculate log
double stackDo::logab(double a,double b)
{
return log(b)/log(a);
}
