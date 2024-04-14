// Hyper3DBox.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "resource.h"
#include "Soft3DEngine/scene.h"
#include <time.h>
#include <math.h>
#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];								// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];								// The title bar text

// Foward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
void OnKeyDown(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
void OnPaint(HDC hdc,HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
void Paint(HDC hdc,HWND hWnd);
void load();
void gameMain(MSG msg);
Scene scene=Scene();
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;
	scene.init();
	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_HYPER3DBOX, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow)) 
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_HYPER3DBOX);

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0)) 
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		//gameMain(msg);
	}

	return msg.wParam;
}
void CALLBACK TimerProc(HWND hwnd,UINT nmsg,UINT ntimerid,DWORD dwtime){
	if(ntimerid==1){
		scene.m_objectList[2].rotate.sety(scene.m_objectList[2].rotate.y()-2);			
		InvalidateRect(hwnd,NULL,TRUE);
	}
}
void gameMain(MSG msg){
	HWND hwnd=msg.hwnd;
	HDC hdc=GetDC(hwnd);
	switch(msg.message){
		case VK_RIGHT:
			{
				if((scene.m_objectList[0].turning+=5)>30){
					scene.m_objectList[0].turning=15;
				}

			}
			break;		
		case VK_LEFT:
			{
				if((scene.m_objectList[0].turning-=5)<-30){
					scene.m_objectList[0].turning=-15;
				}
			}
			break;
		default:
			if(scene.m_objectList[0].turning>0){
				//scene.m_objectList[0].turning-=0.1;
			}else if(scene.m_objectList[0].turning<0){
				//scene.m_objectList[0].turning+=0.1;
			}
			break;
	}

	clock_t start=clock();
	Paint(hdc,hwnd);
	clock_t stop=clock();
	double dur=(double)(stop-start)/(double)CLOCKS_PER_SEC;
	int fps=(int)min(1000,1.0/dur);
	char str[10]={0,0,0,0,0,0,0,0,0,0};
	itoa(fps,str,10);
	TextOut(hdc,0,0,str,10);

	TextOut(hdc,0,20,"J,K,L,I,N,M移动物体",19);
	TextOut(hdc,0,40,"UP,DOWN,LEFT,RIGHT,Z,X移动相机",30);
	TextOut(hdc,0,60,"A,S,D,W旋转物体",15);
	char str1[10]={0,0,0,0,0,0,0,0,0,0};
	itoa(scene.vNum,str1,10);
	TextOut(hdc,0,80,str1,10);
	char str2[10]={0,0,0,0,0,0,0,0,0,0};
	itoa(scene.triNum,str2,10);
	TextOut(hdc,0,100,str2,10);
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage is only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); 

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_HYPER3DBOX);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= NULL;
	wcex.lpszMenuName	= (LPCSTR)IDC_HYPER3DBOX;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, (LPCTSTR)IDI_SMALL);

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HANDLE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, unsigned, WORD, LONG)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LPSTR str="222";
LPCSTR str1("C:\\Users\\mrzhang\\Desktop\\文件\\编程\\自己的代码\\格斗\\res\\qi.bmp");
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	TCHAR szHello[MAX_LOADSTRING];
	LoadString(hInst, IDS_HELLO, szHello, MAX_LOADSTRING);

	switch (message) 
	{
		case WM_KEYDOWN:
			//MessageBox(hWnd,"11111111","555",1);
			OnKeyDown(hWnd,message,wParam,lParam);
			break;
		case WM_CREATE:{
			//获取客户区尺寸
			RECT rect;
			GetClientRect (hWnd,&rect);
			int cxClient=rect.right;
			int cyClient=rect.bottom;
			LPCSTR str="C:\\Users\\mrzhang\\Desktop\\文件\\编程\\自己的代码\\格斗\\res\\qi.bmp";
			//获得前置缓冲区的DC
			HDC hdc1=GetDC(hWnd);
			//装载位图
			HBITMAP hbitmap=(HBITMAP)LoadImage(NULL,str,IMAGE_BITMAP,0,0,LR_LOADFROMFILE|LR_CREATEDIBSECTION);
			BITMAP bit;
			if(GetObject(hbitmap,sizeof(BITMAP),&bit)==0)
				MessageBox(NULL,"heoo",0,0);
			HDC memdc1=CreateCompatibleDC(hdc1);
			BITMAPINFO bmpInfo;
			bmpInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER); 
			bmpInfo.bmiHeader.biWidth=256;
			bmpInfo.bmiHeader.biHeight=256;
			bmpInfo.bmiHeader.biPlanes=1;
			bmpInfo.bmiHeader.biBitCount=24;
			bmpInfo.bmiHeader.biCompression = BI_RGB;
			bmpInfo.bmiHeader.biSizeImage = 0;
			bmpInfo.bmiHeader.biXPelsPerMeter = 3000;
			bmpInfo.bmiHeader.biYPelsPerMeter = 3000;
			bmpInfo.bmiHeader.biClrUsed = 0; 
			bmpInfo.bmiHeader.biClrImportant = 0; 
			long nLnBytes = (bmpInfo.bmiHeader.biWidth*3+3)/4*4;  
			BYTE *pData = new BYTE[nLnBytes*abs(bmpInfo.bmiHeader.biHeight)];
			memset(pData,0,nLnBytes*abs(bmpInfo.bmiHeader.biHeight));  
			for(int j=0;j<128;j++){
			for(int i=0; i<128; i++)  {
				pData[j*nLnBytes+i*3] = 128; 
				pData[j*nLnBytes+i*3+1] = 255; 
				pData[j*nLnBytes+i*3+2] = 128; 
			}}
			scene.pData=pData;

			//scene.m_bit=bit;
			//bit.bmBits[
			SelectObject(memdc1,hbitmap);
			scene.texdc=memdc1;
			//释放DC
			ReleaseDC(hWnd,hdc1);
			load();
			SetTimer(hWnd,1,5,TimerProc);

			//scene.init_texbitmap("C:\\Users\\mrzhang\\Desktop\\文件\\编程\\自己的代码\\格斗\\res\\qi.bmp");
					   }
			break;
		case WM_COMMAND:
			wmId    = LOWORD(wParam); 
			wmEvent = HIWORD(wParam); 
			// Parse the menu selections:
			switch (wmId)
			{
				case IDM_ABOUT:
				   DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
				   break;
				case IDM_EXIT:
				   DestroyWindow(hWnd);
				   break;
				default:
				   return DefWindowProc(hWnd, message, wParam, lParam);
			}
			break;
		case WM_PAINT:{
			hdc = BeginPaint(hWnd, &ps);
			clock_t start=clock();
			OnPaint(hdc,hWnd, message, wParam, lParam);
			clock_t stop=clock();
			double dur=(double)(stop-start)/(double)CLOCKS_PER_SEC;
			int fps=(int)min(1000,1.0/dur);
			char str[10]={0,0,0,0,0,0,0,0,0,0};
			itoa(fps,str,10);
			TextOut(hdc,0,0,str,10);

			TextOut(hdc,0,20,"J,K,L,I,N,M移动物体",19);
			TextOut(hdc,0,40,"UP,DOWN,LEFT,RIGHT,Z,X移动相机",30);
			TextOut(hdc,0,60,"A,S,D,W旋转物体",15);
			char str1[10]={0,0,0,0,0,0,0,0,0,0};
			itoa(scene.vNum,str1,10);
			TextOut(hdc,0,80,str1,10);
			char str2[10]={0,0,0,0,0,0,0,0,0,0};
			itoa(scene.triNum,str2,10);
			TextOut(hdc,0,100,str2,10);


			//TextOut(hdc,0,5+20*2,string("fps:")+numberToStr(fps));
			EndPaint(hWnd, &ps);
			break;}
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}
void load(){
	CVector4 worldPos(0,700,2000,1);
	string fileFullPath="resource\\";
	string filename="file.obj";
	Object obj0(fileFullPath,filename,worldPos,"cube","obj");
	obj0.rotate.setx(180);
	scene.loadObject(obj0);
	CVector4 worldPos1(200,-50,600,1);
	fileFullPath="resource\\";
	filename="cube.txt";
	Object obj1(fileFullPath,filename,worldPos1,"cube1","txt");
	scene.loadObject(obj1);
		for(int i=0;i<0;i++){
			int x,z;
			x=rand()%1000;
			z=rand()%700;
			CVector4 worldPos1(x,-50,z,1);
			Object obj2(fileFullPath,filename,worldPos1,"cube1");
			scene.loadObject(obj2);
		}
}
// Mesage handler for about box.
LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_INITDIALOG:
				return TRUE;

		case WM_COMMAND:
			if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) 
			{
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}
			break;
	}
    return FALSE;
}
void OnKeyDown(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
	switch(wParam){
		MessageBox(hWnd,"11111111","555",1);
		case VK_UP:
			{
				CVector4 eyePos(scene.m_camera->getEyePos().x()+20*sin(scene.m_camera->ydir),scene.m_camera->getEyePos().y(),scene.m_camera->getEyePos().z()+20*cos(scene.m_camera->ydir),scene.m_camera->getEyePos().w());
				scene.m_camera->setEyePos(eyePos);
				//Cc3dVector4 center(scene.m_camera->getEyePos().x()-100*sin(scene.m_camera->ydir),scene.m_camera->getEyePos().y(),scene.m_camera->getEyePos().z()+100*cos(scene.m_camera->ydir),scene.m_camera->getEyePos().w());
				//scene.m_camera->setCenter(center);
			}
			InvalidateRect(hWnd,NULL,TRUE);
			//SendMessage(hWnd,WM_PAINT,NULL,NULL);
			break;
		case VK_DOWN:
			{
				CVector4 eyePos(scene.m_camera->getEyePos().x()-20*sin(scene.m_camera->ydir),scene.m_camera->getEyePos().y(),scene.m_camera->getEyePos().z()-20*cos(scene.m_camera->ydir),scene.m_camera->getEyePos().w());
				scene.m_camera->setEyePos(eyePos);
				//Cc3dVector4 center(scene.m_camera->getEyePos().x()-100*sin(scene.m_camera->ydir),scene.m_camera->getEyePos().y(),scene.m_camera->getEyePos().z()+100*cos(scene.m_camera->ydir),scene.m_camera->getEyePos().w());
				//scene.m_camera->setCenter(center);
			}
			InvalidateRect(hWnd,NULL,TRUE);
			break;		
		case VK_RIGHT:
			{
				if((scene.m_camera->ydir+=2)>=360)
					scene.m_camera->ydir-=360;
				//Cc3dVector4 center(scene.m_camera->getEyePos().x()-100*sin(scene.m_camera->ydir),scene.m_camera->getEyePos().y(),scene.m_camera->getEyePos().z()+100*cos(scene.m_camera->ydir),scene.m_camera->getEyePos().w());
				//scene.m_camera->setCenter(center);
			}
			InvalidateRect(hWnd,NULL,TRUE);
			break;		
		case VK_LEFT:
			{
				if((scene.m_camera->ydir-=2)<=-360)
					scene.m_camera->ydir+=360;
				//Cc3dVector4 center(scene.m_camera->getEyePos().x()-100*sin(scene.m_camera->ydir),scene.m_camera->getEyePos().y(),scene.m_camera->getEyePos().z()+100*cos(scene.m_camera->ydir),scene.m_camera->getEyePos().w());
				//scene.m_camera->setCenter(center);
			}
			InvalidateRect(hWnd,NULL,TRUE);
			break;
		case 90:
			{
				CVector4 eyePos(scene.m_camera->getEyePos().x(),scene.m_camera->getEyePos().y(),scene.m_camera->getEyePos().z()+20,scene.m_camera->getEyePos().w());
				scene.m_camera->setEyePos(eyePos);
			}
			InvalidateRect(hWnd,NULL,TRUE);
			break;
		case 88:
			{
				CVector4 eyePos(scene.m_camera->getEyePos().x(),scene.m_camera->getEyePos().y(),scene.m_camera->getEyePos().z()-20,scene.m_camera->getEyePos().w());
				scene.m_camera->setEyePos(eyePos);
			}
			InvalidateRect(hWnd,NULL,TRUE);
			break;
		case 74://J
			{
				scene.m_objectList[1].worldPos.init(scene.m_objectList[1].worldPos.x()-2,scene.m_objectList[1].worldPos.y(),scene.m_objectList[1].worldPos.z(),1);
			}
			InvalidateRect(hWnd,NULL,TRUE);
			break;
		case 75://K
			{
				scene.m_objectList[1].worldPos.init(scene.m_objectList[1].worldPos.x(),scene.m_objectList[1].worldPos.y()+2,scene.m_objectList[1].worldPos.z(),1);
			}
			InvalidateRect(hWnd,NULL,TRUE);
			break;
		case 76://L
			{
				scene.m_objectList[1].worldPos.init(scene.m_objectList[1].worldPos.x()+2,scene.m_objectList[1].worldPos.y(),scene.m_objectList[1].worldPos.z(),1);
			}
			InvalidateRect(hWnd,NULL,TRUE);
			break;
		case 73://I
			{
				scene.m_objectList[1].worldPos.init(scene.m_objectList[1].worldPos.x(),scene.m_objectList[1].worldPos.y()-2,scene.m_objectList[1].worldPos.z(),1);
			}
			InvalidateRect(hWnd,NULL,TRUE);
			break;
		case 78://N
			{
				scene.m_objectList[1].worldPos.init(scene.m_objectList[1].worldPos.x(),scene.m_objectList[1].worldPos.y(),scene.m_objectList[1].worldPos.z()+10,1);
			}
			InvalidateRect(hWnd,NULL,TRUE);
			break;
		case 77://M
			{
				scene.m_objectList[1].worldPos.init(scene.m_objectList[1].worldPos.x(),scene.m_objectList[1].worldPos.y(),scene.m_objectList[1].worldPos.z()-10,1);
			}
			InvalidateRect(hWnd,NULL,TRUE);
			break;
		case 65://A
			{
				scene.m_objectList[1].rotate.sety(scene.m_objectList[1].rotate.y()-1);
			}
			InvalidateRect(hWnd,NULL,TRUE);
			break;
		case 83://S
			{
				scene.m_objectList[1].rotate.setx(scene.m_objectList[1].rotate.x()-1);
				//scene.m_objectList[2].worldPos.init(scene.m_objectList[2].worldPos.x(),scene.m_objectList[2].worldPos.y()+10,scene.m_objectList[2].worldPos.z(),1);
			}
			InvalidateRect(hWnd,NULL,TRUE);
			break;
		case 68://D
			{
				scene.m_objectList[1].rotate.sety(scene.m_objectList[1].rotate.y()+1);
			}
			InvalidateRect(hWnd,NULL,TRUE);
			break;
		case 87://W
			{
				scene.m_objectList[1].rotate.setx(scene.m_objectList[1].rotate.x()+1);
				//scene.m_objectList[2].worldPos.init(scene.m_objectList[2].worldPos.x(),scene.m_objectList[2].worldPos.y()-10,scene.m_objectList[2].worldPos.z(),1);
			}
			InvalidateRect(hWnd,NULL,TRUE);
			break;
		case 53://5
			{
				CVector4 eyePos(scene.m_camera->getEyePos().x(),scene.m_camera->getEyePos().y()-10,scene.m_camera->getEyePos().z(),scene.m_camera->getEyePos().w());
				scene.m_camera->setEyePos(eyePos);
			}
			InvalidateRect(hWnd,NULL,TRUE);
			break;
		case 50://2
			{
				CVector4 eyePos(scene.m_camera->getEyePos().x(),scene.m_camera->getEyePos().y()+10,scene.m_camera->getEyePos().z(),scene.m_camera->getEyePos().w());
				scene.m_camera->setEyePos(eyePos);
			}
			InvalidateRect(hWnd,NULL,TRUE);
			break;
		case 66://2
			{
				if(scene.mode<3){

				scene.mode+=1;
				}else{
					scene.mode=1;
				}
			}
			InvalidateRect(hWnd,NULL,TRUE);
			break;

	}
}

