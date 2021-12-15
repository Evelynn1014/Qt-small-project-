#ifndef MYQUEUE_H
#define MYQUEUE_H
#include "car.h"

class myQueue
{
public:
    myQueue();

    bool isEmpty() const;
    bool isFull()const;

    void enQueue(const car&);
    car deQueue();
    void setQusize(int i );
    void traverse()const;
    int size  = 50;
private:

    car storge[40];
    int first;
    int last;
};

#endif // MYQUEUE_H
