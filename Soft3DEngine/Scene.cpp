#include "StdAfx.h"
#include "Scene.h"
#include "Matrix.h"
void Scene::centerjisuan(){
		float ddd=m_camera->ydir/180*3.1415926;
		Matrix4 mat;
		mat.initRoMatriY(ddd);
		for(int k=0;k<player.m_localmesh->m_positionList.size();k++){
			m_objectList[0].m_localmesh->m_positionList[k]=mat*player.m_localmesh->m_positionList[k];
		}
		float sinv=sin(ddd),cosv=cos(ddd);
		CVector4 center(m_camera->getEyePos().x()+100*sinv,m_camera->getEyePos().y(),m_camera->getEyePos().z()+100*cosv,m_camera->getEyePos().w());
		m_camera->setCenter(center);
		m_objectList[0].worldPos.init(m_camera->getEyePos().x()+600*sinv,m_camera->getEyePos().y()+300,m_camera->getEyePos().z()+600*cosv,m_camera->getEyePos().w());
}
void Scene::localToWorld(){
	float rotate;
	Matrix4 mat;
	for(int i=0;i<m_objectList.size();i++){
		rotate=(m_objectList[i].rotate.y()+m_objectList[i].turning)/180*3.1415926;
		mat.initRoMatriY(rotate);
		*(m_objectList[i].m_transformedmesh)=*(m_objectList[i].m_localmesh);
		for(int j=0;j<m_objectList[i].m_transformedmesh->m_positionList.size();j++){
			if(rotate!=0){
				m_objectList[i].m_transformedmesh->m_positionList[j]=mat*m_objectList[i].m_transformedmesh->m_positionList[j];
			}
			m_objectList[i].m_transformedmesh->m_positionList[j].init(m_objectList[i].m_transformedmesh->m_positionList[j].x()+m_objectList[i].worldPos.x(),m_objectList[i].m_transformedmesh->m_positionList[j].y()+m_objectList[i].worldPos.y(),m_objectList[i].m_transformedmesh->m_positionList[j].z()+m_objectList[i].worldPos.z(),1);
		}
	}
}
void Scene::worldtoCamera(Matrix4 mat){
	for(int i=0;i<m_objectList.size();i++){
		
		for(int j=0;j<m_objectList[i].m_transformedmesh->m_positionList.size();j++){
			m_objectList[i].m_transformedmesh->m_positionList[j]=mat*m_objectList[i].m_transformedmesh->m_positionList[j];
		}
	}

}
void Scene::localToCamera(Matrix4 mat){
	float rotate,ratatex;
	Matrix4 mat1,mat2,mat3,matx;
	for(int i=0;i<m_objectList.size();i++){
		rotate=m_objectList[i].rotate.y()/180*3.1415926;
		ratatex=m_objectList[i].rotate.x()/180*3.1415926;
		mat1.initRoMatriY(rotate);
		matx.initRoMatriX(ratatex);
		CVector4 ve(m_objectList[i].worldPos.x(),m_objectList[i].worldPos.y(),m_objectList[i].worldPos.z(),1);
		mat2=calculateTranslateMatrix(ve);
		if(rotate!=0){
			mat3=mat*(mat2*(mat1*matx));
		} else {
			mat3=mat*(mat2*matx);
		}
		*(m_objectList[i].m_transformedmesh)=*(m_objectList[i].m_localmesh);
		for(int j=0;j<m_objectList[i].m_transformedmesh->m_positionList.size();j++){
				m_objectList[i].m_transformedmesh->m_positionList[j]=(mat3*m_objectList[i].m_transformedmesh->m_positionList[j]);	
		}
	}
}
void Scene::deleteback(Matrix4 mat){
	CVector4 light1=mat*light;
	for(int i=0;i<m_objectList.size();i++){
		Mesh *m_mesh;
		m_mesh=m_objectList[i].m_transformedmesh;
		for(int k=0;k<m_mesh->m_IDtriList.size();k++){
			CVector4 v;
			CVector4 v1;
			CVector4 v2;

			v=cross(m_mesh->m_positionList[m_mesh->m_IDtriList[k].vID(1)]-m_mesh->m_positionList[m_mesh->m_IDtriList[k].vID(0)],m_mesh->m_positionList[m_mesh->m_IDtriList[k].vID(2)]-m_mesh->m_positionList[m_mesh->m_IDtriList[k].vID(0)]);
			v1=m_mesh->m_positionList[m_mesh->m_IDtriList[k].vID(1)];//-camera.getEyePos();
			v2=m_mesh->m_positionList[m_mesh->m_IDtriList[k].vID(1)]-light1;
			double lighucos;
			if(dot(v,v1)<0){
				m_mesh->m_IDtriList[k].setFlag(1);
				lighucos=dot(v,v2);
			if(lighucos<0){
				m_mesh->m_IDtriList[k].lightflg=-lighucos/sqrtf(v.x()*v.x()+v.y()*v.y()+v.z()*v.z())/sqrtf(v2.x()*v2.x()+v2.y()*v2.y()+v2.z()*v2.z())+0.2;
			}else{
				m_mesh->m_IDtriList[k].lightflg=0.2;
			}
			}else{
				m_mesh->m_IDtriList[k].setFlag(0);
			}
		}

	}
}
//透视投影
void Scene::touyin(){
	CVector4 df;
	for(int i=0;i<m_objectList.size();i++){
		Mesh *m_mesh;
		m_mesh=m_objectList[i].m_transformedmesh;
		for(int m=0;m<m_mesh->m_positionList.size();m++){
			//if(m_mesh->m_positionList[m].z()>500){
			df.setx(m_camera->getzNear()/(m_mesh->m_positionList[m].z())*m_mesh->m_positionList[m].x()*6+600);
			df.sety(m_camera->getzNear()/(m_mesh->m_positionList[m].z())*m_mesh->m_positionList[m].y()*6-800);
			df.setz(m_mesh->m_positionList[m].z());
			m_mesh->m_positionList[m]=df;
			//}else{
			//df.setx(m_mesh->m_positionList[m].x());
			//df.sety(m_mesh->m_positionList[m].y());
			//df.setz(500);
			//m_mesh->m_positionList[m]=df;
			//}
		//tVectorList[m].setx(m_camera->getzNear()/(list[m].z())*list[m].x());
		//tVectorList[m].sety(m_camera->getzNear()/(list[m].z())*list[m].y());
		//tVectorList[m].setz(list[m].z());
		}
	}
}
void Scene::rend(HDC hdc){
		Vertex v0;
		Vertex v1;
		Vertex v2;
		Vertex v3;
		for(int j=0;j<m_objectList.size();j++){
			Mesh *m_mesh;
			m_mesh=m_objectList[j].m_transformedmesh;
			//清成黑色
			//memset(bmbuf,0,nLnBytes*abs(bmpInfo.bmiHeader.biHeight));
			for(int i=0;i<m_mesh->m_IDtriList.size();i++){
				if(m_mesh->m_IDtriList[i].format==2){
				if(m_mesh->m_IDtriList[i].getFlag()){
					v0.init(m_mesh->m_positionList[m_mesh->m_IDtriList[i].m_array[0]],m_mesh->m_texCoordList[i*3]);
					v1.init(m_mesh->m_positionList[m_mesh->m_IDtriList[i].m_array[1]],m_mesh->m_texCoordList[i*3+1]);
					v2.init(m_mesh->m_positionList[m_mesh->m_IDtriList[i].m_array[2]],m_mesh->m_texCoordList[i*3+2]);
					draw(hdc,v0,v1,v2,"C:\\Users\\mrzhang\\Desktop\\文件\\编程\\自己的代码\\格斗\\res\\qi.bmp",m_mesh->m_IDtriList[i].lightflg,j);
				}
				}else if(m_mesh->m_IDtriList[i].format==1){
					if(m_mesh->m_IDtriList[i].getFlag()){
						v0.init(m_mesh->m_positionList[m_mesh->m_IDtriList[i].m_array[0]]);
						v1.init(m_mesh->m_positionList[m_mesh->m_IDtriList[i].m_array[1]]);
						v2.init(m_mesh->m_positionList[m_mesh->m_IDtriList[i].m_array[2]]);
						draw2(hdc,v0,v1,v2,"C:\\Users\\mrzhang\\Desktop\\文件\\编程\\自己的代码\\格斗\\res\\qi.bmp",m_mesh->m_IDtriList[i].lightflg,m_mesh->m_IDtriList[i].m_color);
					}
				}else if(m_mesh->m_IDtriList[i].format==5)
				{
					short m_color[3]={125,125,125};
					if(m_mesh->m_IDtriList[i].getFlag()){
						v0.init(m_mesh->m_positionList[m_mesh->m_IDtriList[i].m_array[0]]);
						v1.init(m_mesh->m_positionList[m_mesh->m_IDtriList[i].m_array[1]]);
						v2.init(m_mesh->m_positionList[m_mesh->m_IDtriList[i].m_array[2]]);
						draw2(hdc,v0,v1,v2,"C:\\Users\\mrzhang\\Desktop\\文件\\编程\\自己的代码\\格斗\\res\\qi.bmp",m_mesh->m_IDtriList[i].lightflg,m_color);
					}
				}
			}
		}
}
void Scene::rendsoild(HDC hdc){
		Vertex v0;
		Vertex v1;
		Vertex v2;
		Vertex v3;
		for(int j=0;j<m_objectList.size();j++){
			short m_color[3]={125,125,125};
			Mesh *m_mesh;
			m_mesh=m_objectList[j].m_transformedmesh;
			//清成黑色
			//memset(bmbuf,0,nLnBytes*abs(bmpInfo.bmiHeader.biHeight));
			for(int i=0;i<m_mesh->m_IDtriList.size();i++){
					if(m_mesh->m_IDtriList[i].getFlag()){
						v0.init(m_mesh->m_positionList[m_mesh->m_IDtriList[i].m_array[0]]);
						v1.init(m_mesh->m_positionList[m_mesh->m_IDtriList[i].m_array[1]]);
						v2.init(m_mesh->m_positionList[m_mesh->m_IDtriList[i].m_array[2]]);
						draw2(hdc,v0,v1,v2,"C:\\Users\\mrzhang\\Desktop\\文件\\编程\\自己的代码\\格斗\\res\\qi.bmp",m_mesh->m_IDtriList[i].lightflg,m_color);
					}
			}
		}
}
void Scene::draw3(HDC hdc,Vertex cv0,Vertex cv1,Vertex cv2,short index[]){
	drawline(hdc,cv0,cv1,index);
	drawline(hdc,cv1,cv2,index);
	drawline(hdc,cv2,cv0,index);
}
void Scene::drawline(HDC hdc,Vertex v0,Vertex v1,short index[]){
	float w=v1.m_pos.x()-v0.m_pos.x(),h=v1.m_pos.y()-v0.m_pos.y();
	float hw;
	float xstart,xend,ystart;
	if(w>0){
		xstart=v0.m_pos.x();
		xend=v1.m_pos.x();
		ystart=v0.m_pos.y();
		hw=h/w;
	} else {
		xstart=v1.m_pos.x();
		xend=v0.m_pos.x();
		ystart=v1.m_pos.y();
		hw=h/w;
	}
	if(xstart<0){
		ystart+=hw*(0-xstart);
		xstart=0;
	}
	if(xend>1360){
		xend=1360;
	}
	int y=ystart;

	for(int x=xstart;x<=xend;x++){
		if(y>=0&&y<=768){
			videobuf->drawPixl(x,y,index,0.8);
		}
		ystart+=hw;
	}


}
void Scene::rendedge(HDC hdc){
		Vertex v0;
		Vertex v1;
		Vertex v2;
		Vertex v3;
		for(int j=0;j<m_objectList.size();j++){
			short m_color[3]={0,0,0};
			Mesh *m_mesh;
			m_mesh=m_objectList[j].m_transformedmesh;
			//清成黑色
			//memset(bmbuf,0,nLnBytes*abs(bmpInfo.bmiHeader.biHeight));
			for(int i=0;i<m_mesh->m_IDtriList.size();i++){
				//if(m_mesh->m_IDtriList[i].getFlag()){
					
					v0.init(m_mesh->m_positionList[m_mesh->m_IDtriList[i].m_array[0]]);
					v1.init(m_mesh->m_positionList[m_mesh->m_IDtriList[i].m_array[1]]);
					v2.init(m_mesh->m_positionList[m_mesh->m_IDtriList[i].m_array[2]]);
					POINT p[4]={{v0.m_pos.x(),v0.m_pos.y()},
					{v1.m_pos.x(),v1.m_pos.y()},
					{v2.m_pos.x(),v2.m_pos.y()},
					{v0.m_pos.x(),v0.m_pos.y()}};
					Polyline(hdc,p,4);		
				//}
			}
		}
}
void Scene::selectrendmode(HDC hdc,HBITMAP hbitmap){
	switch(mode){
		case 1:
			rend(hdc);
			SetDIBits(hdc, hbitmap, 0, abs(videobuf->bmpInfo.bmiHeader.biHeight), videobuf->bmbuf, &videobuf->bmpInfo, DIB_RGB_COLORS);
			break;
		case 2:
			rendsoild(hdc);
			SetDIBits(hdc, hbitmap, 0, abs(videobuf->bmpInfo.bmiHeader.biHeight), videobuf->bmbuf, &videobuf->bmpInfo, DIB_RGB_COLORS);
			break;
		case 3:
			rendedge(hdc);
			break;
		default:
			break;
	}
}
void Scene::softRasterization1(HDC hdc,HBITMAP hbitmap){
	centerjisuan();
	//清成黑色
	memset(videobuf->bmbuf,0,videobuf->nLnBytes*abs(videobuf->bmpInfo.bmiHeader.biHeight));
	zhang++;
	Matrix4 mat=m_camera->calculateViewMat();
	int localtocamera=0;
	if(localtocamera){
		localToWorld();
		worldtoCamera(mat);
	} else {
		localToCamera(mat);
	}
	deleteback(mat);
	touyin();
	//videobuf->drawRectangle(0,0,1359,320,125,125,255);
	//videobuf->drawRectangle(0,320,1359,767,125,255,125);
	selectrendmode(hdc,hbitmap);

}

