//
// Created by 万健洲 on 2020/6/4.
//

#include "Vector.h"
#include <bits/stdc++.h>

using namespace std;

int main(){
    matrix E,A,B,C;
    E = E.identity();
    vec3f a1,a2,a3,a4;
    a1 = {1,-2,0};
    a2 = {0,3,-4};
    a3 = {0,0,5};
    a4 = {0,0,0};
    A.set_col(0,embed<4>(a1,0.f));
    A.set_col(1,embed<4>(a2,0.f));
    A.set_col(2,embed<4>(a3,-6.f));
    A.set_col(3,embed<4>(a4,7.f));
    cout<<A<<endl;

    B = (E+A).invert()*(E-A);
    C = (E+B).invert();
    cout<<C<<endl;

}