void OnPaint(HDC hdc,HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
	HDC memdc=CreateCompatibleDC(hdc);
	HBITMAP hbitmap;
	BITMAP bitmap;
	hbitmap=CreateCompatibleBitmap(hdc,1360,768);

	SelectObject(memdc,hbitmap);
	PatBlt(memdc,0,0,1360,768,WHITENESS);
	//////////////////
	// TODO: Add any drawing code here...
	scene.softRasterization1(memdc,hbitmap);	
	BitBlt(hdc,0,0,1360,768,memdc,0,0,SRCCOPY);
	TextOut(hdc,0,0,"hello",5);
	DeleteObject(hbitmap);
	DeleteDC(memdc);
}
void Paint(HDC hdc,HWND hWnd){
	HDC memdc=CreateCompatibleDC(hdc);
	HBITMAP hbitmap;
	BITMAP bitmap;
	hbitmap=CreateCompatibleBitmap(hdc,1360,768);

	SelectObject(memdc,hbitmap);
	PatBlt(memdc,0,0,1360,768,WHITENESS);
	//////////////////
	// TODO: Add any drawing code here...
	scene.softRasterization1(memdc,hbitmap);	
	BitBlt(hdc,0,0,1360,768,memdc,0,0,SRCCOPY);
	TextOut(hdc,0,0,"hello",5);
	DeleteObject(hbitmap);
	DeleteDC(memdc);
}