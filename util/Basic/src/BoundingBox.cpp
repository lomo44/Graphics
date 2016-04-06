/*
 * BoundingBox.cpp
 *
 *  Created on: Apr 1, 2016
 *      Author: c5lizhua
 */

#include "BoundingBox.h"
#include "Face.h"

#include <assert.h>
BoundingBox::BoundingBox(const Vector4f& _MaxXYZ, const Vector4f& _MinXYZ) {
	// TODO Auto-generated constructor stub
    m_MaxXYZ = _MaxXYZ;;
    m_MinXYZ = _MinXYZ;
    m_pVectorList = new Vector4f[8];
    m_pVectorList[0] = Vector4f(_MinXYZ[0],_MaxXYZ[1],_MaxXYZ[2],1.0);
    m_pVectorList[1] = Vector4f(_MinXYZ[0],_MaxXYZ[1],_MinXYZ[2],1.0);
    m_pVectorList[2] = Vector4f(_MaxXYZ[0],_MaxXYZ[1],_MinXYZ[2],1.0);
    m_pVectorList[3] = Vector4f(_MaxXYZ[0],_MaxXYZ[1],_MaxXYZ[2],1.0);
    m_pVectorList[4] = Vector4f(_MinXYZ[0],_MinXYZ[1],_MaxXYZ[2],1.0);
    m_pVectorList[5] = Vector4f(_MinXYZ[0],_MinXYZ[1],_MinXYZ[2],1.0);
    m_pVectorList[6] = Vector4f(_MaxXYZ[0],_MinXYZ[1],_MinXYZ[2],1.0);
    m_pVectorList[7] = Vector4f(_MaxXYZ[0],_MinXYZ[1],_MaxXYZ[2],1.0);
}

BoundingBox::~BoundingBox() {
	// TODO Auto-generated destructor stub
}

bool BoundingBox::checkIntersect(const Line& temp){
    assert(temp.m_StartPoint[3] == 1.0);
    if((temp.m_StartPoint[0] >= m_MinXYZ[0] && temp.m_StartPoint[0] <= m_MaxXYZ[0])&&
        (temp.m_StartPoint[1] >= m_MinXYZ[1] && temp.m_StartPoint[1] <= m_MaxXYZ[1])&&
        (temp.m_StartPoint[2] >= m_MinXYZ[2] && temp.m_StartPoint[2] <= m_MaxXYZ[2])
        ){
        return true;
    }
    else{
        int i = 1;
        float invx = 1/temp.m_Direction[0];
        float invy = 1/temp.m_Direction[1];
        float invz = 1/temp.m_Direction[2];
        float t1 = (m_MaxXYZ[1] - temp.m_StartPoint[1])*invy;//up
        float t2 = (m_MinXYZ[1] - temp.m_StartPoint[1])*invy;//down
        float t3 = (m_MaxXYZ[0] - temp.m_StartPoint[0])*invx;//right
        float t4 = (m_MinXYZ[0] - temp.m_StartPoint[0])*invx;//left
        float t5 = (m_MaxXYZ[2] - temp.m_StartPoint[2])*invz;//front
        float t6 = (m_MinXYZ[2] - temp.m_StartPoint[2])*invz;//back
        Vector4f p1 = temp.getPoint(t1);
        Vector4f p2 = temp.getPoint(t2);
        Vector4f p3 = temp.getPoint(t3);
        Vector4f p4 = temp.getPoint(t4);
        Vector4f p5 = temp.getPoint(t5);
        Vector4f p6 = temp.getPoint(t6); 
        i *= BoundingBox::isNotin2DPlane(m_MaxXYZ[0],m_MinXYZ[0],m_MaxXYZ[2],m_MinXYZ[2],p1[0],p1[2]);
        if(i == 0) return true;
        i *= BoundingBox::isNotin2DPlane(m_MaxXYZ[0],m_MinXYZ[0],m_MaxXYZ[2],m_MinXYZ[2],p2[0],p2[2]);
        if(i == 0) return true;
        i *= BoundingBox::isNotin2DPlane(m_MaxXYZ[1],m_MinXYZ[1],m_MaxXYZ[2],m_MinXYZ[2],p3[1],p3[2]);
        if(i == 0) return true;
        i *= BoundingBox::isNotin2DPlane(m_MaxXYZ[1],m_MinXYZ[1],m_MaxXYZ[2],m_MinXYZ[2],p4[1],p4[2]);
        if(i == 0) return true;
        i *= BoundingBox::isNotin2DPlane(m_MaxXYZ[0],m_MinXYZ[0],m_MaxXYZ[1],m_MinXYZ[1],p5[0],p5[1]);
        if(i == 0) return true;
        i *= BoundingBox::isNotin2DPlane(m_MaxXYZ[0],m_MinXYZ[0],m_MaxXYZ[1],m_MinXYZ[1],p6[0],p6[1]);
        if(i==1){
            return false;
        }
        else{
            return true;
        }
    }
    return false;
}