void Scene::draw(HDC hdc,Vertex cv0,Vertex cv1,Vertex cv2,LPCSTR fileName,double flg,int index){
	vector<Vertex> vlist;
	vlist.push_back(cv0);
	vlist.push_back(cv1);
	vlist.push_back(cv2);

	vector<int> downOrderIndexList=getThreeValuesDownOrderIndexList(cv0.m_pos.y(),cv1.m_pos.y(),cv2.m_pos.y());
	const CVector4&vBottom=vlist[downOrderIndexList[0]].m_pos;
	const CVector4&vMid=vlist[downOrderIndexList[1]].m_pos;
	const CVector4&vTop=vlist[downOrderIndexList[2]].m_pos;
	const bool triIsPanBottom=(vBottom.y()==vMid.y());
	const bool triIsPanTop=(vMid.y()==vTop.y());
	if(triIsPanTop&&triIsPanBottom){//degenerated tri, actually a horizontal line
		//ignore it
	
	}else if(!triIsPanTop&&triIsPanBottom){//only pan bottom
		if(vBottom.x()==vMid.x()){
			//degenerated tri, actually a line
			//ignore it
		}else if(vBottom.x()<vMid.x()){
			//panBottomTri(vHigh,vLow,vMid)
			dfillPanBottomTriFace(hdc,vlist[downOrderIndexList[0]],vlist[downOrderIndexList[1]],vlist[downOrderIndexList[2]],fileName,flg,index);
		}else{
			//panBottomTri(vHigh,vMid,vLow)
			//fillPanBottomTriFace_solid(hdc,vHigh,vMid,vLow);
			dfillPanBottomTriFace(hdc,vlist[downOrderIndexList[1]],vlist[downOrderIndexList[0]],vlist[downOrderIndexList[2]],fileName,flg,index);
		}


	}else if(triIsPanTop&&!triIsPanBottom){//only pan top
		if(vTop.x()==vMid.x()){
			//degenerated tri, actually a line
			//ignore it
		}else if(vTop.x()<vMid.x()){
			//panTopTri(vHigh,vLow,vMid)

			dfillPanTopTriFace(hdc,vlist[downOrderIndexList[0]],vlist[downOrderIndexList[1]],vlist[downOrderIndexList[2]],fileName,flg,index);
		}else{
			//panTopTri(vMid,vLow,vHigh)
			//fillPanTopTriFace_solid(hdc,vMid,vLow,vHigh);

			dfillPanTopTriFace(hdc,vlist[downOrderIndexList[0]],vlist[downOrderIndexList[2]],vlist[downOrderIndexList[1]],fileName,flg,index);
		}

	}else if(!triIsPanTop&&!triIsPanBottom){//not pan bottom and not pan top
		//a horizontal line across vMid intersect with line=(vHigh,vLow) in point v

			Vertex v1=vlist[downOrderIndexList[1]];

		Vertex v=linePHighPLowIntersectWithHorizontalLineAcrossPMid(vlist[downOrderIndexList[0]],vlist[downOrderIndexList[2]],vlist[downOrderIndexList[1]],1000);
			
		if(v.m_pos.x()==v1.m_pos.x()){
			//triangle is actually a nonHorizon line
			//ignore this degenerated tri
		}else if(v.m_pos.x()<v1.m_pos.x()){
			//panBottomTri(vHigh,v,vMid) and panTopTri(v,vLow,vMid)
			dfillPanBottomTriFace(hdc,v,vlist[downOrderIndexList[1]],vlist[downOrderIndexList[2]],fileName,flg,index);
 			dfillPanTopTriFace(hdc,vlist[downOrderIndexList[0]],vlist[downOrderIndexList[1]],v,fileName,flg,index);
		}else{
			//panBottomTri(vHigh,vMid,v) and panTopTri(vMid,vLow,v)
		    dfillPanBottomTriFace(hdc,vlist[downOrderIndexList[1]],v,vlist[downOrderIndexList[2]],fileName,flg,index);
			dfillPanTopTriFace(hdc,vlist[downOrderIndexList[0]],v,vlist[downOrderIndexList[1]],fileName,flg,index);
	
		}
	}else{//impossible to reach this branch
		//assert(false);
	}




}


