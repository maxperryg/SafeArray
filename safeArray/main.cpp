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
        p= new T*[verticalHigh-verticalLow+1];
        for(int i=0;i<(verticalHigh-verticalLow+1);i++){
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
    
    template <class B>
    class Proxy {
    public:
        Proxy(B* pass){
            array = pass;
        }
        
        B& operator[](int index) {
            cout<<"\n this is also being called\n";
            return array[index];
        }
    private:
        B* array;
    };
    
    Proxy<T> operator[](int r){
        if(r<verticalLow || r>verticalHigh){
            cout<<"index "<<r<<" out of range"<<endl;
            exit(1);
        }
        row = r-verticalLow;
        cout<<"\n this is being called\n";
        return Proxy<T>(p[row]);
    }
//
//    T operator[](short int c){
//        if(c<horizontalLow || c>horizontalHigh){
//            cout<<"index "<<c<<" out of range"<<endl;
//            exit(1);
//        }
//        cout<<"\n this is also being called\n";
//        return *p[row][c-horizontalLow];
//    }
    
    SafeArray & operator=(const SafeArray & s){
        if(this==&s) return *this;
        
        int size=verticalHigh-verticalLow+1;
        for(int i=0;i<size;i++){
            delete [] p[i];
        }
        delete [] p;
        
        size=s.verticalHigh-s.verticalLow+1;
        p=new T*[size];
        for(int i=0;i<size;i++){
            p[i]=new T[s.horizontalHigh-s.horizontalLow+1];
            for(int j=0;j<(s.horizontalHigh-s.horizontalLow+1);j++){
                p[i][j] = s.p[i][j];
            }
        }
        verticalLow=s.verticalLow;
        verticalHigh=s.verticalHigh;
        horizontalLow=s.horizontalLow;
        horizontalHigh=s.horizontalHigh;
        return *this;
    }
    
    template <class U>
    friend ostream& operator<<(ostream& os, SafeArray<U> s);
};

template <class T>
ostream& operator<<(ostream& os, SafeArray<T> s){
    int size=s.verticalHigh-s.verticalLow+1;
    for(int i=0; i<size; i++){
        size=s.horizontalHigh-s.horizontalLow+1;
        for(int j=0; j<size; j++){
            //cout<<"s.p[i] is  "<<s.p[i];
            cout<<s.p[i][j]<<" ";
        }
        cout<<endl;
    }
    return os;
};


int main(){
    SafeArray<int> intArray(5,7, 5, 7);
    for(int i=5;i<=7;i++){
        for(int j=5;j<=7;j++){
            intArray[i][j]=j;
            cout<<intArray[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<intArray;
//    SafeArray<string> stringArray(10);
//    for(int i=0;i<10;i++){
//        stringArray[i]="string";
//    }
//    cout<<stringArray<<endl;



    return 0;
}
