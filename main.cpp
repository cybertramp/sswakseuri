#include <windows.h>
#include <stdio.h>

#define BT1 10000	//버튼1

/* 이벤트 처리 */
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	HINSTANCE hInstance;


	switch(Message) {
		/* Upon destruction, tell the main thread to stop */
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			break;
		}

		case WM_CLOSE:	// 닫았을때 이벤트
			DestroyWindow(hwnd);
			break;

		case WM_PAINT:	// 텍스트 그림
			hdc=BeginPaint(hwnd,&ps);
			SetTextAlign(hdc, TA_LEFT);	// 텍스트 정렬
			TextOut(hdc,10,10," 토렌트임시파일제거 ",19);	// 문자열 출력 함수
			EndPaint(hwnd,&ps);	// 그리기 종료

		case WM_CREATE:
			CreateWindow("button","청소",WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			160,6,40,25,hwnd,(HMENU)BT1,hInstance,NULL);

		case WM_COMMAND:
	    	//만약 버튼이 눌렸을 때
			if (LOWORD(wParam) == BT1)
			{
		        MessageBeep(MB_OK);
		        system("del /f /s /q %appdata%\\uTorrent\\*.torrent");

				MessageBox(hwnd, "청소완료","알림",MB_OK);

		    }


		/* All other messages (a lot of them) are processed using default procedures */
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}



/* 그리기 설정 */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc; /* A properties struct of our window */
	HWND hwnd; /* A 'HANDLE', hence the H, or a pointer to our window */
	MSG msg; /* A temporary location for all messages */

	/* zero out the struct and set the stuff we want to modify */
	memset(&wc,0,sizeof(wc));
	wc.cbSize		 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc; /* This is where we will send messages to */
	wc.hInstance	 = hInstance;
	wc.hCursor		 = LoadCursor(NULL, IDC_ARROW);

	/* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it */
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wc.lpszClassName = "WindowClass";
	wc.hIcon		 = LoadIcon(NULL, IDI_APPLICATION); /* Load a standard icon */
	wc.hIconSm		 = LoadIcon(NULL, IDI_APPLICATION); /* use the name "A" to use the project icon */

	if(!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass","쏵쓸이 v1",WS_VISIBLE|WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, /* x */
		CW_USEDEFAULT, /* y */
		320, /* width */
		200, /* height */
		NULL,NULL,hInstance,NULL);

	if(hwnd == NULL) {
		MessageBox(NULL, "윈도우 창 만들기 실패","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	/*
		This is the heart of our program where all input is processed and
		sent to WndProc. Note that GetMessage blocks code flow until it receives something, so
		this loop will not produce unreasonably high CPU usage
	*/
	while(GetMessage(&msg, NULL, 0, 0) > 0) { /* If no error is received... */
		TranslateMessage(&msg); /* Translate key codes to chars if present */
		DispatchMessage(&msg); /* Send it to WndProc */
	}


	return msg.wParam;
}
