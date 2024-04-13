#ifndef __HelloCpp__Object__
#define __HelloCpp__Object__

#include <iostream>

#include "Vector.h"
#include "mesh.h"
#include "CTriangle.h"
#include "Cvert.h"

class Object{
	public:
		string name;
		Mesh* m_localmesh;
		BITMAP m_texbitmap;
		
		CVector4 worldPos;
		CVector4 rotate;
		float turning;
		Mesh* m_transformedmesh;

	public:
		Object(){
		};
		Object(string fileFullPath,string filename,CVector4 pos,string n,string style="txt"){
			name=n;
			worldPos.init(pos.x(),pos.y(),pos.z(),1);
			rotate.init(0,0,0,1);
			turning=0;
			m_localmesh = new Mesh();
			m_transformedmesh = new Mesh();
			Model m(fileFullPath+filename);
			if(style=="txt"){
			m.loadModelFromZdy(m_localmesh);
			fileFullPath+=m_localmesh->m_texfilepath;
			LPCSTR str=LPCSTR((fileFullPath.c_str()));
			//装载位图
			HBITMAP hbitmap=(HBITMAP)LoadImage(NULL,str,IMAGE_BITMAP,0,0,LR_LOADFROMFILE|LR_CREATEDIBSECTION);
			if(GetObject(hbitmap,sizeof(BITMAP),&m_texbitmap)==0)
				MessageBox(NULL, LPCSTR("heoo"),0,0);
			}else if(style=="obj"){
			m.loadModelFromObj(m_localmesh);
			}else{
				string str=fileFullPath+":不能识别的类型";
				MessageBox(NULL, LPCSTR(str.c_str()),0,0);
			}
			m_localmesh->m_positionList.size();
		};
		void setPos(CVector4 pos){
			worldPos.init(pos.x(),pos.y(),pos.z(),1);
		}
		virtual~Object(){};
};
#endif /* defined(__HelloCpp__mesh__) */