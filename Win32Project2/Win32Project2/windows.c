#include <windows.h>

//6.�����ڹ���
LRESULT CALLBACK  CallWindowProcA(
	HWND    hWnd,	//��Ϣ�����Ĵ��ھ��
	UINT    uMsg,	//��Ϣ����, WM_XXXX ��Ϣ��
	WPARAM  wParam,	//����
	LPARAM  lParam	//���
) {
	//����ֵĬ�ϴ���ʽ

	switch (uMsg)
	{
	case WM_CLOSE:
		//xxxWindwos()�ķ������������Ϣ����,����ֱ��ִ��
		DestroyWindow(hWnd); //��������һ����Ϣ WM_DESTROY
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	
	case WM_LBUTTONDOWN: //����������
	{
		int xPos = LOWORD(lParam);
		int yPos = HIWORD(lParam);

		char buf[1024];
		wsprintf(buf, TEXT("x=%d,y=%d"), xPos, yPos);
		MessageBox(hWnd, buf, TEXT("����������"), MB_OK);


		break;
	}

	case WM_KEYDOWN:
	{
		MessageBox(hWnd, TEXT("���̰���"), TEXT("���̰���"), MB_OK);
		break;
	}
	case WM_PAINT:	//��ͼ
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

	//1.��ƴ���
	WNDCLASS wc;
	wc.cbClsExtra = 0; //��Ķ������cun
	wc.cbWndExtra = 0;	//���ڶ����ڴ�
	wc.hbrBackground =(HBRUSH) GetStockObject(WHITE_BRUSH); //���ñ���
	wc.hCursor = LoadCursor(NULL,IDC_HAND);
	wc.hIcon = LoadCursor(NULL, IDC_ARROW);
	wc.hInstance = hInstance;
	wc.lpfnWndProc = CallWindowProcA; //���ڹ���;
	wc.lpszClassName = TEXT("WIN");  //ָ�����ڵ�������
	wc.lpszMenuName = NULL; 
	wc.style = 0;
	

	//2.ע�ᴰ����
	RegisterClass(&wc);
		

	//3.��������
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

	//4. ��ʾ����
	ShowWindow(hwnd, SW_SHOWNORMAL);
	UpdateWindow(hwnd);


	//5.ͨ��ѭ��ȡ��Ϣ
	MSG msg;

	/*
	 HWND        hwnd;	//�����ھ��
    UINT        message;	//��Ϣ����
    WPARAM      wParam;	//������Ϣ
    LPARAM      lParam;	//�����Ϣ(���Ҽ�)
    DWORD       time;	//��Ϣ������ʱ��
    POINT       pt;		//������Ϣ �����Ϣ(λ��) 
	
	*/

	while (1)
	{

		/*
			LPMSG lpMsg,	��Ϣ
			HWND  hWnd,		���񴰿�,NULL����
			UINT  wMsgFilterMin,	��С�����Ĺ�����Ϣ,0������������Ϣ
			UINT  wMsgFilterMax
		*/
		if (GetMessage(&msg, NULL, 0, 0) == FALSE) {//��X�˳�
			break;
		}
		//������Ϣ 
		TranslateMessage(&msg);

		//������Ϣ�ַ�
		DispatchMessage(&msg);

	}

	//�����ڹ���
	


	return 0;
}