#ifndef MAXKHEAP_H
#define MAXKHEAP_H

#define MKHSIZE 10

class MaxKHeap  {
protected:
    int size;
    int data[MKHSIZE+1][2];
public:
    MaxKHeap() { size = 0; }
    virtual void insert(int key, int val);
};

class FixedMKH : MaxKHeap {
public:
    void insert(int key, int val) {
        if( size < MKHSIZE ){
            data[size][0]= key;
            data[size++][1]= val;
        }
    }
};


#endif