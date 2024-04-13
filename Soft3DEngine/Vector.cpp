#include "StdAfx.h"
#include "Vector.h"
//--------Cc3dVector2
void CVector2::initMembers(){
    memset(&m_array, 0, sizeof(m_array));
}
void CVector2::init(float a0,float a1){
    m_array[0]=a0;
    m_array[1]=a1;
}
CVector2::CVector2(float a0,float a1){
    initMembers();
    init(a0,a1);
}
CVector2::CVector2(const float array[2]){
    initMembers();
    init(array);
}
vector<float> CVector2::convertToVector()const{
    vector<float> vec(m_array,m_array+2);
    return vec;
}
CVector2 CVector2::operator +(const CVector2&right)const {
    CVector2 rs(this->x()+right.x(),this->y()+right.y());
    return rs;
}
CVector2 CVector2::operator -(const CVector2&right)const {
    CVector2 rs(this->x()-right.x(),this->y()-right.y());
    return rs;
}
CVector2 CVector2::operator *(float k)const {
    CVector2 rs(this->x()*k,this->y()*k);
    return rs;
}
void CVector2::init(const float array[2]){
    for(int i=0;i<2;i++){
        m_array[i]=array[i];
    }
}
void CVector2::print()const {
    //C3DLOG("Cc3dVector2: %f,%f",m_array[0],m_array[1]);
}
//--------Cc3dVector4
void CVector4::init(float a0,float a1,float a2,float a3){
    m_array[0]=a0;
    m_array[1]=a1;
    m_array[2]=a2;
    m_array[3]=a3;
    
}
CVector4::CVector4(float a0,float a1,float a2,float a3){
    initMembers();
    init(a0,a1,a2,a3);
}
CVector4::CVector4(const float array[4]){
    initMembers();
    init(array);
}

float CVector4::getAt(int index)const {
    //assert(index>=0&&index<=3);
    return m_array[index];
}
vector<float> CVector4::convertToVector()const{
    vector<float> vec(m_array,m_array+4);
    return vec;
}
CVector4 CVector4::operator +(const CVector4&right)const {
    CVector4 rs(this->x()+right.x(),this->y()+right.y(),this->z()+right.z(),this->w()+right.w());
    return rs;
}
CVector4 CVector4::operator -(const CVector4&right)const {
    CVector4 rs(this->x()-right.x(),this->y()-right.y(),this->z()-right.z(),this->w()-right.w());
    return rs;
}
CVector4 CVector4::operator *(float k)const {
    CVector4 rs(this->x()*k,this->y()*k,this->z()*k,this->w()*k);
    return rs;
}
void CVector4::init(const float array[4]){
    for(int i=0;i<4;i++){
        m_array[i]=array[i];
    }
}
void CVector4::print()const {
    //C3DLOG("Cc3dVector4: %f,%f,%f,%f",m_array[0],m_array[1],m_array[2],m_array[3]);
}