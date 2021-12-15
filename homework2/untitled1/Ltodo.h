// 刘佳垚 20301107 2021.9.16
#ifndef LTODO_H
#define LTODO_H
#include <iostream>
//声明结构体
struct ListNode{
    int num;
    ListNode *next;
};
//封装
//类
class Ltodo {
public:
    //所封装的函数声明
    Ltodo();
    ListNode* build(ListNode* end, int num);
    ListNode* delNode(ListNode *p);
    ListNode* jump(ListNode *p, int n);

};

#endif // LTODO_H
