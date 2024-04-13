#ifndef __HelloCpp__Matrix__
#define __HelloCpp__Matrix__

#include <iostream>
#include <vector>
using namespace std;
#include "Vector.h"

class Matrix4 
{
public:
    Matrix4(){
        initMembers();
    }
    Matrix4(const float array[16]);
    Matrix4(float a0,float a1,float a2,float a3,//col 1
                         float a4,float a5,float a6,float a7,//col2
                         float a8,float a9,float a10,float a11,//col3
                         float a12,float a13,float a14,float a15//col4
    );
    ~Matrix4(){}
    void init(const float array[16]);
    void init(float a0,float a1,float a2,float a3,//col 1
                    float a4,float a5,float a6,float a7,//col2
                    float a8,float a9,float a10,float a11,//col3
                    float a12,float a13,float a14,float a15//col4
    );
    const float* getArray()const{return  m_array;}
    float getAt(int index)const;
    void setAt(int index,float value);
    int getArrayLen()const{return 16;}
    vector<float> convertToVector()const;
    Matrix4 operator*(const Matrix4&mat)const;
    CVector4 operator*(const CVector4&v)const;
	Matrix4 operator*(float k)const;
	Matrix4 operator+(const Matrix4&mat)const;
	void initRoMatriX(float theta);
	void initRoMatriY(float theta);
	void initRoMatriZ(float theta);
    void print();
private:
    void initMembers();
private:
    float m_array[16];
  
    
};
#endif /* defined(__HelloCpp__c3dMatrix__) */