#include <windows.h>

//6.处理窗口过程
LRESULT CALLBACK  CallWindowProcA(
	HWND    hWnd,	//消息所属的窗口句柄
	UINT    uMsg,	//消息名称, WM_XXXX 消息名
	WPARAM  wParam,	//键盘
	LPARAM  lParam	//鼠标
) {
	//返回值默认处理方式

	switch (uMsg)
	{
	case WM_CLOSE:
		//xxxWindwos()的方法不会进入消息队列,而是直接执行
		DestroyWindow(hWnd); //发送另外一个消息 WM_DESTROY
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	
	case WM_LBUTTONDOWN: //鼠标左键按下
	{
		int xPos = LOWORD(lParam);
		int yPos = HIWORD(lParam);

		char buf[1024];
		wsprintf(buf, TEXT("x=%d,y=%d"), xPos, yPos);
		MessageBox(hWnd, buf, TEXT("鼠标左键按下"), MB_OK);


		break;
	}

	case WM_KEYDOWN:
	{
		MessageBox(hWnd, TEXT("键盘按下"), TEXT("键盘按下"), MB_OK);
		break;
	}
	case WM_PAINT:	//绘图
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		
		TextOut(hdc, 100, 100, TEXT("Hello , World"), strlen("Hello , World"));
		
		EndPaint(hWnd, &ps);

	}
		break;
	default:

		break;
	}

	return DefWindowProc(hWnd, uMsg,wParam,lParam);
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, LPSTR lpCndLine, int nShowCmd) {

	//1.设计窗口
	WNDCLASS wc;
	wc.cbClsExtra = 0; //类的额外的内cun
	wc.cbWndExtra = 0;	//窗口额外内存
	wc.hbrBackground =(HBRUSH) GetStockObject(WHITE_BRUSH); //设置背景
	wc.hCursor = LoadCursor(NULL,IDC_HAND);
	wc.hIcon = LoadCursor(NULL, IDC_ARROW);
	wc.hInstance = hInstance;
	wc.lpfnWndProc = CallWindowProcA; //窗口过程;
	wc.lpszClassName = TEXT("WIN");  //指定窗口的类名称
	wc.lpszMenuName = NULL; 
	wc.style = 0;
	

	//2.注册窗口类
	RegisterClass(&wc);
		

	//3.创建窗口
	//lpClassName, lpWindowName, dwStyle, x, y,nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam
	HWND hwnd = CreateWindow(
		wc.lpszClassName,
		TEXT("WINDOWS"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	//4. 显示窗口
	ShowWindow(hwnd, SW_SHOWNORMAL);
	UpdateWindow(hwnd);


	//5.通过循环取消息
	MSG msg;

	/*
	 HWND        hwnd;	//主窗口句柄
    UINT        message;	//消息名称
    WPARAM      wParam;	//键盘消息
    LPARAM      lParam;	//鼠标消息(左右键)
    DWORD       time;	//消息产生的时间
    POINT       pt;		//附加消息 鼠标消息(位置) 
	
	*/

	while (1)
	{

		/*
			LPMSG lpMsg,	消息
			HWND  hWnd,		捕获窗口,NULL代表
			UINT  wMsgFilterMin,	最小和最大的过滤消息,0代表捕获所有消息
			UINT  wMsgFilterMax
		*/
		if (GetMessage(&msg, NULL, 0, 0) == FALSE) {//点X退出
			break;
		}
		//翻译消息 
		TranslateMessage(&msg);

		//其他消息分发
		DispatchMessage(&msg);

	}

	//处理窗口过程
	


	return 0;
}