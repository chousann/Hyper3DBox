#ifndef __HelloCpp__Camera__

#define __HelloCpp__Camera__



#include <iostream>

using namespace std;



#include "Vector.h"

#include "Matrix.h"

#include "GLMath.h"
#define cc3dv4(x,y,z,w) CVector4(x,y,z,w)
enum Ec3dMatStackName{
    ec3dModelViewStack = 0,
    ec3dProjectionStack,
    ec3dTextureStack,
};


#include "Range.h"
class CSize{
public:
	float m_width;
	float m_height;
	CSize(){}
	CSize(float width,float height){m_width=width;m_height=height;}
	virtual ~CSize(){}
	float getWidth()const{return m_width;}
	float getHeight()const{return m_height;}
};
class Camera

{
	protected:

    //projection mode type

    Ec3dProjectionMode m_projectionMode;

    //perspective projection mode params

    float m_fovy;

    float m_aspect;

    float m_zNear;

    float m_zFar;

    //Ortho projection mode params

    Range m_range;//in the camera space

protected:
	CVector4 m_eyePos;
	CVector4 m_center;
	CVector4 m_up;

public:
	float ydir;
	void init(CVector4 eyePos,CVector4 center,CVector4 up,float w,float h){
		m_eyePos=eyePos;
		m_center=center;
		ydir=0;
		m_up=up;
		m_fovy=60;
        m_aspect=w/h;
        m_zNear=500;
        m_zFar=1200;//1500;
		m_range.init(-w/2, -w/2+w, -h/2, -h/2+h,

                     1024,//yeah, better to use negative value

                     1024
					 );

        m_projectionMode=ec3dPerspectiveMode;
	}

    Camera(float w,float h){


        m_fovy=60;

        m_aspect=w/h;

        m_zNear=0.5;

        m_zFar=150;//1500;

       

        m_range.init(-w/2, -w/2+w, -h/2, -h/2+h,

                     1024,//yeah, better to use negative value

                     1024
					 );

        m_projectionMode=ec3dPerspectiveMode;





    }
	Camera(){
	}

    virtual ~Camera(){

    }
	void takePicture();





    CVector4 getEyePos()const;

    CVector4 getCenter()const;

    CVector4 getUp()const;

    void setEyePos(const CVector4&eyePos);

    void setCenter(const CVector4&center);

    void setUp(const CVector4&up);

    float getFovy()const {return m_fovy;}

    float getAspect()const {return m_aspect;}

    float getzNear()const {return m_zNear;}

    float getzFar()const {return m_zFar;}

    void setFovy(float fovy){m_fovy=fovy;}

    void setAspect(float aspect){m_aspect=aspect;}

    void setzNear(float zNear){m_zNear=zNear;}

    void setzFar(float zFar){m_zFar=zFar;}

    Range getRange()const {return m_range;}

    void setRange(const Range&range){m_range=range;}

    Matrix4 calculateViewMat()const;

    Matrix4 calculateViewMatInverse()const;

    Matrix4 calculateProjectionMat()const;

    Ec3dProjectionMode getProjectionMode()const{return m_projectionMode;}

    void setProjectionMode(Ec3dProjectionMode projectionMode){m_projectionMode=projectionMode;}


    void printProjectionMode()const;
	void rotate(const CVector4&axis,float cosA,float sinA);


};

#endif /* defined(__HelloCpp__c3dCamera__) */
