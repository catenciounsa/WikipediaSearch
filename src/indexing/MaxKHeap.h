#ifndef MAXKHEAP_H
#define MAXKHEAP_H

#include <iostream>
#include <vector>

#define MKHSIZE 10

class MaxKHeap  {
protected:
    int size;
    int data[MKHSIZE+1][2];
public:
    MaxKHeap() {
        size = 0;
    }
    std::vector<int> getKeys() {
        std::vector<int> vec;    
        for(int i=0; i<size; i++) vec.push_back(data[i][0]);
        return vec;
    }
    std::vector<int> getVals() {
        std::vector<int> vec;
        for(int i=0; i<size; i++) vec.push_back(data[i][0]);
        return vec;
    }

    virtual void insert(int key, int val) = 0;
};

class FixedMKH : public MaxKHeap {
public:
    void insert(int key, int val) {
        if( size < MKHSIZE ){
            data[size][0]= key;
            data[size++][1]= val;
        }
    }
    void print() {
        for(int i=0; i<size; i++) {
                std::cout << "Fileid:" << data[i][0] << "=>" <<  " freq:" << data[i][1] << std::endl;
        }
    }
};


#endif