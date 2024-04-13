#ifndef _Cvert_H_
#define _Cvert_H_
#include "Vector.h"
class Vertex{
	public:
		CVector4 m_pos;
		CVector2 m_texCoord;
	public:
		Vertex(){
		
		}
		~Vertex(){}
		void init(CVector4 pos,CVector2 texCoord){
			m_pos=pos;
			m_texCoord=texCoord;
		}
		void init(CVector4 pos){
			m_pos=pos;
		}
};

#endif