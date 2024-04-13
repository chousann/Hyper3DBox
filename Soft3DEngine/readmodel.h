#ifndef _readmodel_H_
#define _readmodel_H_
#include "Vector.h"
#include <iostream> 
#include <fstream>
#include <sstream>
class Model{
	public:
		string fileFullPath;
		ifstream ifs;
	public:
		Model(){
		
		}
		Model(string file){
			fileFullPath=file;
			ifs.open(fileFullPath.c_str()); 
		}
		~Model(){}
	void maheCube(Mesh *m_mesh){
		float l=100;
		CVector4 v[8];
		v[0].init(-l/2,-l/2,-l/2,1);
		v[1].init( l/2,-l/2,-l/2,1);
		v[2].init( l/2,-l/2, l/2,1);
		v[3].init(-l/2,-l/2, l/2,1);
		v[4].init(-l/2, l/2,-l/2,1);
		v[5].init( l/2, l/2,-l/2,1);
		v[6].init( l/2, l/2, l/2,1);
		v[7].init(-l/2, l/2, l/2,1);
		for(int i=0;i<8;i++){
			m_mesh->m_positionList[i]=v[i];
		}
		CTriangle triList[12];
		CVector2 texCoordList[36];
		triList[0].init(0,4,5);
		texCoordList[0].init(0,0);
		texCoordList[1].init(0,1);
		texCoordList[2].init(1,1);
		triList[1].init(0,5,1);
		texCoordList[3].init(0,0);
		texCoordList[4].init(1,1);
		texCoordList[5].init(1,0);
		triList[2].init(1,5,6);
		texCoordList[6].init(0,0);
		texCoordList[7].init(0,1);
		texCoordList[8].init(1,1);
		triList[3].init(1,6,2);
		texCoordList[9].init(0,0);
		texCoordList[10].init(1,1);
		texCoordList[11].init(1,0);
		triList[4].init(2,6,7);
		texCoordList[12].init(0,0);
		texCoordList[13].init(0,1);
		texCoordList[14].init(1,1);
		triList[5].init(2,7,3);
		texCoordList[15].init(0,0);
		texCoordList[16].init(1,1);
		texCoordList[17].init(1,0);
		triList[6].init(3,7,4);
		texCoordList[18].init(0,0);
		texCoordList[19].init(0,1);
		texCoordList[20].init(1,1);
		triList[7].init(3,4,0);
		texCoordList[21].init(0,0);
		texCoordList[22].init(1,1);
		texCoordList[23].init(1,0);
		triList[8].init(0,1,2);
		texCoordList[24].init(0,1);
		texCoordList[25].init(1,1);
		texCoordList[26].init(1,0);
		triList[9].init(0,2,3);
		texCoordList[27].init(0,1);
		texCoordList[28].init(1,0);
		texCoordList[29].init(0,0);
		triList[10].init(4,7,6);
		texCoordList[30].init(0,0);
		texCoordList[31].init(0,1);
		texCoordList[32].init(1,1);
		triList[11].init(4,6,5);
		texCoordList[33].init(0,0);
		texCoordList[34].init(1,1);
		texCoordList[35].init(1,0);
		for(i=0;i<12;i++){
			m_mesh->m_IDtriList[i]=triList[i];
			m_mesh->m_texCoordList[3*i]=texCoordList[3*i];
			m_mesh->m_texCoordList[3*i+1]=texCoordList[3*i+1];
			m_mesh->m_texCoordList[3*i+2]=texCoordList[3*i+2];
		}
	}



void loadModelFromZdy(Mesh *m_mesh){
	string str; 
	while(getline(ifs,str)){
		istringstream iss(str);
		string head;
		iss>>head;
		if(head=="texfilepath"){
			string path;
			iss>>path;
			m_mesh->m_texfilepath=path;
		}
		if(head=="vetex"){
			float a,b,c;
			iss>>a>>b>>c;
			CVector4 v;
			v.init(a,b,c,1);
			m_mesh->m_positionList.push_back(v);
		}
		if(head=="IDtri"){
			int format;
			int a,b,c;
			CTriangle triList;
			iss>>format>>a>>b>>c;
			triList.init(a,b,c);
			triList.format=format;
			if(format==2){
				getline(ifs,str);
				istringstream iss1(str);
				iss1>>head;
				if(head=="texCoord"){
					int size=255;
					float x,y,z,d,e,f;
					iss1>>x>>y>>z>>d>>e>>f;
					CVector2 texCoordList[3];
					texCoordList[0].init(x*size,y*size);
					texCoordList[1].init(z*size,d*size);
					texCoordList[2].init(e*size,f*size);
					m_mesh->m_IDtriList.push_back(triList);
					m_mesh->m_texCoordList.push_back(texCoordList[0]);
					m_mesh->m_texCoordList.push_back(texCoordList[1]);
					m_mesh->m_texCoordList.push_back(texCoordList[2]);
				}
			} else if(format==1){
				getline(ifs,str);
				istringstream iss1(str);
				iss1>>head;
				if(head=="color"){
					short x,y,z;
					int size=1;
					iss1>>x>>y>>z;
					triList.m_color[0]=x;
					triList.m_color[1]=y;
					triList.m_color[2]=z;
				}
				m_mesh->m_IDtriList.push_back(triList);
			}
		}
	}
}
void loadModelFromObj(Mesh *m_mesh){
	vector<CVector4> positionList;
	vector<CVector2> texCoordList;
	string str; 
	while(getline(ifs,str)){
		istringstream iss(str);
		string head;
		iss>>head;
		if(head=="v"){
			float a,b,c;
			iss>>a>>b>>c;
			CVector4 v;
			v.init(a,b,c,1);
			m_mesh->m_positionList.push_back(v);
		}
		if(head=="vt"){
			float a,b;
			iss>>a>>b;
			CVector2 v;
			v.init(a,b);
			texCoordList.push_back(v);
		}
		if(head=="f"){
			string v; 
			int a[4],i;
			for(i=0;iss>>v;i++){
				for(int k=v.size()-1;k>=0;k--){
					if(v[k]=='/')v[k]=' ';
				}
				istringstream iss1(v);
				iss1>>a[i];
			}
			if(i==3){
				CTriangle triList;
				triList.init(a[0]-1,a[1]-1,a[2]-1);
				triList.format=5;
				m_mesh->m_IDtriList.push_back(triList);
			}else if(i==4){
				CTriangle triList,triList1;
				triList.init(a[0]-1,a[1]-1,a[2]-1);
				triList1.init(a[2]-1,a[3]-1,a[0]-1);
				triList.format=5;
				triList1.format=5;
				m_mesh->m_IDtriList.push_back(triList);
				m_mesh->m_IDtriList.push_back(triList1);
			}
		}
	}
}


};

#endif