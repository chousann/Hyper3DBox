#include "StdAfx.h"
#include "GLMath.h"
const float M_PI=3.1415926;
//计算三角形面积
float calculate3dTriangleArea(const CVector4&v1,const CVector4&v2,const CVector4&v3){
	float area=0.5*getLength(cross(v2-v1,v3-v1));
	return area;
}
//从相机坐标系表示转换到世界坐标系表示的矩阵
Matrix4 calculateViewMatrixInverse(const CVector4&_eyePos,const CVector4&_center,const CVector4&_up)

{//up no need to be unit vector

    //assert(_eyePos.w()==1);

    //assert(_center.w()==1);

   // assert(_up.w()==0);

    CVector4 forward,side,up;

    forward=_center-_eyePos;

    up=_up;

    forward=normalize(forward);

    /* Side = forward x up */

    side=cross(up, forward);

    side=normalize(side);

    /* Recompute up as: up = side x forward */

    up=cross(forward, side);

    //calculate back (use back as Z axis)

    CVector4 back=forward;//Cc3dVector4(0,0,0,0)-forward;

    //the matrix transform point from camera space to world space is

    float m[16]={

        side.x(),side.y(),side.z(),0,//col1

        up.x(),up.y(),up.z(),0,

        back.x(),back.y(),back.z(),0,

        _eyePos.x(),_eyePos.y(),_eyePos.z(),1

    };

    Matrix4 viewMatInverse(m);

    return viewMatInverse;

}

//从世界坐标系表示转换到相机坐标系表示

Matrix4 calculateViewMatrix(const CVector4&eyePos,const CVector4&center,const CVector4&up)

{//up no need to be unit vector

    //assert(eyePos.w()==1);

    //assert(center.w()==1);

    //assert(up.w()==0);

    Matrix4 viewMatInverse=calculateViewMatrixInverse(eyePos, center, up);

    //inverse viewMatInverse to get viewMat

    //notice that the left up 3x3 sub matrix of viewMatInverse is orthogonal matrix,

    //so we have easy way to inverse it, see:

    //http://user.qzone.qq.com/350479720/blog/1329478296

    //calculate the fourth col of view mat

    const float *mInv=viewMatInverse.getArray();

    float x=-(mInv[12]*mInv[0]+mInv[13]*mInv[1]+mInv[14]*mInv[2]);

    float y=-(mInv[12]*mInv[4]+mInv[13]*mInv[5]+mInv[14]*mInv[6]);

    float z=-(mInv[12]*mInv[8]+mInv[13]*mInv[9]+mInv[14]*mInv[10]);

    //view mat

    float m[16]={

        mInv[0],mInv[4],mInv[8],0,//col 1

        mInv[1],mInv[5],mInv[9],0,//col 2

        mInv[2],mInv[6],mInv[10],0,//col 3

        x,y,z,1//col 4

    };

    Matrix4 viewMat(m);

    return viewMat;

}
//计算绕响亮axis的旋转矩阵
Matrix4 calculateRotationMatrix(const CVector4&axis,float cosA,float sinA){

    //axis must be a unit vector

    //assert(axis.w()==0);

    //assert(getLength2(axis)==1);

    //

    float nx=axis.x();

    float ny=axis.y();

    float nz=axis.z();

    

    float _cosA=1-cosA;

    float nx_cosA=nx*_cosA;

    float nz_cosA=nz*_cosA;

    float nxnx_cosA=nx*nx_cosA;

    float nxny_cosA=ny*nx_cosA;

    float nxnz_cosA=nz*nx_cosA;

    float nyny_cosA=ny*ny*_cosA;

    float nynz_cosA=ny*nz_cosA;

    float nznz_cosA=nz*nz_cosA;

    float nxsinA=nx*sinA;

    float nzsinA=nz*sinA;

    float nysinA=ny*sinA;

    float rotMat[16]={

        nxnx_cosA+cosA,nxny_cosA+nzsinA,nxnz_cosA-nysinA,0,//col 1

        nxny_cosA-nzsinA,nyny_cosA+cosA,nynz_cosA+nxsinA,0,//col 2

        nxnz_cosA+nysinA,nynz_cosA-nxsinA,nznz_cosA+cosA,0,//col 3

        0,0,0,1//col 4

    };

    return Matrix4(rotMat);

}
//计算平移矩阵
Matrix4 calculateTranslateMatrix(const CVector4&translate){

    //assert(translate.w()==0);

    //1 0 0 dx

    //0 1 0 dy

    //0 0 1 dz

    //0 0 0  1

    float dx=translate.x();

    float dy=translate.y();

    float dz=translate.z();

    float TMat[16]={

        1,0,0,0,//col 1

        0,1,0,0,

        0,0,1,0,

        dx,dy,dz,1

    };

    return Matrix4(TMat);

}
//计算缩放矩阵
Matrix4 calculateScaleMatrix(float kx,float ky,float kz){

    //1 0 0 0

    //0 1 0 0

    //0 0 1 0

    //0 0 0 1

    float SMat[16]={

        kx,0,0,0,//col 1

        0,ky,0,0,

        0,0,kz,0,

        0,0,0,1

    };

    return Matrix4(SMat);

}
//几所透射投影矩阵
Matrix4 calculatePerspectiveProjectionMatrix(float fovy,float aspect,float zNear,float zFar)

