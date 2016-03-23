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
                    if(buffer == "v")
                        std::cout<<"Vertex Added: ";
                    else if(buffer == "vn")
                        std::cout<<"Normal Added: ";
                    else if(buffer == "vt")
                        std::cout<<"Texture Added";
                    float temp[4] = {};
                    for(int i = 0;!ss.eof();i++){
                        ss>>buffer;
                        temp[i] = atof(buffer.c_str());
                    }
                    temp[3] = 1.0;
                    std::cout<<"X: "<<temp[0]<<" Y: "<<temp[1]<<" Z: "<<temp[2]<<std::endl;
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

void OBJParser::parseVertex(std::stringstream& ss){
    std::string buffer;
    ss>>buffer;
    for(int i = 0;!ss.eof();i++){
        ss>>buffer;
    }
}
