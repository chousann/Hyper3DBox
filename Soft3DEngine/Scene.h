#ifndef __HelloCpp__Scene__

#define __HelloCpp__Scene__
#include "mesh.h"
#include "Camera.h"
#include "Triangle.h"
#include"windows.h"
#include "Utils.h"
#include "readmodel.h"
#include "Object.h"
#include "VideoBuf.h"
class Scene{

public://camera

	Camera*m_camera;
	vector<Object> m_objectList;
	Object player;



	BYTE *pData;
	VideoBuf *videobuf;
	HDC texdc;
	CVector4 light;
	int zhang;
	int mode;
	int vNum;
	int triNum;

public:
	Scene(){
		m_camera=NULL;
	}
	virtual~Scene(){

	}
	void init(){
		//放入相机
		CVector4 eyePos(0,-500,-500,1);
		CVector4 center(0,-500,-400,1);
		CVector4 up(0,1,0,1);
		m_camera=new Camera();
		m_camera->init(eyePos,center,up,960,640);

		zhang=0;
		videobuf = new VideoBuf;
		light.init(100000,-100000,0,1);
		vNum=0;
		triNum=0;
		loadPlayer();
		mode=1;



	}
	void loadObject(Object obj){
		vNum+=obj.m_localmesh->m_positionList.size();
		triNum+=obj.m_localmesh->m_IDtriList.size();
		m_objectList.push_back(obj);
	}
	void loadPlayer(){
		string fileFullPath="..\\resource\\";
		string filename="cube1.txt";
		CVector4 worldPos2(m_camera->getEyePos().x(),m_camera->getEyePos().y()+300,m_camera->getEyePos().z()+600,1);
		Object obj2(fileFullPath,filename,worldPos2,"player");
		Object obj3(fileFullPath,filename,worldPos2,"player");
		player=obj3;
		m_objectList.push_back(obj2);
		for(int m=0;m<m_objectList.size();m++){
			vNum+=m_objectList[m].m_localmesh->m_positionList.size();
			triNum+=m_objectList[m].m_localmesh->m_IDtriList.size();
		}
	}

	void softRasterization(HDC hdc,HBITMAP hbitmap);
	void softRasterization1(HDC hdc,HBITMAP hbitmap);
	void localToWorld();
	void worldtoCamera(Matrix4 mat);
	void localToCamera(Matrix4 mat);
	void deleteback(Matrix4 mat);
	void touyin();
	void rend(HDC hdc);
	void rendsoild(HDC hdc);
	void rendedge(HDC hdc);
	void selectrendmode(HDC hdc,HBITMAP hbitmap);
	void draw(HDC hdc,Vertex cv0,Vertex cv1,Vertex cv2,LPCSTR fileName,double flg,int index);
	void draw2(HDC hdc,Vertex cv0,Vertex cv1,Vertex cv2,LPCSTR fileName,double flg,short index[]);
	void draw3(HDC hdc,Vertex cv0,Vertex cv1,Vertex cv2,short index[]);
	void drawline(HDC hdc,Vertex cv0,Vertex cv1,short index[]);
	/*
		z缓冲：
	*/
	void fillPanTopTriFace(HDC hdc,Vertex vBottom,Vertex vMid,Vertex vTop,LPCSTR fileName,double flg,int index);
	void fillPanBottomTriFace(HDC hdc,Vertex vBottom,Vertex vMid,Vertex vTop,LPCSTR fileName,double flg,int index);
	void dfillPanTopTriFace(HDC hdc,Vertex vBottom,Vertex vMid,Vertex vTop,LPCSTR fileName,double flg,int index);
	void dfillPanBottomTriFace(HDC hdc,Vertex vBottom,Vertex vMid,Vertex vTop,LPCSTR fileName,double flg,int index);

	void PanTopTri(HDC hdc,Vertex vBottom,Vertex vMid,Vertex vTop,LPCSTR fileName,double flg,short index[]);
	void PanBottomTri(HDC hdc,Vertex vBottom,Vertex vMid,Vertex vTop,LPCSTR fileName,double flg,short index[]);
	////////////////////
	/*
		z缓冲：深度插值法
	*/
	void deepfillPanTopTriFace(HDC hdc,Vertex vBottom,Vertex vMid,Vertex vTop,LPCSTR fileName);
	void deepfillPanBottomTriFace(HDC hdc,Vertex vBottom,Vertex vMid,Vertex vTop,LPCSTR fileName);
	void centerjisuan();
	///////////////////////
	void init(CVector4 viewport){	

	}

	/*
		//深度插值与透视纹理映射插值
		参考文档及源码
		https://github.com/wantnon2/gdi3d
		http://www.cnblogs.com/wantnon/p/4894980.html
		http://www.cnblogs.com/wantnon/p/4892284.html
		利用深度插值计算z缓冲深度值
	*/
	float interpolateInTri_inViewportSpace_earlyZ(const Vertex&v0,const Vertex&v1,const Vertex&v2,float x,float y){
		const float x0=v0.m_pos.x();
		const float y0=v0.m_pos.y();
		const float z0=v0.m_pos.z();
		const float x1=v1.m_pos.x();
		const float y1=v1.m_pos.y();
		const float z1=v1.m_pos.z();
		const float x2=v2.m_pos.x();
		const float y2=v2.m_pos.y();
		const float z2=v2.m_pos.z();
			const float y1suby0=y1-y0;
		const float y2suby0=y2-y0;
		const float ysuby0=y-y0;
		const float x1subx0=x1-x0;
		const float x2subx0=x2-x0;
		const float xsubx0=x-x0;
		const float M=y1suby0*x2subx0-x1subx0*y2suby0;
		float A=0;
		float B=0;
		float z=1;
		if(M==0){//  p0p1//p0p2, p0p1p2 is degenerated tri, this may not happen, so no matter return what
			//do nothing
		}else{
			A=-(y2suby0*xsubx0-x2subx0*ysuby0)/M;
			B=(y1suby0*xsubx0-x1subx0*ysuby0)/M;
			//----calculate z
			z=z0+(z1-z0)*A+(z2-z0)*B;

		}
		//CearlyZOutput earlyZOutput;
		//earlyZOutput.m_A=A;
		//earlyZOutput.m_B=B;
		//earlyZOutput.m_x=x;
		//earlyZOutput.m_y=y;
		//earlyZOutput.m_z=z;
		return z;
	}
	/////////////////////////////////////////


};

#endif
