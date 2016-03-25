/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: john
 *
 * Created on March 10, 2016, 9:55 PM
 */
#include <iostream>
#include <cstdlib>
#include "Vector.h"
#include "Color.h"
#include "Matrix.h"
#include "OBJParser.h"
#include <string>
#include <string.h>
using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    /*Vector4<float> newvec(1,0,0,0);
    Vector4<float> newvec2(0,1,0,0);
    float fin = newvec.dot(newvec2);
    Color4b c(0x00ffffff);
    OBJParser newp;
    newp.parsefile("/home/john/Desktop/Obj/playground1.obj");*/
    //fin.Print();
    //std::cout<<fin<<std::endl;
    string temp = "/12///12";
    char* pt;
    char s = '/';
    pt = strtok(&temp[0],&s);
    cout<<temp<<endl;
    cout<<pt<<endl;
    pt = strtok(NULL,&s);
    cout<<pt<<endl;
    return 0;
}