//if calculation failed, return zero matrix

{

    double sine, cotangent, deltaZ;

    double radians = (fovy/2) * M_PI/180;

    deltaZ = zFar - zNear;

    sine = sinf(radians);

    if ((deltaZ == 0) || (sine == 0) || (aspect == 0)) {

        return zeroMat();

    }

    cotangent = cosf(radians) / sine;

    float m[16]={

        cotangent / aspect,0,0,0,//col 1

        0,cotangent,0,0,//col 2

        0,0,-(zFar + zNear) / deltaZ,-1,//col 3

        0,0, -2 * zNear * zFar / deltaZ,0};//col 4

    return Matrix4(m);

}

Matrix4 calculateOrthoProjectionMatrix(float left,float right,float bottom,float top,float near1,float far1){

	//"near" and "far" have been defined in windows, so we use other var name 

    float tx=-((right+left)/(right-left));

    float ty=-((top+bottom)/(top-bottom));

	float tz=-(far1+near1)/(far1-near1);

    float m[16]={

        2.0/(right-left),0,0,0,//col 1

        0,2.0/(top-bottom),0,0,//col 2

        0,0,(-2.0)/(far1-near1),0,//col 3

        tx,ty,tz,1//col 4

    };

    return Matrix4(m);



}

CVector4 convertFromViewportSpaceToWorldSpace(const CVector4&winPos,

                                                 const Matrix4&projMat,

                                                 const Matrix4&viewMat,

                                                 const float viewport[4]){

    

    float viewportX=viewport[0];

    float viewportY=viewport[1];

    float viewportW=viewport[2];

    float viewportH=viewport[3];

    

    CVector4 t_winPos=winPos;

    // Map x and y from window coordinates

    t_winPos.setx((t_winPos.x()-viewportX)/viewportW);

    t_winPos.sety((t_winPos.y()-viewportY)/viewportH);

    // Map to range -1 to 1

    //?????????????????

    t_winPos.setx(t_winPos.x()*2-1);

    t_winPos.sety(t_winPos.y()*2-1);

    t_winPos.setz(t_winPos.z()*2-1);

    //?????????????????

    Matrix4 projMatInverse=inverse(projMat);

    Matrix4 viewMatInverse=inverse(viewMat);

    CVector4 eyeSpacePos=projMatInverse*t_winPos;

    CVector4 worldPos=viewMatInverse*eyeSpacePos;

//    worldPos.print();

    if (worldPos.w() == 0.0){

        //assert(false);

    }

    //??????

    worldPos.setx(worldPos.x()/worldPos.w());

    worldPos.sety(worldPos.y()/worldPos.w());

    worldPos.setz(worldPos.z()/worldPos.w());

    worldPos.setw(1);

    return worldPos;

}


//计算直线与平面的交点
CVector4 getIntersectPointOfLine3dIntersectWithPlane3d(const CVector4&start,const CVector4&dir,

                                  const CVector4&p,const CVector4&norm)

//dir not need to be normalized

//norm not need to be normalized

{

    //line3d:

    //               x-startx=dirx*t

    //               y-starty=diry*t

    //               z-startz=dirz*t

    //plan3d:

    //              normx*(x-px)+normy*(y-py)+normz*(z-pz)=0

    //solve:

    //              t=-B/A

    //              where A=normx*dirx+normy*diry+normz*dirz

    //                           B=normx*(startx-px)+normy*(starty-py)+normz*(startz-pz)

    float A=norm.x()*dir.x()+norm.y()*dir.y()+norm.z()*dir.z();

    float B=norm.x()*(start.x()-p.x())+norm.y()*(start.y()-p.y())+norm.z()*(start.z()-p.z());

    float t=-B/A;

    float x=dir.x()*t+start.x();

    float y=dir.y()*t+start.y();

    float z=dir.z()*t+start.z();

    return CVector4(x,y,z,1);

}
//判断点是否是直线与面的交点
bool isLine3dIntersectWithTriangle3d(const CVector4&start,const CVector4&dir,

                                     const CVector4&p0,const CVector4&p1,const CVector4&p2){



    CVector4 triNormNE=cross(p1-p0, p2-p1);//normNE is not normalized normal

    CVector4 intersectPointOfLine3dAndTri3d=getIntersectPointOfLine3dIntersectWithPlane3d(start, dir, p0, triNormNE);

    CVector4&p=intersectPointOfLine3dAndTri3d;

    //if p is in triangle p0p1p2

    CVector4 crossP0P1_P0P=cross(p1-p0, p-p0);

    CVector4 crossP1P2_P1P=cross(p2-p1, p-p1);

    CVector4 crossP2P0_P2P=cross(p0-p2, p-p2);

    float dot_crossP0P1_P0P_triNormNE=dot(crossP0P1_P0P, triNormNE);

    float dot_crossP1P2_P1P_triNormNE=dot(crossP1P2_P1P, triNormNE);

    float dot_crossP2P0_P2P_triNormNE=dot(crossP2P0_P2P, triNormNE);

    

    if(dot_crossP0P1_P0P_triNormNE>0&&dot_crossP1P2_P1P_triNormNE>0&&dot_crossP2P0_P2P_triNormNE>0){

        return true;

    }else{

        return false;

    }

}

