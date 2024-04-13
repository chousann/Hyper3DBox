#include "StdAfx.h"
#include "Utils.h"
vector<int> getThreeValuesDownOrderIndexList(float a,float b,float c){
	vector<int> rs;
	int indexOfA=0;
	int indexOfB=1;
	int indexOfC=2;
	bool ABigThanB=(a>b);
	bool ABigThanC=(a>c);
	bool BBigThanC=(b>c);
	if(ABigThanB!=ABigThanC){//b and c is on the different side of a
		if(BBigThanC){//b>c
			rs.push_back(indexOfB);
			rs.push_back(indexOfA);
			rs.push_back(indexOfC);
		}else{
			rs.push_back(indexOfC);
			rs.push_back(indexOfA);
			rs.push_back(indexOfB);
		}
	}else{//b and c is on the same side of a, namely a is min or max
		if(ABigThanB){//a is max
			if(BBigThanC){//a>b>c
				rs.push_back(indexOfA);
				rs.push_back(indexOfB);
				rs.push_back(indexOfC);
			}else{//a>c>b
				rs.push_back(indexOfA);
				rs.push_back(indexOfC);
				rs.push_back(indexOfB);
			}
		}else{//a is min
			if(BBigThanC){//b>c>a
				rs.push_back(indexOfB);
				rs.push_back(indexOfC);
				rs.push_back(indexOfA);
			}else{//c>b>a
				rs.push_back(indexOfC);
				rs.push_back(indexOfB);
				rs.push_back(indexOfA);
			}

		}
	}
	return rs;
}

Vertex linePHighPLowIntersectWithHorizontalLineAcrossPMid(const Vertex&vHigh,const Vertex&vLow,const Vertex&vMid,double camera_n)
	//return intersect point
{
	//----calculate x,y
	const double n=camera_n;
	const double x1=vHigh.m_pos.x();
	const double y1=vHigh.m_pos.y();
	const double z1=vHigh.m_pos.z();
	const double s1=vHigh.m_texCoord.x();
	const double t1=vHigh.m_texCoord.y();
	const double x2=vLow.m_pos.x();
	const double y2=vLow.m_pos.y();
	const double z2=vLow.m_pos.z();
	const double s2=vLow.m_texCoord.x();
	const double t2=vLow.m_texCoord.y();
	const double x3=vMid.m_pos.x();
	const double y3=vMid.m_pos.y();
	const double z3=vMid.m_pos.z();
	const double s3=vMid.m_texCoord.x();
	const double t3=vMid.m_texCoord.y();
	const double x3d1=x1*z1/n;
	const double y3d1=y1*z1/n;
	const double x3d2=x2*z2/n;
	const double y3d2=y2*z2/n;
	const double x3d3=x3*z3/n;
	const double y3d3=y3*z3/n;
	double x,y,z,s,t;
	if(y1==y2){
		x=x3;
		y=y3;
	}else{
		y=y3;
		x=(y3-y2)*(x1-x2)/(y1-y2)+x2;
		double zInverse=1/z2+(y-y2)*(1/z1-1/z2)/(y1-y2);
		z=1/zInverse;
		double x3d=x*z/n;
		double y3d=y*z/n;
		//if(x3d1==x3d2){
			//if(y3d1==y3d2){
				//if(z1==z2){
					//s=vMid.m_texCoord.x();
					//t=vMid.m_texCoord.y();
				//}else{
					//s=s2+(z-z2)*(s1-s2)/(z1-z2);
					//t=t2+(z-z2)*(t1-t2)/(z1-z2);
				//}
			//}else{
				s=s2+(y3d-y3d2)*(s1-s2)/(y3d1-y3d2);
				t=t2+(y3d-y3d2)*(t1-t2)/(y3d1-y3d2);
			//}
		//}else{
			//s=s2+(x3d-x3d2)*(s1-s2)/(x3d1-x3d2);
			//t=t2+(x3d-x3d2)*(t1-t2)/(x3d1-x3d2);
		//}
	}

	
	//----make v
	Vertex v;
	v.m_pos=CVector4(x,y,z,1);
	v.m_texCoord=CVector2(s,t);

	return v;

}

Vertex linePHighPLowIntersectWithHorizontalLineAcrossPMid1(const Vertex&vHigh,const Vertex&vLow,const Vertex&vMid,double camera_n)
	//return intersect point
{
	//----calculate x,y
	const double n=camera_n;
	const double x1=vHigh.m_pos.x();
	const double y1=vHigh.m_pos.y();
	const double z1=vHigh.m_pos.z();
	//const double s1=vHigh.m_texCoord.x();
	//const double t1=vHigh.m_texCoord.y();
	const double x2=vLow.m_pos.x();
	const double y2=vLow.m_pos.y();
	const double z2=vLow.m_pos.z();
	//const double s2=vLow.m_texCoord.x();
	//const double t2=vLow.m_texCoord.y();
	const double x3=vMid.m_pos.x();
	const double y3=vMid.m_pos.y();
	const double z3=vMid.m_pos.z();
	//const double s3=vMid.m_texCoord.x();
	//const double t3=vMid.m_texCoord.y();
	const double x3d1=x1*z1/n;
	const double y3d1=y1*z1/n;
	const double x3d2=x2*z2/n;
	const double y3d2=y2*z2/n;
	const double x3d3=x3*z3/n;
	const double y3d3=y3*z3/n;
	double x,y,z,s,t;
	if(y1==y2){
		x=x3;
		y=y3;
	}else{
		y=y3;
		x=(y3-y2)*(x1-x2)/(y1-y2)+x2;
		double zInverse=1/z2+(y-y2)*(1/z1-1/z2)/(y1-y2);
		z=1/zInverse;


	}

	
	//----make v
	Vertex v;
	v.m_pos=CVector4(x,y,z,1);
	//v.m_texCoord=Cc3dVector2(s,t);

	return v;

}
/*void soft(){
		Cc3dVector4 list[8];
		for(int k=0;k<8;k++){
		list[k]=mat*vectorList[k];
	}
		for(k=0;k<12;k++){
	  Cc3dVector4 v=cross(list[triList[k].vID(1)]-list[triList[k].vID(0)],list[triList[k].vID(2)]-list[triList[k].vID(0)]);
      Cc3dVector4 v1=list[triList[k].vID(1)];//-camera.getEyePos();
      if(dot(v,v1)<0){
        triList[k].setFlag(1);
	  }else{
	    triList[k].setFlag(0);
	  }

	}
		//Cc3dVector4 tVectorList[8];
		for(int m=0;m<8;m++){
		//tVectorList[m].setx(camera.getzNear()/(list[m].z())*list[m].x());
		//tVectorList[m].sety(camera.getzNear()/(list[m].z())*list[m].y());
	}
/*for(k=0;k<12;k++){
	if(triList[k].getFlag()){
		POINT p[4]={{tVectorList[triList[k].vID(0)].x()+400,tVectorList[triList[k].vID(0)].y()+200},
					{tVectorList[triList[k].vID(1)].x()+400,tVectorList[triList[k].vID(1)].y()+200},
					{tVectorList[triList[k].vID(2)].x()+400,tVectorList[triList[k].vID(2)].y()+200},
					{tVectorList[triList[k].vID(0)].x()+400,tVectorList[triList[k].vID(0)].y()+200}};
		Cc3dVector4 v=cross(tVectorList[triList[k].vID(1)]-tVectorList[triList[k].vID(0)],tVectorList[triList[k].vID(2)]-tVectorList[triList[k].vID(0)]);
		pDC->Polygon(p,4);
	}
}*/
//}*/