void Scene::draw2(HDC hdc,Vertex cv0,Vertex cv1,Vertex cv2,LPCSTR fileName,double flg,short index[]){
	vector<Vertex> vlist;
	vlist.push_back(cv0);
	vlist.push_back(cv1);
	vlist.push_back(cv2);

	vector<int> downOrderIndexList=getThreeValuesDownOrderIndexList(cv0.m_pos.y(),cv1.m_pos.y(),cv2.m_pos.y());
	const CVector4&vBottom=vlist[downOrderIndexList[0]].m_pos;
	const CVector4&vMid=vlist[downOrderIndexList[1]].m_pos;
	const CVector4&vTop=vlist[downOrderIndexList[2]].m_pos;
	const bool triIsPanBottom=(vBottom.y()==vMid.y());
	const bool triIsPanTop=(vMid.y()==vTop.y());
	if(triIsPanTop&&triIsPanBottom){//degenerated tri, actually a horizontal line
		//ignore it
	
	}else if(!triIsPanTop&&triIsPanBottom){//only pan bottom
		if(vBottom.x()==vMid.x()){
			//degenerated tri, actually a line
			//ignore it
		}else if(vBottom.x()<vMid.x()){
			//panBottomTri(vHigh,vLow,vMid)
			PanBottomTri(hdc,vlist[downOrderIndexList[0]],vlist[downOrderIndexList[1]],vlist[downOrderIndexList[2]],fileName,flg,index);
		}else{
			//panBottomTri(vHigh,vMid,vLow)
			//fillPanBottomTriFace_solid(hdc,vHigh,vMid,vLow);
			PanBottomTri(hdc,vlist[downOrderIndexList[1]],vlist[downOrderIndexList[0]],vlist[downOrderIndexList[2]],fileName,flg,index);
		}


	}else if(triIsPanTop&&!triIsPanBottom){//only pan top
		if(vTop.x()==vMid.x()){
			//degenerated tri, actually a line
			//ignore it
		}else if(vTop.x()<vMid.x()){
			//panTopTri(vHigh,vLow,vMid)

			PanTopTri(hdc,vlist[downOrderIndexList[0]],vlist[downOrderIndexList[1]],vlist[downOrderIndexList[2]],fileName,flg,index);
		}else{
			//panTopTri(vMid,vLow,vHigh)
			//fillPanTopTriFace_solid(hdc,vMid,vLow,vHigh);

			PanTopTri(hdc,vlist[downOrderIndexList[0]],vlist[downOrderIndexList[2]],vlist[downOrderIndexList[1]],fileName,flg,index);
		}

	}else if(!triIsPanTop&&!triIsPanBottom){//not pan bottom and not pan top
		//a horizontal line across vMid intersect with line=(vHigh,vLow) in point v

			Vertex v1=vlist[downOrderIndexList[1]];

		Vertex v=linePHighPLowIntersectWithHorizontalLineAcrossPMid1(vlist[downOrderIndexList[0]],vlist[downOrderIndexList[2]],vlist[downOrderIndexList[1]],1000);
			
		if(v.m_pos.x()==v1.m_pos.x()){
			//triangle is actually a nonHorizon line
			//ignore this degenerated tri
		}else if(v.m_pos.x()<v1.m_pos.x()){
			//panBottomTri(vHigh,v,vMid) and panTopTri(v,vLow,vMid)
			PanBottomTri(hdc,v,vlist[downOrderIndexList[1]],vlist[downOrderIndexList[2]],fileName,flg,index);
 			PanTopTri(hdc,vlist[downOrderIndexList[0]],vlist[downOrderIndexList[1]],v,fileName,flg,index);
		}else{
			//panBottomTri(vHigh,vMid,v) and panTopTri(vMid,vLow,v)
		    PanBottomTri(hdc,vlist[downOrderIndexList[1]],v,vlist[downOrderIndexList[2]],fileName,flg,index);
			PanTopTri(hdc,vlist[downOrderIndexList[0]],v,vlist[downOrderIndexList[1]],fileName,flg,index);
	
		}
	}else{//impossible to reach this branch
		//assert(false);
	}




}
void Scene::dfillPanTopTriFace(HDC hdc,Vertex vBottom,Vertex vMid,Vertex vTop,LPCSTR fileName,double flg,int index){

	CVector4 v0=vBottom.m_pos;
	CVector4 v1=vMid.m_pos;
	CVector4 v2=vTop.m_pos;
	BYTE *tex=(BYTE *)m_objectList[index].m_texbitmap.bmBits;

	//裁剪测试
	if(v0.y()<0||v2.y()>=768||(v1.x()<0&&v0.x()<0)||(v2.x()>=1360&&v0.x()>=1360)){
		return;
	}



	float zInverseLeft,zInverseRight,zInverseStep;
	//一条扫描线的左端和右端：xleft,xright
	//扫描线 y
	//扫描线上的烧苗点 x
	float xleft,xright;

	float x0  = vBottom.m_pos.x();
	float y0  = vBottom.m_pos.y();
	float tu0 = vBottom.m_texCoord.x() / vBottom.m_pos.z();

	float tv0 = vBottom.m_texCoord.y() / vBottom.m_pos.z();

	float x1  = vMid.m_pos.x();
	float y1  = vMid.m_pos.y();
	float tu1 = vMid.m_texCoord.x() / vMid.m_pos.z();
	float tv1 = vMid.m_texCoord.y() / vMid.m_pos.z();

	float x2  = vTop.m_pos.x();
	float y2  = vTop.m_pos.y();
	float tu2 = vTop.m_texCoord.x() / vTop.m_pos.z();
	float tv2 = vTop.m_texCoord.y() / vTop.m_pos.z();


	//一条扫描线的左端和右端
	float zleft,zrighr;
	//纹理坐标s和t
	float s, t,sleft,sright,tleft,tright; 


	float A,B,C,D;
	A=(v2.x()-v0.x())/(v2.y()-v0.y());
	B=(v1.x()-v0.x())/(v1.y()-v0.y());
	C=(1/v2.z()-1/v0.z())/(v2.y()-v0.y());
	D=(1/v1.z()-1/v0.z())/(v1.y()-v0.y());
	float At,Bt,Ct,Dt;
	At=(tu0-tu2)/(vBottom.m_pos.y()-vTop.m_pos.y());
	Bt=(tu0-tu1)/(vBottom.m_pos.y()-vMid.m_pos.y());
	Ct=(tv0-tv2)/(vBottom.m_pos.y()-vTop.m_pos.y());
	Dt=(tv0-tv1)/(vBottom.m_pos.y()-vMid.m_pos.y());

	//求扫描线==y时，扫描线的右端和左端
	xleft=v2.x();
	xright=v1.x();
	//求扫描线==y时，扫描线的右端和左端在相机空间的深度值z的倒数
	zInverseLeft=1/v2.z();
	zInverseRight=1/v1.z();

	//求扫描线==y时，纹理的左端和右端
	sleft=tu2;
	sright=tu1;
	tleft=tv2;
	tright=tv1;

	int yT,yB;
	//Y屏幕裁剪
	if(v2.y()+0.5<0){
		yT=0;
		//求扫描线==y时，扫描线的右端和左端
		xleft+=A*(yT-v2.y());
		xright+=B*(yT-v2.y());
		//求扫描线==y时，扫描线的右端和左端在相机空间的深度值z的倒数
		zInverseLeft+=C*(yT-v2.y());
		zInverseRight+=D*(yT-v2.y());


		//求扫描线==y时，纹理的左端和右端
		sleft+=At*(yT-v2.y());
		sright+=Bt*(yT-v2.y());
		tleft+=Ct*(yT-v2.y());
		tright+=Dt*(yT-v2.y());
	} else {
		yT=int(v2.y()+0.5);
		if(yT<v2.y()){
			yT=yT+1;
		}
		//求扫描线==y时，扫描线的右端和左端
		xleft+=A*(yT-v2.y());
		xright+=B*(yT-v2.y());
		//求扫描线==y时，扫描线的右端和左端在相机空间的深度值z的倒数
		zInverseLeft+=C*(yT-v2.y());
		zInverseRight+=D*(yT-v2.y());


		//求扫描线==y时，纹理的左端和右端
		sleft+=At*(yT-v2.y());
		sright+=Bt*(yT-v2.y());
		tleft+=Ct*(yT-v2.y());
		tright+=Dt*(yT-v2.y());
	}
	if(v0.y()+0.5<768){
		yB=int(v0.y()+0.5);
	} else {
		yB=767;
	}
	int y;
	for(y=yT;y<=yB;y++){
		//求扫描线==y时，深度值z的倒数随x线性变化的步长
		zInverseStep=(zInverseRight-zInverseLeft)/(xright-xleft);

		float S,T;
		if(xright-xleft!=0){

			S=(sright-sleft)/(xright-xleft);
			T=(tright-tleft)/(xright-xleft);
		}

		s=sleft;
		t=tleft;
		//X屏幕裁剪
		float zInverseCL;
		int xL,xR;
		if(xleft+0.5<0){
			xL=0;
			zInverseCL=zInverseLeft+zInverseStep*(xL-xleft);
			s+=S*(xL-xleft);
			t+=T*(xL-xleft);
		} else {
			xL=int(xleft+0.5);
			zInverseCL=zInverseLeft+zInverseStep*(xL-xleft);
			s+=S*(xL-xleft);
			t+=T*(xL-xleft);
		}
		if(xright+0.5<1360){
			xR=int(xright+0.5);
		} else {
			xR=1359;
		}
		int x;
		float zInverse;
		for(x=xL,zInverse=zInverseCL;x<=xR;x++,zInverse+=zInverseStep){
			if(zInverse<0||zInverse>0.002){
				continue;
			}
			if(videobuf->m_zBuffer[x][y]<zInverse+zhang){
				videobuf->m_zBuffer[x][y]=zInverse+zhang;
				int u=(int)(s/zInverse+0.5),v=(int)(t/zInverse+0.5);
				if(u<256&&u>=0&&v<256&&v>=0){
					videobuf->drawPixl(x,y,tex,u,v,flg);
				}
			}


			s+=S;
			t+=T;
		}
		//求扫描线==y时，扫描线的右端和左端
		xleft+=A;
		xright+=B;
		//求扫描线==y时，扫描线的右端和左端在相机空间的深度值z的倒数
		zInverseLeft+=C;
		zInverseRight+=D;


		//求扫描线==y时，纹理的左端和右端
		sleft+=At;
		sright+=Bt;
		tleft+=Ct;
		tright+=Dt;
	}

}


