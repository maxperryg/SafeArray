//
//  main.cpp
//  safeArray
//
//  Created by Maxwell Perry Grossman on 10/29/18.
//  Copyright © 2018 Maxwell Perry Grossman. All rights reserved.
//

#include <iostream>
#include "SafeMatrix.cpp"
using namespace std;

int main(){
    SafeMatrix<int> intArrayA(5,7, 5, 7);
    for(int i=5;i<=7;i++){
        for(int j=5;j<=7;j++){
            intArrayA[i][j]=j;
        }
    }
    cout<<intArrayA<<endl;
    
    SafeMatrix<int> intArrayB(5,7, 5, 7);
    for(int i=5;i<=7;i++){
        for(int j=5;j<=7;j++){
            intArrayB[i][j]=j+i;
        }
    }
    cout<<intArrayB<<endl;
    
    cout<<intArrayA*intArrayB<<endl;
    
//    SafeArray<string> stringArray(10);
//    for(int i=0;i<10;i++){
//        stringArray[i]="string";
//    }
//    cout<<stringArray<<endl;



    return 0;
}
