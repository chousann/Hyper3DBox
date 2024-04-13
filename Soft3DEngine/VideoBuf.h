#ifndef __HelloCpp__VideoBuf__
#define __HelloCpp__VideoBuf__
#include"windows.h"
class VideoBuf{
	public:

		BITMAPINFO bmpInfo;
		BYTE *bmbuf;
		long nLnBytes;
		float m_zBuffer[1360][768]; 

	public:
		VideoBuf(){
			for(int j=0;j<768;j++){
				for(int i=0;i<1360;i++){
					m_zBuffer[j][i]=0;
				}
			}
			init();
		};	
		void init(){
			bmpInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
			bmpInfo.bmiHeader.biWidth = 1360;
			bmpInfo.bmiHeader.biHeight = -768;
			bmpInfo.bmiHeader.biPlanes = 1;
			bmpInfo.bmiHeader.biBitCount = 24;
			bmpInfo.bmiHeader.biCompression = BI_RGB;
			bmpInfo.bmiHeader.biSizeImage = 0;
			bmpInfo.bmiHeader.biXPelsPerMeter = 3000;
			bmpInfo.bmiHeader.biYPelsPerMeter = 3000;
			bmpInfo.bmiHeader.biClrUsed = 0;
			bmpInfo.bmiHeader.biClrImportant = 0;
	
			nLnBytes = (bmpInfo.bmiHeader.biWidth*3+3)/4*4;
			bmbuf = new BYTE[nLnBytes*abs(bmpInfo.bmiHeader.biHeight)];
	
			//Çå³ÉºÚÉ«
			memset(bmbuf,0,nLnBytes*abs(bmpInfo.bmiHeader.biHeight));

		}
		void drawPixl(int x, int y, BYTE *tex, int s, int t,double flg);
		void drawPixl(int x, int y, short color[],double flg);
		void drawLine(int x,int y,int w,int h,BYTE r,BYTE g ,BYTE b);
		void drawRectangle(int x,int y,int w,int h,BYTE r,BYTE g ,BYTE b);

		virtual~VideoBuf(){};
};
#endif /* defined(__HelloCpp__mesh__) */