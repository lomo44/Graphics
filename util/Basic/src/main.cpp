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
#include "MeshObject.h"
#include <string>
#include <string.h>
using namespace std;

/*
 * 
 */
Vector4i test(string _temp){
	int startp = 0;
	int numofslash = 0;
	Vector4i v;
	for(int j = 0;_temp[j]!='\0';j++){
		if(_temp[j] == '/'||_temp[j+1]=='\0'){
			int length = j-startp;
			if(length != 0){
				if(_temp[j+1]=='\0')
					length++;
				char temp[20];
				strncpy(temp,&_temp[startp],length);
				int index = atoi(&temp[0]);
				v[numofslash] = index;
			}
			numofslash++;
			cout<<length<<endl;
			startp = j+1;
		}
		//cout<<j<<endl;
	}
	return v;
}

int main(int argc, char** argv) {
    //fin.Print();
    //std::cout<<fin<<std::endl;
    string temp = "12//13";
    Vector4i ret = test(temp);
    ret.Print();
    OBJParser* newparser  = new OBJParser();
    newparser->parsefile("/h/u5/c5/04/c5lizhua/git/Graphics/Obj/FinalBaseMesh.obj");
    MeshObject* out = newparser->getOutputObject();
    out->print();
    return 0;
}

