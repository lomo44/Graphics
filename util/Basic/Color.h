/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Color.h
 * Author: john
 *
 * Created on March 10, 2016, 11:00 PM
 */

#ifndef COLOR_H
#define COLOR_H

class Color4b{
public:
    Color4b(){
        this->_c = 0;
    }
    Color4b(int _hex){
        this->_c = _hex;
    }
    Color4b(int R,int G,int B, int A){
        ARGB[0] = B;
        ARGB[1] = G;
        ARGB[2] = R;
        ARGB[3] = A;
    }
    inline int B(){return ARGB[0];}
    inline int G(){return ARGB[1];}
    inline int R(){return ARGB[2];}
    inline int A(){return ARGB[3];}
    union{
            unsigned int _c;
            unsigned char ARGB[4];
    };
};

class Color4f{
public:
    Color4f(){
        _f = new float[4];
        _f[0] = 0;
        _f[1] = 0;
        _f[2] = 0;
        _f[3] = 0;
    }
    Color4f(float R, float G, float B, float A){
        _f = new float[4];
        _f[0] = B;
        _f[1] = G;
        _f[2] = R;
        _f[3] = A;
    }
    Color4f(const Color4f& rhs){
        _f = new float[4];
        _f[0] = rhs.B();
        _f[1] = rhs.G();
        _f[2] = rhs.A();
        _f[3] = rhs.R();
    }
    ~Color4f(){
        delete _f;
    }
    inline float B() const{return _f[0];}
    inline float G() const{return _f[1];}
    inline float R() const{return _f[2];}
    inline float A() const{return _f[3];}
private:
    float* _f;
};

class ColorConverter{
    static Color4f Color4bto4f(Color4b _4b){
        return Color4f(((float)_4b.A())/256,((float)_4b.A())/256,
                ((float)_4b.A())/256,((float)_4b.A())/256);
    }
    static Color4b Color4fto4b(Color4b _4f){
        return Color4b((int)(_4f.R()*256),(int)(_4f.G()*256),
                (int)(_4f.B()*256),(int)(_4f.A()*256));
    }
};

#endif /* COLOR_H */

