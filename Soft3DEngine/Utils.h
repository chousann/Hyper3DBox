#ifndef __HelloCpp__Utils__
#define __HelloCpp__Utils__
#include <string>
#include <vector>
#include "Cvert.h"
using namespace std;

vector<int> getThreeValuesDownOrderIndexList(float a,float b,float c);
Vertex linePHighPLowIntersectWithHorizontalLineAcrossPMid(const Vertex&vHigh,const Vertex&vLow,const Vertex&vMid,double camera_n);
Vertex linePHighPLowIntersectWithHorizontalLineAcrossPMid1(const Vertex&vHigh,const Vertex&vLow,const Vertex&vMid,double camera_n);





#endif