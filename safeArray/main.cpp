//
//  main.cpp
//  safeArray
//
//  Created by Maxwell Perry Grossman on 10/29/18.
//  Copyright © 2018 Maxwell Perry Grossman. All rights reserved.
//

#include <iostream>
using namespace std;

template <class T>
class SafeArray{
private:
    int verticalLow, verticalHigh, horizontalLow, horizontalHigh, row;
    T** p;
public:
    
    // default constructor
    // allows for writing things like SA a;
    SafeArray(){
        verticalLow=0;
        verticalHigh=-1;
        horizontalLow=0;
        horizontalHigh=-1;
        p=NULL;
    }
    
    //One parameter constructor to create a square matrix
    SafeArray(int size){
        verticalLow=0;
        verticalHigh=size-1;
        horizontalLow=0;
        horizontalHigh=size-1;
        p=new T*[size];
        for(int i=0;i<size;i++){
            p[i]=new T[size];
        }
    }
    
    // 2 parameter constructor lets us write
    // SA x(10,20) and get a safe 10X20 matrix;
    SafeArray(int verticalSize, int horizontalSize){
        verticalLow=0;
        verticalHigh=verticalSize-1;
        horizontalLow=0;
        horizontalHigh=horizontalSize-1;
        p=new T*[verticalSize];
        for(int i=0;i<verticalSize;i++){
            p[i]=new T[horizontalSize];
        }
    }
    
    // 4 parameter constructor lets us set bounds on each dimension
    //SA(2,4,5,7); is a 3X3 matrix with indexes from 2->4 and 5->7
    SafeArray(int vLow, int vHigh, int hLow, int hHigh){
        if((vHigh-vLow+1)<=0 || (hHigh-hLow+1)<=0){
            cout<< "constructor error in bounds definition"<<endl;
            exit(1);
            
        }
        verticalLow=vLow;
        verticalHigh=vHigh;
        horizontalLow=hLow;
        horizontalHigh=hHigh;
        p=new T*[(verticalHigh-verticalLow)+1];
        for(int i=0;i<((verticalHigh-verticalLow)+1);i++){
            p[i]=new T[((horizontalHigh-horizontalLow)+1)];
        }
    }
    
    // copy constructor for pass by value and
    // initialization
    SafeArray(const SafeArray & s){
        int size=s.verticalHigh-s.verticalLow+1;
        p= new T*[size];
        for(int i=0; i<size; i++){
            p[i]=new T[s.horizontalHigh-s.horizontalLow+1];
            for(int j=0;j<(s.horizontalHigh-s.horizontalLow+1);j++){
                p[i][j] = s.p[i][j];
            }
        }
        verticalLow=s.verticalLow;
        verticalHigh=s.verticalHigh;
        horizontalLow=s.horizontalLow;
        horizontalHigh=s.horizontalHigh;
    }
    // destructor
    
    ~SafeArray(){
        int size=verticalHigh-verticalLow+1;
        for(int i=0;i<size;i++){
            delete [] p[i];
        }
        delete [] p;
    }
    
    T* operator[](int r){
        if(r<verticalLow || r>verticalHigh){
            cout<<"index "<<r<<" out of range"<<endl;
            exit(1);
        }
        row = r-verticalLow;
        return p[row];
    }
    
    T operator[](short int c){
        if(c<horizontalLow || c>horizontalHigh){
            cout<<"index "<<c<<" out of range"<<endl;
            exit(1);
        }
        return *p[row][c-horizontalLow];
    }
    
//    SafeArray & operator=(const SafeArray & s){
//        if(this==&s) return *this;
//        delete []p;
//        int size = (s.high-s.low)+1;
//        p=new T[size];
//        for(int i=0;i<size;i++){
//            p[i]=s.p[i];
//        }
//        high = s.high;
//        low = s.low;
//        return *this;
//    }
    template <class U>
    friend ostream& operator<<(ostream& os, SafeArray<U> s);
};

template <class T>
ostream& operator<<(ostream& os, SafeArray<T> s){
    int size=s.verticalHigh-s.verticalLow+1;
    for(int i=0; i<size; i++){
        for(int j=0; j<(s.horizontalHigh-s.horizontalLow+1); j++){
            cout<<s.p[i][j]<<" ";
        }
        cout<<endl;
    }
    return os;
};


int main(){
    SafeArray<int> intArray(5,10,3,4);
    for(int i=5;i<=10;i++){
        for(int j=3;j<=4;j++){
            intArray[i][j]=5;
        }
    }
    cout<<intArray;
//    SafeArray<string> stringArray(10);
//    for(int i=0;i<10;i++){
//        stringArray[i]="string";
//    }
//    cout<<stringArray<<endl;



    return 0;
}
