/*
 * BoundingBox.h
 *
 *  Created on: Apr 1, 2016
 *      Author: c5lizhua
 */

#ifndef BOUNDINGBOX_H_
#define BOUNDINGBOX_H_
#include "Vector.h"
#include "RenderObject.h"
#include "Attribute.h"
class Line;
class Face;
class BoundingBox : public RenderObject{
public:
	BoundingBox(const Vector4f& _MaxXYZ, const Vector4f& _MinXYZ);
    bool checkIntersect(const Line& _l);
    Attr_Intersection* isIntersect(const Line& _l);
    inline static int isNotin2DPlane(float x_max, float x_min, 
        float y_max, float y_min, float px,
    float py){
        if(px >= x_min && px <= x_max && py >= y_min && py <= y_max){
            return 0;
        }
        else{
            return 1;
        }
    }
	virtual ~BoundingBox();
    Vector4f m_MaxXYZ;
    Vector4f m_MinXYZ;
private:
    void InitializeBoundingbox();

    Vector4f* m_pVectorList;
};

#endif /* BOUNDINGBOX_H_ */
