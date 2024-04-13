#include "StdAfx.h"
#include "VideoBuf.h"

void VideoBuf::drawPixl(int x, int y, BYTE *tex, int s, int t,double flg){
	int pix=nLnBytes*y+3*x;
	int texpix=768*s+3*t;
	bmbuf[pix]=min(255,tex[texpix]*(flg));
	bmbuf[pix+1]=min(255,tex[texpix+1]*(flg));
	bmbuf[pix+2]=min(255,tex[texpix+2]*(flg));
}

void VideoBuf::drawPixl(int x, int y, short color[],double flg){
	int pix=nLnBytes*y+3*x;
	bmbuf[pix]=min(255,color[0]*(flg));
	bmbuf[pix+1]=min(255,color[1]*(flg));
	bmbuf[pix+2]=min(255,color[2]*(flg));
}

void VideoBuf::drawRectangle(int x,int y,int w,int h,BYTE r,BYTE g,BYTE b){
	int pix;
	int pix1;
	for(int i=y;i<h;i++){
		pix=nLnBytes*i;
		for(int j=x;j<w;j++){
			pix1=pix+3*j;
			bmbuf[pix1]=b;
		    bmbuf[pix1+1]=g;
		    bmbuf[pix1+2]=r;
		}
	}

}
void VideoBuf::drawLine(int x,int y,int w,int h,BYTE r,BYTE g,BYTE b){
	int pix;
	int pix1;
	for(int i=y;i<h;i++){
		pix=nLnBytes*i;
		for(int j=x;j<w;j++){
			pix1=pix+3*j;
			bmbuf[pix1]=0;
		    bmbuf[pix1+1]=0;
		    bmbuf[pix1+2]=0;
		}
	}

}