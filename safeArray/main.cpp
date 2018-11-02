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
    int low, high;
    T* p;
public:
    
    // default constructor
    // allows for writing things like SA a;
    
    SafeArray(){low=0; high=-1;p=NULL;}
    
    
    // 2 parameter constructor lets us write
    // SA x(10,20);
    
    SafeArray(int l, int h){
        if((h-l+1)<=0)
        {cout<< "constructor error in bounds definition"<<endl;
            exit(1);}
        low=l;
        high=h;
        p=new T[(h-l)+1];
    }
    // single parameter constructor lets us
    // create a SA almost like a "standard" one by writing
    // SA x(10); and getting an array x indexed from 0 to 9
    
    SafeArray(int i){
        low=0;
        high=i-1;
        p=new T[i];
    }
    // copy constructor for pass by value and
    // initialization
    
    SafeArray(const SafeArray & s){
        int size=s.high-s.low+1;
        p=new T[size];
        for(int i=0; i<size; i++)
            p[i]=s.p[i];
        low=s.low;
        high=s.high;
    }
    // destructor
    
    ~SafeArray(){
        delete [] p;
    }
    
    T& operator[](int i){
        if(i<low || i>high){
            cout<<"index "<<i<<" out of range"<<endl;
            exit(1);
        }
        return p[i-low];
    }
    
    SafeArray & operator=(const SafeArray & s){
        if(this==&s) return *this;
        delete []p;
        int size = (s.high-s.low)+1;
        p=new T[size];
        for(int i=0;i<size;i++){
            p[i]=s.p[i];
        }
        high = s.high;
        low = s.low;
        return *this;
    }
    template <class U>
    friend ostream& operator<<(ostream& os, SafeArray<U> s);
};

template <class T>
ostream& operator<<(ostream& os, SafeArray<T> s){
    int size=s.high-s.low+1;
    for(int i=0; i<size; i++)
        cout<<s.p[i]<<endl;
    return os;
};

template<class T>
class SafeMatrix{
    
private:
    int verticalLow, verticalHigh, horizontalLow, horizontalHigh;
    SafeArray<SafeArray<T>> p;
    int **p;
public:
    
    //default constructor
    //SafeMatrix SM();
    SafeMatrix(){
        verticalLow = 0;
        verticalHigh = -1;
        horizontalLow = 0;
        horizontalHigh = -1;
        p = NULL;
    }
    
    //one parameter constructor for square matrix
    
    SafeMatrix(int rowsCols){
        verticalLow = 0;
        verticalHigh = rowsCols-1;
        horizontalLow = 0;
        horizontalHigh = rowsCols-1;
        p = new int*[rowsCols];
        for(int i = 0; i < rowsCols; ++i){
            p[i] = new int[rowsCols];
        }
    }
    
    
    //Two parameter constructor for size bounds but not specific number bounds
    //SafeMatrix(10) would give you a 10X10 matrix with indexes from 0-9
    SafeMatrix(int vertical, int horizontal){
        verticalLow = 0;
        verticalHigh = vertical-1;
        horizontalLow = 0;
        horizontalHigh = horizontal-1;
        p = new int*[vertical];
        for(int i = 0; i < vertical; ++i){
            p[i] = new int[horizontal];
        }
    }
    
    //Four parameter constructor for specific bounds on rows and columns
    //SafeMatrix(2,4,3,6) would give you a 3 rows (with index from 2 to 4) by 4 columns (with index from 3 to 6) matrix
    SafeMatrix(int rowTop, int rowBottom, int colLeft, int colRight){
        if((rowBottom-rowTop+1)<=0 || (colRight-colLeft+1)<=0){
            cout<< "constructor error in bounds definition"<<endl;
            exit(1);
            
        }
        verticalLow = rowTop;
        verticalHigh = rowBottom;
        horizontalLow = colLeft;
        horizontalHigh = colRight;
        p = new int*[rowBottom-rowTop+1];
        for(int i = 0; i < rowBottom-rowTop+1; ++i){
            p[i] = new int[colRight-colLeft+1];
        }
    }
    
    ~SafeMatrix(){
        for(int i = 0; i < verticalHigh-verticalLow+1 ; ++i) {
            delete [] p[i];
        }
        delete [] p;
    }
    
    int& operator[](int i){
        if((i<verticalLow || i>verticalHigh) || (i<horizontalLow || i>horizontalHigh)){
            cout<< "constructor error in bounds definition"<<endl;
            exit(1);
            
        }
        return p[i-low];
    }
};

int main(){
    SafeArray<int> intArray(10);
    for(int i=0;i<10;i++){
        intArray[i]=i;
    }
    cout<<intArray<<endl;

    SafeArray<string> stringArray(10);
    for(int i=0;i<10;i++){
        stringArray[i]="string";
    }
    cout<<stringArray<<endl;


    return 0;
}
