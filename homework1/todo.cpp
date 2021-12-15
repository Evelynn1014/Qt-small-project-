//20301107 Jiayao Liu 2021.9.11
// Created by Tooooo on 2021/9/17.
//

#include "todo.h"
#include <cstdlib>

using namespace std;
//主要操作在这里被封装


// multiply is many add
ListNode *todo::fakeAdd(ListNode *head1, ListNode *head2) {
    ListNode *temp1, *temp2;
    ListNode *head3, *end3 = (ListNode *) malloc(sizeof(ListNode));
    temp1 = head1->next;
    temp2 = head2->next;
    head3 = end3;
    while (!(nullptr == temp1 || nullptr == temp2)) {
        ListNode *pw = (ListNode *) malloc(sizeof(ListNode));
        int l1, l2;
        l1 = temp1->e;
        l2 = temp2->e;
        if (l1 == l2) {
            pw->e = l1;
            pw->num = temp2->num + temp1->num;
            end3->next = pw;
            end3 = pw;
            temp1 = temp1->next;
            temp2 = temp2->next;

        } else if (l1 > l2) {
            pw->e = l1;
            pw->num = temp1->num;
            end3->next = pw;
            end3 = pw;
            temp1 = temp1->next;
        } else if (l1 < l2) {
            pw->e = l2;
            pw->num = temp2->num;
            end3->next = pw;
            end3 = pw;
            temp2 = temp2->next;
        }
    }

    if (nullptr == temp1) {
        end3->next = temp2;
    }

    if (nullptr == temp2) {
        end3->next = temp1;
    }

    return head3;

}

ListNode *todo::OneM(int n, int e, ListNode *head2) {
    ListNode *temp;
    temp = head2->next;
    ListNode *head, *end = (ListNode *) malloc(sizeof(ListNode));
    head = end;
    while (nullptr != temp) {
        ListNode *instant = (ListNode *) malloc(sizeof(ListNode));
        instant->num = temp->num * n;
        instant->e = temp->e + e;
        end->next = instant;
        end = end->next;

        temp = temp->next;
    }
    end->next = nullptr;
    return head;
}
