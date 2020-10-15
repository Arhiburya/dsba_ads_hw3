#include "pq.h"

#include <iostream>
using namespace std;

class priorityQueue
{
private:
    int front;
    int rear;
    int size;
    int *array;

public:
    priorityQueue();
    ~priorityQueue();
    void insert(int x);
    //remove and return the smallest item currently in the priority queue
    int extractMin();
    bool empty();
};

priorityQueue::priorityQueue()
{
    front = rear = -1;
    size = 10;
    array = new int[size];
}

priorityQueue::~priorityQueue()
{
    delete[] array;
}

void priorityQueue::insert(int x)
{
    //if queue is full
    if ( (rear + 1)% size == front ){
        return;
    }

    //else if queue is empty
    else if ( empty() ){
        rear = front = 0;
    }

    else
    {
        rear = (rear + 1) % size;
    }

    array[rear] = x;
}

//extract and return smallest value in queue
int priorityQueue::extractMin()
{
    int minValue = array[front];

    if ( empty() ){
        return -1;
    }

    else if (front == rear){
        front = rear = -1;
        }

    else
    {
        front = (front + 1) % size;
    }

    int minIndex = front;

    //find smallest value
    for (int i = front; i <= rear; i++){
        if (array[i] < minValue)
        {
            minIndex = i;
            minValue = array[i];
        }
    }

    array[minIndex] = array[front];

    //return smallest value
    return minValue;
}


bool priorityQueue::empty()
{
    if ( (front == -1) && (rear == -1) )
        return true;
    else
        return false;
}