void Scene::dfillPanBottomTriFace(HDC hdc,Vertex vBottom,Vertex vMid,Vertex vTop,LPCSTR fileName,double flg,int index){

	CVector4 v0=vBottom.m_pos;
	CVector4 v1=vMid.m_pos;
	CVector4 v2=vTop.m_pos;
	BYTE *tex=(BYTE *)m_objectList[index].m_texbitmap.bmBits;

	//裁剪测试
	if(v0.y()<0||v2.y()>=768||(v1.x()<0&&v2.x()<0)||(v2.x()>=1360&&v0.x()>=1360)){
		return;
	}


	float zInverseLeft,zInverseRight,zInverseStep;
	//一条扫描线的左端和右端：xleft,xright
	//扫描线 y
	//扫描线上的烧苗点 x
	float xleft,xright;

	float x0  = vBottom.m_pos.x();
	float y0  = vBottom.m_pos.y();
	float tu0 = vBottom.m_texCoord.x() / vBottom.m_pos.z();
	float tv0 = vBottom.m_texCoord.y() / vBottom.m_pos.z();

	float x1  = vMid.m_pos.x();
	float y1  = vMid.m_pos.y();
	float tu1 = vMid.m_texCoord.x() / vMid.m_pos.z();
	float tv1 = vMid.m_texCoord.y() / vMid.m_pos.z();

	float x2  = vTop.m_pos.x();
	float y2  = vTop.m_pos.y();
	float tu2 = vTop.m_texCoord.x() / vTop.m_pos.z();
	float tv2 = vTop.m_texCoord.y() / vTop.m_pos.z();


	//一条扫描线的左端和右端
	float zleft,zrighr;
	//纹理坐标s和t
	float s, t,sleft,sright,tleft,tright; 


	float A,B,C,D;
	A=(v2.x()-v0.x())/(v2.y()-v0.y());
	B=(v2.x()-v1.x())/(v2.y()-v1.y());
	C=(1/v2.z()-1/v0.z())/(v2.y()-v0.y());
	D=(1/v2.z()-1/v1.z())/(v2.y()-v1.y());
	float At,Bt,Ct,Dt;
	At=(tu0-tu2)/(vBottom.m_pos.y()-vTop.m_pos.y());
	Bt=(tu2-tu1)/(vTop.m_pos.y()-vMid.m_pos.y());
	Ct=(tv0-tv2)/(vBottom.m_pos.y()-vTop.m_pos.y());
	Dt=(tv2-tv1)/(vTop.m_pos.y()-vMid.m_pos.y());

	//求扫描线==y时，扫描线的右端和左端
	xleft=v2.x();
	xright=v2.x();
	//求扫描线==y时，扫描线的右端和左端在相机空间的深度值z的倒数
	zInverseLeft=1/v2.z();
	zInverseRight=1/v2.z();

	//求扫描线==y时，纹理的左端和右端
	sleft=tu2;
	sright=tu2;
	tleft=tv2;
	tright=tv2;

	int yT,yB;
	//Y屏幕裁剪
	if(v2.y()+0.5<0){
		yT=0;
		//求扫描线==y时，扫描线的右端和左端
		xleft+=A*(yT-v2.y());
		xright+=B*(yT-v2.y());
		//求扫描线==y时，扫描线的右端和左端在相机空间的深度值z的倒数
		zInverseLeft+=C*(yT-v2.y());
		zInverseRight+=D*(yT-v2.y());

		//求扫描线==y时，纹理的左端和右端
		sleft+=At*(yT-v2.y());
		sright+=Bt*(yT-v2.y());
		tleft+=Ct*(yT-v2.y());
		tright+=Dt*(yT-v2.y());
	} else {
		yT=int(v2.y()+0.5);
		//求扫描线==y时，扫描线的右端和左端
		xleft+=A*(yT-v2.y());
		xright+=B*(yT-v2.y());
		//求扫描线==y时，扫描线的右端和左端在相机空间的深度值z的倒数
		zInverseLeft+=C*(yT-v2.y());
		zInverseRight+=D*(yT-v2.y());

		//求扫描线==y时，纹理的左端和右端
		sleft+=At*(yT-v2.y());
		sright+=Bt*(yT-v2.y());
		tleft+=Ct*(yT-v2.y());
		tright+=Dt*(yT-v2.y());
	}
	if(v0.y()+0.5<768){
		yB=int(v0.y());
	} else {
		yB=767;
	}
	int y;
	for(y=yT;y<=yB;y++){
		//求扫描线==y时，深度值z的倒数随x线性变化的步长
		zInverseStep=(zInverseRight-zInverseLeft)/(xright-xleft);

		float S,T;
		if(xright-xleft!=0){
			S=(sright-sleft)/(xright-xleft);
			T=(tright-tleft)/(xright-xleft);
		}

		s=sleft;
		t=tleft;
		//X屏幕裁剪
		float zInverseCL=zInverseLeft;
		int xL,xR;
		if(xleft+0.5<0){
			xL=0;
			zInverseCL=zInverseLeft+zInverseStep*(xL-xleft);
			s+=S*(xL-xleft);
			t+=T*(xL-xleft);
		} else {
			xL=int(xleft+0.5);
			zInverseCL=zInverseLeft+zInverseStep*(xL-xleft);
			s+=S*(xL-xleft);
			t+=T*(xL-xleft);
		}
		if(xright+0.5<1360){
			xR=int(xright+0.5);
		} else {
			xR=1359;
		}
		int x;
		float zInverse;
		for(x=xL,zInverse=zInverseCL;x<=xR;x++,zInverse+=zInverseStep){	
			if(zInverse<0||zInverse>0.002){
				continue;
			}
			if(videobuf->m_zBuffer[x][y]<zInverse+zhang){
				videobuf->m_zBuffer[x][y]=zInverse+zhang;
				int u=(int)(s/zInverse+0.5),v=(int)(t/zInverse+0.5);
				if(u<256&&u>=0&&v<256&&v>=0){
					videobuf->drawPixl(x,y,tex,u,v,flg);
				}
			}


			s+=S;
			t+=T;
		}
		//求扫描线==y时，扫描线的右端和左端
		xleft+=A;
		xright+=B;
		//求扫描线==y时，扫描线的右端和左端在相机空间的深度值z的倒数
		zInverseLeft+=C;
		zInverseRight+=D;


		//求扫描线==y时，纹理的左端和右端
		sleft+=At;
		sright+=Bt;
		tleft+=Ct;
		tright+=Dt;
	}

}





