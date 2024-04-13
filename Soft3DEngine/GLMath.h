#ifndef __HelloCpp__GLMath__

#define __HelloCpp__GLMath__



#include <iostream>

using namespace std;

#include "CMath.h"
enum Ec3dProjectionMode{
    ec3dOrthographicMode = 0,
    ec3dPerspectiveMode,
};


Matrix4 calculateViewMatrixInverse(const CVector4&eyePos,const CVector4&center,const CVector4&up);

Matrix4 calculateViewMatrix(const CVector4&eyePos,const CVector4&center,const CVector4&up);

Matrix4 calculateRotationMatrix(const CVector4&axis,float cosA,float sinA);

Matrix4 calculateTranslateMatrix(const CVector4&translate);

Matrix4 calculateScaleMatrix(float kx,float ky,float kz);

Matrix4 calculatePerspectiveProjectionMatrix(float fovy,float aspect,float zNear,float zFar);

Matrix4 calculateOrthoProjectionMatrix(float left,float right,float bottom,float top,float near,float far);



CVector4 convertFromViewportSpaceToWorldSpace(const CVector4&winPos,

                                                 const Matrix4&projMat,

                                                 const Matrix4&viewMat,

                                                 const float viewport[4]);

bool isLine3dIntersectWithTriangle3d(const CVector4&start,const CVector4&dir,

                                     const CVector4&p0,const CVector4&p1,const CVector4&p2);

CVector4 getIntersectPointOfLine3dIntersectWithPlane3d(const CVector4&start,const CVector4&dir,

                                     const CVector4&p,const CVector4&norm);

float calculate3dTriangleArea(const CVector4&v1,const CVector4&v2,const CVector4&v3);

#endif /* defined(__HelloCpp__c3dGLMath__) */
