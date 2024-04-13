#include "StdAfx.h"
#include "Camera.h"



CVector4 Camera::getEyePos()const{
	return m_eyePos;
}

CVector4 Camera::getCenter()const{

	return m_center;

}

CVector4 Camera::getUp()const{


	return m_up;

}

void Camera::setEyePos(const CVector4&eyePos){
	m_eyePos=eyePos;


    

}

void Camera::setCenter(const CVector4&center){
	m_center=center;


    

}

void Camera::setUp(const CVector4&up){
	m_up=up;




}


//从世界坐标系表示转换到相机坐标系表示
Matrix4 Camera::calculateViewMat()const {


    Matrix4 ret;



    ret=::calculateViewMatrix(getEyePos(), getCenter(), getUp());


    return ret;

    

};
//从相机坐标系表示转换到世界坐标系表示的矩阵
Matrix4 Camera::calculateViewMatInverse()const {

    Matrix4 ret;


        ret=::calculateViewMatrixInverse(getEyePos(), getCenter(), getUp());

 

    return ret;

}

Matrix4 Camera::calculateProjectionMat()const {

    Matrix4 projectionMat;

    switch (m_projectionMode) {

        case ec3dPerspectiveMode:

            projectionMat=::calculatePerspectiveProjectionMatrix(m_fovy, m_aspect, m_zNear, m_zFar);

            break;

        case ec3dOrthographicMode:

            projectionMat=::calculateOrthoProjectionMatrix(m_range.getMinX(), m_range.getMaxX(), m_range.getMinY(), m_range.getMaxY(), m_range.getMinZ(), m_range.getMaxZ());

            break;

        default:

            //assert(false);

            break;

    }

    return projectionMat;

}


void Camera::printProjectionMode()const{

    if(m_projectionMode==ec3dPerspectiveMode){

        //C3DLOG("projectionMode: perspectiveMode");

    }else if(m_projectionMode==ec3dOrthographicMode){

        //C3DLOG("projectionMode: orthographic");

    }else{

        //assert(false);

    }

}

void Camera::rotate(const CVector4&axis,float cosA,float sinA){
	Matrix4 viewMat=calculateViewMat();
	Matrix4 modelMatOfCamera=inverse(viewMat);
	Matrix4 rotMat=calculateRotationMatrix(axis,cosA,sinA);
	Matrix4 newModelMatOfCamera=modelMatOfCamera*rotMat;
	CVector4 up=cc3dv4(newModelMatOfCamera.getAt(4),newModelMatOfCamera.getAt(5),newModelMatOfCamera.getAt(6),newModelMatOfCamera.getAt(7));
	CVector4 dir=cc3dv4(newModelMatOfCamera.getAt(8),newModelMatOfCamera.getAt(9),newModelMatOfCamera.getAt(10),newModelMatOfCamera.getAt(11))*(-1);
	CVector4 eyepos=cc3dv4(newModelMatOfCamera.getAt(12),newModelMatOfCamera.getAt(13),newModelMatOfCamera.getAt(14),newModelMatOfCamera.getAt(15));
	up.setw(0);
	dir.setw(0);
	eyepos.setw(1);
	//update camera
	m_eyePos=eyepos;
	m_center=m_eyePos+dir;
	m_up=up;

}

void Camera::takePicture(){

}