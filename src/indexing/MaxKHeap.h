#ifndef MAXKHEAP_H
#define MAXKHEAP_H

#define MKHSIZE 10

class MaxKHeap  {
protected:
    int size;
    int data[MKHSIZE+1][2];
public:
    virtual void insert(int key, int val) = 0;
};

class FixedMKH : public MaxKHeap {
public:
    FixedMKH() {
        size = 0;
    }
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