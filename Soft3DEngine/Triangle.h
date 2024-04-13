#ifndef _Triangle_H_
#define _Triangle_H_
#include "Vector.h"
#include "Cvert.h"
class Triangle{
public:
	Triangle(){}
	~Triangle(){}
public:
	Vertex m_v0;
	Vertex m_v1;
	Vertex m_v2;
};
#endif