void Scene::PanTopTri(HDC hdc,Vertex vBottom,Vertex vMid,Vertex vTop,LPCSTR fileName,double flg,short index[]){

	CVector4 v0=vBottom.m_pos;
	CVector4 v1=vMid.m_pos;
	CVector4 v2=vTop.m_pos;

	//裁剪测试
	if(v0.y()<0||v2.y()>=768||(v1.x()<0&&v0.x()<0)||(v2.x()>=1360&&v0.x()>=1360)){
		return;
	}



	float zInverseLeft,zInverseRight,zInverseStep;
	//一条扫描线的左端和右端：xleft,xright
	//扫描线 y
	//扫描线上的烧苗点 x
	float xleft,xright;

	float x0  = vBottom.m_pos.x();
	float y0  = vBottom.m_pos.y();

	float x1  = vMid.m_pos.x();
	float y1  = vMid.m_pos.y();

	float x2  = vTop.m_pos.x();
	float y2  = vTop.m_pos.y();


	//一条扫描线的左端和右端
	float zleft,zrighr;


	float A,B,C,D;
	A=(v2.x()-v0.x())/(v2.y()-v0.y());
	B=(v1.x()-v0.x())/(v1.y()-v0.y());
	C=(1/v2.z()-1/v0.z())/(v2.y()-v0.y());
	D=(1/v1.z()-1/v0.z())/(v1.y()-v0.y());

	//求扫描线==y时，扫描线的右端和左端
	xleft=v2.x();
	xright=v1.x();
	//求扫描线==y时，扫描线的右端和左端在相机空间的深度值z的倒数
	zInverseLeft=1/v2.z();
	zInverseRight=1/v1.z();


	int yT,yB;
	//Y屏幕裁剪
	if(v2.y()+0.5<0){
		yT=0;
		//求扫描线==y时，扫描线的右端和左端
		xleft+=A*(yT-v2.y());
		xright+=B*(yT-v2.y());
		//求扫描线==y时，扫描线的右端和左端在相机空间的深度值z的倒数
		zInverseLeft+=C*(yT-v2.y());
		zInverseRight+=D*(yT-v2.y());


	} else {
		yT=int(v2.y()+0.5);
		if(yT<v2.y()){
			yT=yT+1;
		}
		//求扫描线==y时，扫描线的右端和左端
		xleft+=A*(yT-v2.y());
		xright+=B*(yT-v2.y());
		//求扫描线==y时，扫描线的右端和左端在相机空间的深度值z的倒数
		zInverseLeft+=C*(yT-v2.y());
		zInverseRight+=D*(yT-v2.y());

	}
	if(v0.y()+0.5<768){
		yB=int(v0.y()+0.5);
	} else {
		yB=767;
	}
	int y;
	for(y=yT;y<=yB;y++){
		//求扫描线==y时，深度值z的倒数随x线性变化的步长
		zInverseStep=(zInverseRight-zInverseLeft)/(xright-xleft);
		//X屏幕裁剪
		float zInverseCL;
		int xL,xR;
		if(xleft+0.5<0){
			xL=0;
			zInverseCL=zInverseLeft+zInverseStep*(xL-xleft);
		} else {
			xL=int(xleft+0.5);
			zInverseCL=zInverseLeft+zInverseStep*(xL-xleft);
		}
		if(xright+0.5<1360){
			xR=int(xright+0.5);
		} else {
			xR=1359;
		}
		int x;
		float zInverse;
		for(x=xL,zInverse=zInverseCL;x<=xR;x++,zInverse+=zInverseStep){
			if(zInverse<0||zInverse>0.002){
				continue;
			}
			if(x>1000){
				int yyyy;
				yyyy=1111;
			}
			if(videobuf->m_zBuffer[x][y]<zInverse+zhang){
				videobuf->m_zBuffer[x][y]=zInverse+zhang;
					videobuf->drawPixl(x,y,index,flg);
			}


		}
		//求扫描线==y时，扫描线的右端和左端
		xleft+=A;
		xright+=B;
		//求扫描线==y时，扫描线的右端和左端在相机空间的深度值z的倒数
		zInverseLeft+=C;
		zInverseRight+=D;
	}

}


