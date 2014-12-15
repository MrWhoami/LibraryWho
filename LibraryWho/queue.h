//
//  queue.h
//  Queue
//
//  Created by Whoami on 14/11/9.
//  Copyright (c) 2014年 Whoami.
//

#ifndef Queue_queue_h
#define Queue_queue_h
#include <stdio.h>

template<class T>
class QueueNode {
public:
    T data;
    QueueNode<T> *next;
    QueueNode(){
        next = NULL;
    }
    QueueNode(T x){
        data = x;
        next = NULL;
    }
};

template<class T>
class Queue{
    QueueNode<T> *front;
    QueueNode<T> *rear;
public:
    Queue(){                    //Create/Delete a new Queue.
        front = NULL;
        rear = NULL;
    }
    ~Queue(){
        T tmp;
        while (front != NULL) {
            deQueue(tmp);
        }
    }
    bool enQueue(const T x);    //Input a data.
    bool deQueue(T &x);         //Output a data.
    T deQueue();
    bool getFront(T &x);        //Get the data of the front.
    T getFront();
    bool isEmpty();             //Judge whether it is empty/full or not.
    bool isFull();
    int getSize();              //Get the size of the Queue.
    void makeEmpty();           //Make the queue empty.
};

template <class T>
bool Queue<T>::enQueue(const T x){
    QueueNode<T> *p = new QueueNode<T>(x);
    if (rear == NULL) {
        front = p;
        rear = p;
    } else {
        rear->next = p;
        rear = p;
    }
    return true;
}

template <class T>
bool Queue<T>::deQueue(T &x){
    if(front == NULL) {
        return false;
    } else {
        x = front->data;
        if (front->next == NULL) {
            delete front;
            front = NULL;
            rear = NULL;
        } else {
            QueueNode<T> *tmp = front;
            front = front->next;
            delete tmp;
        }
        return true;
    }
}

template <class T>
T Queue<T>::deQueue(){
    if(front == NULL) {
        return 0;
    } else {
        T x;
        x = front->data;
        if (front->next == NULL) {
            delete front;
            front = NULL;
            rear = NULL;
        } else {
            QueueNode<T> *tmp = front;
            front = front->next;
            delete tmp;
        }
        return x;
    }
}

template <class T>
T Queue<T>::getFront(){
    return front->data;
}

template <class T>
bool Queue<T>::getFront(T &x){
    x = front->data;
    return 1;
}

template <class T>
bool Queue<T>::isEmpty(){
    if (front == NULL) {
        return true;
    } else {
        return false;
    }
}

template <class T>
bool Queue<T>::isFull(){
    return false;
}

template <class T>
int Queue<T>::getSize(){
    int size = 0;
    QueueNode<T> *tmp = front;
    while (tmp != NULL) {
        tmp = tmp->next;
        size++;
    }
    return size;
}

template <class T>
void Queue<T>::makeEmpty(){
    T tmp;
    while (front != NULL) {
        deQueue(tmp);
    }
    front = NULL;
    rear = NULL;
}
#endif
