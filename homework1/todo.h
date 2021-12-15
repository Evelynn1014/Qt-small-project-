#ifndef HOMEWORK1_TODO_H
#define HOMEWORK1_TODO_H
#include <fstream>
#include <iostream>
//20301107 Jiayao Liu 2021.9.11
// Created by Tooooo on 2021/9/17.
//
struct ListNode {
    int num;
    int e;
    ListNode *next;

};


 class todo{
 public:
    ListNode *OneM(int n, int e, ListNode *head2);
// only add
    ListNode *fakeAdd(ListNode *head1, ListNode *head2);
};


#endif //HOMEWORK1_TODO_H

