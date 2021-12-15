#include <iostream>
#include "myQueue.h"
using namespace std;


myQueue::myQueue()
{
    first = last = -1;
}

void myQueue::setQusize(int i ){
    size = i;
}
bool myQueue::isEmpty()const
{
    //如果为空，first必然为-1,因为在deQueue()出栈函数中已经处理
    return first == -1;
}


bool myQueue::isFull()const
{
    //两种情况，第一种是正常的满，第二种是存在出队时的满
    return first == 0 && last == size - 1 || last == first - 1;
}



void myQueue::enQueue(const car& elem)
{
    if (!isFull())
    {
        //last为-1或指向最后一个元素的位置时
        if (last == -1 || last == size - 1)
        {
            storge[0] = elem;
            last = 0;
            //若队列为空，还需将first赋为0
            if (first == -1)
            {
                first = 0;
            }
        }
        else
        {
            storge[++last] = elem;
        }
    }
    else
    {
        cout << "Queue full." << endl;
        exit(1);
    }
}

//template<typename T, int size>
car myQueue::deQueue()
{
    if (isEmpty())
    {
        cout << "Queue empty." << endl;
        exit(1);
    }
    car temp;
    temp = storge[first];
    //队列中只有一个元素时
    if (first == last)
    {
        //这样，判断是否为空时只需判定first是否为-1
        first = last = -1;
    }
    else if (first == size - 1)
    {
        //回到第一个元素位置
        first = 0;
    }
    else
    {
        ++first;
    }
    return temp;
}

