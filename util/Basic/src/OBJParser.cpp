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
#include "ObjectGroup"
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
                if(buffer == "g"){
                    std::cout<<"Group Added"<<std::endl;
                    
                }else if(buffer == "v" || buffer == "vn" || buffer == "vt"){
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
                    for(int i = 0 ; !ss.eof();i++){
                        char* pt;
                        char backslash = '/';
                        //std::cout<<buffer;
                        pt = strtok(&buffer[0],&backslash);
                        for(;pt!=NULL;){
                            int a = atoi(pt);
                            std::cout<<a<<"/";
                            pt = strtok(NULL,&backslash);
                        }
                        std::cout<<"-"; 
                        ss>>buffer;
                    }
                    std::cout<<std::endl;
                        
                }
                else if(buffer == "g"){
                    std::cout<<"Group added: ";
                    ss>>buffer;
                    std::cout<<atoi(&buffer[0])<<std::endl;
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
