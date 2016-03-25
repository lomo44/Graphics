/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "OBJParser.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include "Vector.h"
#include "Face.h"
#include "MeshObject.h"

OBJParser::OBJParser(){
    
}
OBJParser::~OBJParser(){
    
}
void OBJParser::parsefile(std::string filepath){
    std::cout<<filepath<<std::endl;
    std::fstream fs;
    fs.open(filepath.c_str(),std::fstream::in);
    if(fs.good()){
        for(;!fs.eof();){
            std::string temp;
            std::getline(fs,temp);
            std::stringstream ss(temp);
            std::string buffer;
            ss>>buffer;
            if(buffer != "#" && buffer != "\0"){
            	if(buffer == "v" || buffer == "vn" || buffer == "vt"){
                    std::vector<Vector4f>& temp = m_Vbuffer;
                    if(buffer == "v"){
                    	std::cout<<"Vertex Added: ";
                    }
                    else if(buffer == "vn"){
                        std::cout<<"Normal Added: ";
                        temp = m_Nbuffer;
                    }
                    else if(buffer == "vt"){
                        std::cout<<"Texture Added";
                        temp = m_Tbuffer;
                    }
                    Vector4f vec;
                    ss>>buffer;
                    for(int i = 0;!ss.eof();i++){
                        vec[i] = atof(buffer.c_str());
                        ss>>buffer;
                    }
                    vec[3] = 1.0;
                    std::cout<<"X: "<<vec[0]<<" Y: "<<vec[1]<<" Z: "<<vec[2]<<std::endl;
                    temp.push_back(vec);
                }else if(buffer == "f"){
                    std::cout<<"Face added: " ;
                    ss>>buffer;
                    std::vector<Vector4i> _list;
                    for(int i = 0 ; !ss.eof();i++){
                    	int startp = 0;
                    	int numofslash = 0;
                    	Vector4i v;
                    	for(int j = 0;buffer[j]!='\0';j++){
                    		if(buffer[j] == '/'||buffer[j+1]=='\0'){
                    			int length = j-startp;
                    			if(length != 0){
                    				if(buffer[j+1]=='\0')
                    					length++;
                    				char temp[20];
                    				strncpy(temp,&buffer[startp],length);
                    				int index = atoi(&temp[0]);
                    				v[numofslash] = index;
                    			}
                    			numofslash++;
                    			startp = j+1;
                    		}
                    	}
                        ss>>buffer;
                        _list.push_back(v);
                    }
                    if(_list.size() == 3){
                    	Face* f1 = new Face();
                    	f1->m_V1 = _list[0];
                    	f1->m_V2 = _list[1];
                    	f1->m_V3 = _list[2];
                    	m_Fbuffer.push_back(f1);
                    }
                    if(_list.size() == 4){
                    	Face* f1 = new Face();
                    	Face* f2 = new Face();
                    	f1->m_V1 = _list[0];
                    	f1->m_V2 = _list[1];
                    	f1->m_V3 = _list[2];
                    	f2->m_V1 = _list[1];
                    	f2->m_V2 = _list[2];
                    	f2->m_V3 = _list[3];
                    	m_Fbuffer.push_back(f1);
                    	m_Fbuffer.push_back(f2);
                    }
                    std::cout<<std::endl;
                }
                else if(buffer == "s"){
                    std::cout<<"Shade change: ";
                    ss>>buffer;
                    m_CurrentShadingNum = atoi(&buffer[0]);
                }
                else if(buffer == "g"){
                	std::cout<<"Group change: ";
                	ss>>buffer;
                	m_CurrentShadingNum = atoi(&buffer[0]);
                }
                else{
                    std::cout<<buffer<<std::endl;
                }     
            }
        }
    }
    else{
        std::cout<<"File Not Found"<<std::endl;
    }
    fs.close();
}
void OBJParser::clearBuffer(){
	m_Vbuffer.clear();
	m_Nbuffer.clear();
	m_Tbuffer.clear();
	m_pOutPutObject = NULL;
}