void Scene::PanBottomTri(HDC hdc,Vertex vBottom,Vertex vMid,Vertex vTop,LPCSTR fileName,double flg,short index[]){

	CVector4 v0=vBottom.m_pos;
	CVector4 v1=vMid.m_pos;
	CVector4 v2=vTop.m_pos;

	//裁剪测试
	if(v0.y()<0||v2.y()>=768||(v1.x()<0&&v2.x()<0)||(v2.x()>=1360&&v0.x()>=1360)){
		return;
	}


	float zInverseLeft,zInverseRight,zInverseStep;
	//一条扫描线的左端和右端：xleft,xright
	//扫描线 y
	//扫描线上的烧苗点 x
	float xleft,xright;

	float x0  = vBottom.m_pos.x();
	float y0  = vBottom.m_pos.y();

	float x1  = vMid.m_pos.x();
	float y1  = vMid.m_pos.y();

	float x2  = vTop.m_pos.x();
	float y2  = vTop.m_pos.y();


	//一条扫描线的左端和右端
	float zleft,zrighr;


	float A,B,C,D;
	A=(v2.x()-v0.x())/(v2.y()-v0.y());
	B=(v2.x()-v1.x())/(v2.y()-v1.y());
	C=(1/v2.z()-1/v0.z())/(v2.y()-v0.y());
	D=(1/v2.z()-1/v1.z())/(v2.y()-v1.y());

	//求扫描线==y时，扫描线的右端和左端
	xleft=v2.x();
	xright=v2.x();
	//求扫描线==y时，扫描线的右端和左端在相机空间的深度值z的倒数
	zInverseLeft=1/v2.z();
	zInverseRight=1/v2.z();

	int yT,yB;
	//Y屏幕裁剪
	if(v2.y()+0.5<0){
		yT=0;
		//求扫描线==y时，扫描线的右端和左端
		xleft+=A*(yT-v2.y());
		xright+=B*(yT-v2.y());
		//求扫描线==y时，扫描线的右端和左端在相机空间的深度值z的倒数
		zInverseLeft+=C*(yT-v2.y());
		zInverseRight+=D*(yT-v2.y());
	} else {
		yT=int(v2.y()+0.5);
		//求扫描线==y时，扫描线的右端和左端
		xleft+=A*(yT-v2.y());
		xright+=B*(yT-v2.y());
		//求扫描线==y时，扫描线的右端和左端在相机空间的深度值z的倒数
		zInverseLeft+=C*(yT-v2.y());
		zInverseRight+=D*(yT-v2.y());

	}
	if(v0.y()<768){
		yB=int(v0.y());
	} else {
		yB=767;
	}
	int y;
	for(y=yT;y<=yB;y++){
		//求扫描线==y时，深度值z的倒数随x线性变化的步长
		zInverseStep=(zInverseRight-zInverseLeft)/(xright-xleft);

		//X屏幕裁剪
		float zInverseCL=zInverseLeft;
		int xL,xR;
		if(xleft+0.5<0){
			xL=0;
			zInverseCL=zInverseLeft+zInverseStep*(xL-xleft);
		} else {
			xL=int(xleft+0.5);
			zInverseCL=zInverseLeft+zInverseStep*(xL-xleft);
		}
		if(xright+0.5<1360){
			xR=int(xright+0.5);
		} else {
			xR=1359;
		}
		int x;
		float zInverse;
		for(x=xL,zInverse=zInverseCL;x<=xR;x++,zInverse+=zInverseStep){	
			if(zInverse<0||zInverse>0.002){
				continue;
			}
			if(videobuf->m_zBuffer[x][y]<zInverse+zhang){
				videobuf->m_zBuffer[x][y]=zInverse+zhang;
					videobuf->drawPixl(x,y,index,flg);
			}


		}
		//求扫描线==y时，扫描线的右端和左端
		xleft+=A;
		xright+=B;
		//求扫描线==y时，扫描线的右端和左端在相机空间的深度值z的倒数
		zInverseLeft+=C;
		zInverseRight+=D;

	}

}