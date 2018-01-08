// Minesweeper.cpp : Defines the entry point for the application.
#include "stdafx.h"
#include "Operations.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name
DWORD       dwStyle;							// Window Style
// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
					   _In_opt_ HINSTANCE hPrevInstance,
					   _In_ LPTSTR    lpCmdLine,
					   _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_MINESWEEPER, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MINESWEEPER));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}

//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MINESWEEPER));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_MINESWEEPER);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
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

	dwStyle=(WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX);

	hWnd = CreateWindow( szWindowClass, 
		szTitle, 
		dwStyle,//WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 
		0, 
		215,
		259,
		NULL,
		NULL,
		hInstance,
		NULL);

	fill_numbers();

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case ID_FILE_NEWGAME:
			new_game(hWnd);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;

	case WM_LBUTTONDOWN:
		{
			if (!Game_over)
			{
				hdc = GetDC(hWnd); 

				x=LOWORD(lParam);
				y=HIWORD(lParam);
				x=round(x);
				y=round(y);

				if (bombs[CellNumber(y)][CellNumber(x)]==1)
				{
					SelectObject(hdc,CreatePatternBrush(LoadBitmap(hInst,(const char*)IDBM_MINE)));
					Rectangle(hdc,x,y,x+SQURE_SIZE,y+SQURE_SIZE);
					Game_over=true;
					int msgboxID=MessageBox
						(hWnd,
						"Would you like to retry?",
						"Game over",
						MB_RETRYCANCEL|MB_ICONQUESTION|MB_DEFBUTTON1);
					switch (msgboxID)
					{
					case IDRETRY:
						new_game(hWnd);
						break;
					case IDCANCEL:
						break;
					}
				}

				else if (numbers[CellNumber(y)][CellNumber(x)]!=0)
				{
					been_here[CellNumber(y)][CellNumber(x)]=true;
					switch (numbers[CellNumber(y)][CellNumber(x)])
					{
					case 1:
						SelectObject(hdc,CreatePatternBrush(LoadBitmap(hInst, (const char*)IDBM_1)));
						Rectangle(hdc,x,y,x+SQURE_SIZE,y+SQURE_SIZE);
						break;
					case 2: 
						SelectObject(hdc,CreatePatternBrush(LoadBitmap(hInst, (const char*)IDBM_2)));
						Rectangle(hdc,x,y,x+SQURE_SIZE,y+SQURE_SIZE);
						break;
					case 3:
						SelectObject(hdc,CreatePatternBrush(LoadBitmap(hInst, (const char*)IDBM_3)));
						Rectangle(hdc,x,y,x+SQURE_SIZE,y+SQURE_SIZE);
						break;
					case 4:
						SelectObject(hdc,CreatePatternBrush(LoadBitmap(hInst, (const char*)IDBM_4)));
						Rectangle(hdc,x,y,x+SQURE_SIZE,y+SQURE_SIZE);
						break;
					case 5:
						SelectObject(hdc,CreatePatternBrush(LoadBitmap(hInst, (const char*)IDBM_5)));
						Rectangle(hdc,x,y,x+SQURE_SIZE,y+SQURE_SIZE);
						break;
					case 6:
						SelectObject(hdc,CreatePatternBrush(LoadBitmap(hInst, (const char*)IDBM_6)));
						Rectangle(hdc,x,y,x+SQURE_SIZE,y+SQURE_SIZE);
						break;
					case 7:
						SelectObject(hdc,CreatePatternBrush(LoadBitmap(hInst, (const char*)IDBM_7)));
						Rectangle(hdc,x,y,x+SQURE_SIZE,y+SQURE_SIZE);
						break;
					case 8:
						SelectObject(hdc,CreatePatternBrush(LoadBitmap(hInst, (const char*)IDBM_8)));
						Rectangle(hdc,x,y,x+SQURE_SIZE,y+SQURE_SIZE);
						break;
					default:
						break;
					}
				}

				else
				{recursive_draw(hdc,hInst,x,y);}
				ReleaseDC(hWnd, hdc);  
			}
			break;
		}
	case WM_RBUTTONDOWN:
		{
			if (!Game_over)
			{
				hdc = GetDC(hWnd);
				x=LOWORD(lParam);
				y=HIWORD(lParam);
				x=round(x);
				y=round(y);

				if (been_here[CellNumber(y)][CellNumber(x)]==false )
				{
					if (safe[CellNumber(y)][CellNumber(x)]==false )
					{

						safe[CellNumber(y)][CellNumber(x)]=true;
						SelectObject(hdc,CreatePatternBrush(LoadBitmap(hInst,(const char*)IDBM_SAFE)));
						Rectangle(hdc,x,y,x+SQURE_SIZE,y+SQURE_SIZE);

						if (bombs[CellNumber(y)][CellNumber(x)]==1)
						{
							Number_of_mines--;
							if (Number_of_mines==0)
							{
								Game_over=true;
								int msgboxID=MessageBox
									(hWnd,
									"Would you like to retry?",
									"You Won!",
									MB_RETRYCANCEL|MB_ICONEXCLAMATION|MB_DEFBUTTON1);
								switch (msgboxID)
								{
								case IDRETRY:
									new_game(hWnd);
									break;
								case IDCANCEL:
									break;
								}
							}
						}
					}

					else
					{
						safe[CellNumber(y)][CellNumber(x)]=false;
						SelectObject(hdc,CreatePatternBrush(LoadBitmap(hInst,(const char*)IDBM_UNCLICKED)));
						Rectangle(hdc,x,y,x+SQURE_SIZE,y+SQURE_SIZE);
						if (bombs[CellNumber(y)][CellNumber(x)]==1)
						{Number_of_mines++;}
					}
					ReleaseDC(hWnd, hdc); 
				} 
			}
			break; 
		}
	case WM_PAINT:
		{
			hdc = BeginPaint(hWnd, &ps);
			//Sets the default back of the window to the unselected brush
			SelectObject(hdc,CreatePatternBrush(LoadBitmap(hInst, (const char*)IDBM_UNCLICKED)));
			Rectangle(hdc,0,0,SQURE_SIZE*10,SQURE_SIZE*10);

			// Add any drawing code here...
			EndPaint(hWnd, &ps);
			break;
		}
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
