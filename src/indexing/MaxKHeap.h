#ifndef MAXKHEAP_H
#define MAXKHEAP_H

#include <iostream>
#include <vector>

#define MKHSIZE 10
#define INF 1000000000

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
        for(int i=0; i<size; i++) vec.push_back(data[i][1]);
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

class OptimizedMaxKHeap : public MaxKHeap{
private:
    void insertMinHeap(int key, int val) {
        data[ size ][0] = key;
        data[ size++ ][1] = val;
        int parent, pivote=size-1;
        
        if( size == 1) return;
        
        do {
            parent = (pivote-1)>>1;
            if( data[pivote][1] < data[parent][1] ) {
                swap( data[parent][0], data[pivote][0] );
                swap( data[parent][1], data[pivote][1] );
            } else break;
        } while( parent );
    }
    void heapify(int pivote) {
        int left=(pivote<<1)+1;
        int right=left +1;
        int lval, rval;

        while( left != INF ) {
            lval = (left<size) ? data[left][1] : INF;
            rval = (right<size) ? data[right][1] : INF;

            if( lval < rval && lval < data[pivote][1]) {
                swap( data[pivote][0], data[left][0] );
                swap( data[pivote][1], data[left][1] );
                pivote = left;
            }else if( rval <= lval && rval < data[pivote][1]) {
                swap( data[pivote][0], data[right][0] );
                swap( data[pivote][1], data[right][1] );
                pivote = right;
            }
            else break;
            left = (pivote<<1)+1; right = left+1;
        }
    }

public: 
    void insert( int key, int val ) {
        if( size < MKHSIZE ) insertMinHeap( key, val );
        else {
            if( val > data[0][1] ) { //if val < data[0] ignore it
                data[0][0] = key;
                data[0][1] = val;
                heapify(0);
            }
        }
    }
    void print() {
        for (int i = 0; i < size; i++){
            cout << "[" << data[i][0]  << "=>" << data[i][1] << "] ";
        }
        cout<<endl;        
    }
};


#endif