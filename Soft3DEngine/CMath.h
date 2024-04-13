#ifndef __HelloCpp__CMath__

#define __HelloCpp__CMath__



#include <iostream>

using namespace std;
#include<math.h>
#include "Matrix.h"

#include "Vector.h"

#define square(x) ((x)*(x)) //must with the brackets

Matrix4 unitMat();

Matrix4 zeroMat();

CVector4 normalize(const CVector4&v);

CVector4 cross(const CVector4&v1,const CVector4&v2);

float dot(const CVector4&v1,const CVector4&v2);

bool isUnitMat(const Matrix4&mat);

bool isEqual(const Matrix4&mat1,const Matrix4&mat2,float eps=0);

bool isEqual(const CVector4&v1,const CVector4&v2,float eps=0);

Matrix4 inverse(const Matrix4&mat);

Matrix4 transpose(const Matrix4&mat);

CVector4 toV4(const CVector2&v2,float z,float w);

CVector2 toV2(const Matrix4&v4);

float getLength2(const CVector4&v);

float getLength(const CVector4&v);

CVector4 perComponentProduct(const CVector4&v1,const CVector4&v2);
inline float pow2(float x){return x*x;}
#endif /* defined(__HelloCpp__c3dMath__) */