Attr_Intersection* BoundingBox::isIntersect(const Line& _l){
    Line temp = _l;
    temp.m_Direction = this->m_Transform * _l.m_Direction;
    temp.m_StartPoint = this->m_Transform * _l.m_StartPoint;
    assert(temp.m_StartPoint[3] == 1.0);
    if((temp.m_StartPoint[0] >= m_MinXYZ[0] && temp.m_StartPoint[0] <= m_MaxXYZ[0])&&
        (temp.m_StartPoint[1] >= m_MinXYZ[1] && temp.m_StartPoint[1] <= m_MaxXYZ[1])&&
        (temp.m_StartPoint[2] >= m_MinXYZ[2] && temp.m_StartPoint[2] <= m_MaxXYZ[2])
        ){
        return new Attr_Intersection();
    }
    else{
        int i = 1;
        float invx = 1/temp.m_Direction[0];
        float invy = 1/temp.m_Direction[1];
        float invz = 1/temp.m_Direction[2];
        float t1 = (m_MaxXYZ[1] - temp.m_StartPoint[1])*invy;//up
        float t2 = (m_MinXYZ[1] - temp.m_StartPoint[1])*invy;//down
        float t3 = (m_MaxXYZ[0] - temp.m_StartPoint[0])*invx;//right
        float t4 = (m_MinXYZ[0] - temp.m_StartPoint[0])*invx;//left
        float t5 = (m_MaxXYZ[2] - temp.m_StartPoint[2])*invz;//front
        float t6 = (m_MinXYZ[2] - temp.m_StartPoint[2])*invz;//back
        Vector4f p1 = temp.getPoint(t1);
        Vector4f p2 = temp.getPoint(t2);
        Vector4f p3 = temp.getPoint(t3);
        Vector4f p4 = temp.getPoint(t4);
        Vector4f p5 = temp.getPoint(t5);
        Vector4f p6 = temp.getPoint(t6); 
        i *= BoundingBox::isNotin2DPlane(m_MaxXYZ[0],m_MinXYZ[0],m_MaxXYZ[2],m_MinXYZ[2],p1[0],p1[2]);
        if(i == 0) return new Attr_Intersection();
        i *= BoundingBox::isNotin2DPlane(m_MaxXYZ[0],m_MinXYZ[0],m_MaxXYZ[2],m_MinXYZ[2],p2[0],p2[2]);
        if(i == 0) return new Attr_Intersection();
        i *= BoundingBox::isNotin2DPlane(m_MaxXYZ[1],m_MinXYZ[1],m_MaxXYZ[2],m_MinXYZ[2],p3[1],p3[2]);
        if(i == 0) return new Attr_Intersection();
        i *= BoundingBox::isNotin2DPlane(m_MaxXYZ[1],m_MinXYZ[1],m_MaxXYZ[2],m_MinXYZ[2],p4[1],p4[2]);
        if(i == 0) return new Attr_Intersection();
        i *= BoundingBox::isNotin2DPlane(m_MaxXYZ[0],m_MinXYZ[0],m_MaxXYZ[1],m_MinXYZ[1],p5[0],p5[1]);
        if(i == 0) return new Attr_Intersection();
        i *= BoundingBox::isNotin2DPlane(m_MaxXYZ[0],m_MinXYZ[0],m_MaxXYZ[1],m_MinXYZ[1],p6[0],p6[1]);
        if(i==1){
            return NULL;
        }
        else{
            return new Attr_Intersection();
        }
    }
    return NULL;
}