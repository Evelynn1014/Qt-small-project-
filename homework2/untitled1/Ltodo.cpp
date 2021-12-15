// 刘佳垚 20301107 2021.9.16
#include"Ltodo.h"
Ltodo ::Ltodo(){
}
//构建链表的函数
ListNode* Ltodo :: build(ListNode* end, int num){

    for(int i = 1; i <= num; i++){
        ListNode *temp = new ListNode();
        temp->num = i;
        end->next = temp;
        end = end->next;
    }
    return end;
}
//删除链表
ListNode* Ltodo ::delNode(ListNode *p){
   p->next = p->next->next;
   p = p->next;
   return p;

}
//链表的跳跃
ListNode* Ltodo ::jump(ListNode *p, int n){
    for(int i = 1; i < n-1; i++){
        p = p->next;
    }
    return p;
}
