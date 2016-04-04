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
#include "Attribute.h"
OBJParser::OBJParser(){
    m_CurrentShadingNum = 0;
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
            		//std::cout<<buffer<<std::endl;
            		std::string vertex_type = buffer;
                    Vector4f vec;
                    for(int i = 0;!ss.eof();i++){
                        ss>>buffer;
                        vec[i] = atof(buffer.c_str());
                    }
                    
                    //std::cout<<"X: "<<vec[0]<<" Y: "<<vec[1]<<" Z: "<<vec[2]<<std::endl;
                    if(vertex_type == "v"){
                    	//std::cout<<"Vertex Added: "
                        vec[3] = 1.0;
                    	m_Vbuffer.push_back(vec);
                        //vec.Print();
                    }
                    else if(vertex_type == "vn"){
                        //std::cout<<"Normal Added: ";
                        vec[3] = 0.0;
                        m_Nbuffer.push_back(vec);
                    }
                    else if(vertex_type == "vt"){
                        //std::cout<<"Texture Added";
                        m_Tbuffer.push_back(vec);
                    }
                }else if(buffer == "f"){
                    //std::cout<<"Face added: " ;
                    std::vector<Vector4i> _list;
                    std::vector<std::string> string_list;
                    while(ss>>buffer){
                        string_list.push_back(buffer);
                    }
                    for(int i = 0 ; i<string_list.size();i++){
                        buffer = string_list[i];
                    	int startp = 0;
                    	int numofslash = 0;
                    	Vector4i v;
                    	for(int j = 0;buffer[j]!='\0';j++){
                    		if(buffer[j] == '/'||buffer[j+1]=='\0'){
                    			int length = j-startp;
                                        if(buffer[j+1] == '\0')
                    			length++;
                    			if(length != 0){
                    				char temp[100];
                    				strncpy(temp,&buffer[startp],length);
                    				temp[length] = '\0';
                    				int index = atoi(&temp[0]);
                    				v[numofslash] = index;
                    			}
                    			numofslash++;
                    			startp = j+1;
                    		}
                    	}   
                        _list.push_back(v);
                    }
                    for(unsigned i = 0; i < _list.size(); i++){
                           _list[i].Print();
                     }
                    std::cout<<std::endl;
                    if(_list.size() == 3){
                    	Triangle f1;
                    	f1.m_V1 = _list[0];
                    	f1.m_V2 = _list[1];
                    	f1.m_V3 = _list[2];
                    	f1.m_iShadingGroup = this->m_CurrentShadingNum;
                    	m_Fbuffer.push_back(f1);
                    }
                    else if(_list.size() == 4){

                    	Triangle f1;
                    	Triangle f2;
                    	f1.m_V1 = _list[0];
                    	f1.m_V2 = _list[1];
                    	f1.m_V3 = _list[2];
                    	f2.m_V1 = _list[0];
                    	f2.m_V2 = _list[2];
                    	f2.m_V3 = _list[3];
                    	f1.m_iShadingGroup = this->m_CurrentShadingNum;
                    	f2.m_iShadingGroup = this->m_CurrentShadingNum;
                    	m_Fbuffer.push_back(f1);
                    	m_Fbuffer.push_back(f2);
                    }
                }
                else if(buffer == "s"){
                    //std::cout<<"Shade change: ";
                    ss>>buffer;
                    m_CurrentShadingNum = atoi(&buffer[0]);
                }
                else if(buffer == "g"){
                	//std::cout<<"Group change: ";
                	ss>>buffer;
                	m_CurrentGroup= buffer;
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
    printParsedInformation();
    fs.close();
}
void OBJParser::clearBuffer(){
	m_Vbuffer.clear();
	m_Nbuffer.clear();
	m_Tbuffer.clear();
}

void OBJParser::printParsedInformation(){
	std::cout<<"File Parsed"<<std::endl;
	std::cout<<"Total Number of Vertex: "<<m_Vbuffer.size()<<std::endl;
	std::cout<<"Total Number of Normal: "<<m_Nbuffer.size()<<std::endl;
	std::cout<<"Total Number of Texture Point: "<<m_Tbuffer.size()<<std::endl;
	std::cout<<"Total Number of Faces: "<<m_Fbuffer.size()<<std::endl;
}

MeshObject* OBJParser::getOutputObject(){
	Vector4f* vertexlist = new Vector4f[this->m_Vbuffer.size()];
	for(unsigned int i = 0 ; i < m_Vbuffer.size();i++){
		vertexlist[i] = m_Vbuffer[i];
	}
	Vector4f* Normallist = new Vector4f[this->m_Nbuffer.size()];
		for(unsigned int i = 0 ; i < m_Nbuffer.size();i++){
			Normallist[i] = m_Nbuffer[i];
	}
	Vector4f* Textlist = new Vector4f[this->m_Tbuffer.size()];
	for(unsigned int i = 0 ; i < m_Tbuffer.size();i++){
		Textlist[i] = m_Tbuffer[i];
	}
	Triangle* face = new Triangle[m_Fbuffer.size()];
	for(unsigned int i = 0; i < m_Fbuffer.size();i++){
		face[i] = m_Fbuffer[i];
	}
	Attr_MeshObject _new;
	_new.m_Normallist = Normallist;
	_new.m_Texturelist = Textlist;
	_new.m_Trianglelist = face;
	_new.m_Vertexlist = vertexlist;
	_new.m_iTriangleCount = m_Fbuffer.size();
	_new.m_iNormalCount = m_Nbuffer.size();
	_new.m_iTextureCount = m_Tbuffer.size();
	_new.m_iVertexCount = m_Vbuffer.size();
	MeshObject* ret = new MeshObject(_new);
	return ret;
}
