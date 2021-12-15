//20301107 Jiayao Liu 2021.9.11


#include <iostream>
#include <fstream>
#include <cstdlib>
#include "todo.h"
using namespace std;
/*struct ListNode {
    int num;
    int e;
    ListNode *next;

};*/
// add and output
void add(ListNode *head1, ListNode *head2);

void Multiplication(ListNode *head1, ListNode *head2);

//ListNode *OneM(int n, int e, ListNode *head2);
// only add
//ListNode *fakeAdd(ListNode *head1, ListNode *head2);

int main() {
    todo todo;
    int i;
    int l;
    int numRead;
    int eRead;
    ListNode *head1 = (ListNode *) malloc(sizeof(ListNode)), *end1;
    ListNode *head2 = (ListNode *) malloc(sizeof(ListNode)), *end2;
    ifstream in;

    in.open("D:\\homework_cxd\\homework1\\ini.txt", ios::in);
    // two lists
    if (in.is_open()) {
        in >> i;
        end1 = head1;

        for (int q = 0; q < i; q++) {
            ListNode *pr = (ListNode *) malloc(sizeof(ListNode));
            in >> numRead >> eRead;
            pr->num = numRead;
            pr->e = eRead;
            end1->next = pr;
            end1 = pr;
        }
        end1->next = nullptr;

        in >> l;
        end2 = head2;

       for (int q = 0; q < l; q++) {
            ListNode *qr = (ListNode *) malloc(sizeof(ListNode));
            in >> numRead >> eRead;
            qr->num = numRead;
            qr->e = eRead;
            end2->next = qr;
            end2 = qr;
        }
        end2->next = nullptr;

    }
    in.close();
    //add
    add(head1, head2);
    //multiply
    Multiplication(head1, head2);
    return 0;
}


void add(ListNode *head1, ListNode *head2) {
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

    ofstream out;
    //print
    out.open("D:\\homework_cxd\\homework1\\addFinally.txt", ios::out);
    ListNode *temp;
    temp = head3->next;
    int cot = 1;
    while (temp->next != nullptr) {
        temp = temp->next;
        cot++;
    }
    // print number of members
    out << cot;
    while (head3->next != nullptr) {
        head3 = head3->next;
        out << " " << head3->num << " " << head3->e;
    }

    out.close();
}



void Multiplication(ListNode *head1, ListNode *head2) {
    int cot1 = 1;
    int cot2 = 2;
    ListNode *temp1, *temp2;
    ListNode *head3 = (ListNode *) malloc(sizeof(ListNode));

    temp1 = head1;
    temp2 = head2;
    while (temp1->next != nullptr) {
        temp1 = temp1->next;
        cot1++;
    }

    while (temp2->next != nullptr) {
        temp2 = temp2->next;
        cot2++;
    }
    todo todo;
    int n1, e1;
    temp1 = head1->next;
    for (int i = 1; i < cot1; i++) {
        e1 = temp1->e;
        n1 = temp1->num;
        head3 = todo.fakeAdd(head3, todo.OneM(n1, e1, head2));
        temp1 = temp1->next;
    }
    //print
    ofstream out;
    out.open("D:\\homework_cxd\\homework1\\MultiFinally.txt", ios::out);
    ListNode *temp;
    temp = head3->next;
    int cot = 1;
    while (temp->next != nullptr) {
        temp = temp->next;
        cot++;
    }
    // print number of members
    out << cot;
    while (head3->next != nullptr) {
        head3 = head3->next;
        out << " " << head3->num << " " << head3->e;
    }

    out.close();

}