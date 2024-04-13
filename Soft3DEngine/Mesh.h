#ifndef __HelloCpp__mesh__

#define __HelloCpp__mesh__



#include <iostream>

#include "Vector.h"

#include "CTriangle.h"
#include "Cvert.h"

class Mesh{

public:
	vector<CVector4> m_positionList;
    //Cc3dVector4 m_positionList[8];
	//vector<int> m_textureIDList;
    vector<CVector2> m_texCoordList;
    //vector<Cc3dVector4> m_normalList;
    vector<CTriangle> m_IDtriList;
	string m_texfilepath;
public:

    Mesh(){};

    virtual~Mesh(){};

	void resizeVerts(int vertexCount);
	void resizeIDtris(int IDtriCount){
		//m_IDtriList.resize(IDtriCount);

	}
	void clearAll(){
		resizeVerts(0);
		resizeIDtris(0);
	}
	Vertex getVert(int vertIndex);
	void setVert(int vertIndex,const Vertex&v);
	void pushBackVert(const Vertex&v);
	/*void initCube(Cc3dObject cube){
		int i;
		for(i=0;i<8;i++){
			m_positionList[i]=cube.vPtr[i];
		}
		for(i=0;i<12;i++){
			m_IDtriList[i]=cube.triPtr[i];
			}
	}*/
};
#endif /* defined(__HelloCpp__mesh__) */