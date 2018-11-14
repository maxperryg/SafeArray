//
//  SafeMatrix.cpp
//  safeArray
//
//  Created by Maxwell Perry Grossman on 11/14/18.
//  Copyright © 2018 Maxwell Perry Grossman. All rights reserved.
//

#include <iostream>
using namespace std;

template <class T>
class SafeMatrix{
private:
    int verticalLow, verticalHigh, horizontalLow, horizontalHigh, row, height, width;
    T** p;
public:
    
    // default constructor
    // allows for writing things like SA a;
    SafeMatrix(){
        verticalLow=0;
        verticalHigh=-1;
        horizontalLow=0;
        horizontalHigh=-1;
        height = 0;
        width = 0;
        p=NULL;
    }
    
    //One parameter constructor to create a square matrix
    SafeMatrix(int size){
        verticalLow=0;
        verticalHigh=size-1;
        horizontalLow=0;
        horizontalHigh=size-1;
        height = size;
        width = size;
        p=new T*[height];
        for(int i=0;i<height;i++){
            p[i]=new T[width];
        }
    }
    
    // 2 parameter constructor lets us write
    // SA x(10,20) and get a safe 10X20 matrix;
    SafeMatrix(int verticalSize, int horizontalSize){
        verticalLow=0;
        verticalHigh=verticalSize-1;
        horizontalLow=0;
        horizontalHigh=horizontalSize-1;
        height = verticalSize;
        width = horizontalSize;
        p=new T*[height];
        for(int i=0;i<height;i++){
            p[i]=new T[width];
        }
    }
    
    // 4 parameter constructor lets us set bounds on each dimension
    //SA(2,4,5,7); is a 3X3 matrix with indexes from 2->4 and 5->7
    SafeMatrix(int vLow, int vHigh, int hLow, int hHigh){
        if((vHigh-vLow+1)<=0 || (hHigh-hLow+1)<=0){
            cout<< "constructor error in bounds definition"<<endl;
            exit(1);
            
        }
        verticalLow=vLow;
        verticalHigh=vHigh;
        horizontalLow=hLow;
        horizontalHigh=hHigh;
        height = verticalHigh-verticalLow+1;
        width = horizontalHigh-horizontalLow+1;
        p= new T*[height];
        for(int i=0;i<height;i++){
            p[i]=new T[width];
        }
    }
    
    // copy constructor for pass by value and
    // initialization
    SafeMatrix(const SafeMatrix& s){
        verticalLow=s.verticalLow;
        verticalHigh=s.verticalHigh;
        horizontalLow=s.horizontalLow;
        horizontalHigh=s.horizontalHigh;
        height = verticalHigh-verticalLow+1;
        width = horizontalHigh-horizontalLow+1;
        
        p= new T*[height];
        for(int i=0; i<height; i++){
            p[i]=new T[width];
        }
        for(int i=0; i<height; i++){
            for(int j=0;j<width;j++){
                p[i][j] = s.p[i][j];
            }
        }
    }
    
    // destructor
    ~SafeMatrix(){
        for(int i=0;i<height;i++){
            delete [] p[i];
        }
        delete [] p;
    }
    
    
    SafeMatrix& operator=(const SafeMatrix &s){
        if(this==&s) return *this;
        
        for(int i=0;i<height;i++){
            delete [] p[i];
        }
        delete [] p;
        
        verticalLow=s.verticalLow;
        verticalHigh=s.verticalHigh;
        horizontalLow=s.horizontalLow;
        horizontalHigh=s.horizontalHigh;
        height = verticalHigh-verticalLow+1;
        width = horizontalHigh-horizontalLow+1;
        
        p= new T*[height];
        for(int i=0; i<height; i++){
            p[i]= new T[width];
        }
        for(int i=0; i<height; i++){
            for(int j=0;j<width;j++){
                p[i][j] = s.p[i][j];
            }
        }
        return *this;
    }
    
    class Proxy {
    private:
        T* array;
        int lowI, highI;
    public:
        Proxy(T* pass, int low, int high){
            array = pass;
            lowI = low;
            highI= high;
        }
        
        ~Proxy(){
            //delete [] array;
        }
        
        T& operator[](int index) {
            if(index<lowI || index>highI){
                cout<<"index "<<index<<" out of range"<<endl;
                exit(1);
            }
            return array[index-lowI];
        }
    };
    
    Proxy operator[](int r){
        if(r<verticalLow || r>verticalHigh){
            cout<<"index "<<r<<" out of range"<<endl;
            exit(1);
        }
        row = r-verticalLow;
        Proxy proxy(p[row],horizontalLow, horizontalHigh);
        return proxy;
    }
    
    SafeMatrix<T> operator*(const SafeMatrix &s){
        if(width!= s.height){
            cout<<"The width of the first and the height of the second need to be the same"<<endl;
            exit(1);
        }
        SafeMatrix<T> answer(height,s.width);
        for (int r = 0; r < answer.height; r++) {
            for (int c = 0; c < answer.width; c++) {
                answer[r][c]=0;
                for (int in = 0; in < answer.height; in++) {
                    answer[r][c] += p[r][in]*s.p[in][c];
                }
            }
        }
        return answer;
    }
    
    template <class U>
    friend ostream& operator<<(ostream& os, SafeMatrix<U> s);
};

template <class T>
ostream& operator<<(ostream& os, SafeMatrix<T> s){
    for(int i=0; i<s.height; i++){
        for(int j=0; j<s.width; j++){
            cout<<s.p[i][j]<<" ";
        }
        cout<<endl;
    }
    return os;
};
