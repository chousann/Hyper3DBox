#include "StdAfx.h"
#include "CTriangle.h"

CTriangle::CTriangle(int ID0,int ID1,int ID2){

    initMembers();

    init(ID0, ID1, ID2);

}



void CTriangle::init(int ID0,int ID1,int ID2){

    m_array[0]=ID0;

    m_array[1]=ID1;

    m_array[2]=ID2;

}

short CTriangle::vID(int i)const {

    //assert(i>=0&&i<=3);

    return m_array[i];

}

void CTriangle::setVID(int i,short vID){

    //assert(i>=0&&i<=3);

    m_array[i]=vID;

}

void CTriangle::initMembers(){

    memset(&m_array, 0, sizeof(m_array));

}



