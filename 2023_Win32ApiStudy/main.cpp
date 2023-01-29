// main.cpp : 애플리케이션에 대한 진입점을 정의합니다.

#include "framework.h"
#include "main.h"

#include <vector>

using namespace std;

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                     // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];       // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING]; // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,         // 현재 실행 된 프로세스의 시작 주소
                      _In_opt_ HINSTANCE hPrevInstance,
                      _In_ LPWSTR lpCmdLine,
                      _In_ int nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MY2023WIN32APISTUDY, szWindowClass, MAX_LOADSTRING);

    // 윈도우 정보 등록
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    // 단축키 테이블 정보 로딩
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY2023WIN32APISTUDY));

    // 기본 메시지 루프입니다:
    // 1. GetMessage
    // - 메세지 큐에서 메세지가 확인될 때까지 대기한다.
    // - msg.messge == WM_QUIT인 경우, false를 반환한다.(프로그램을 종료한다.)
    //
    // 2. PeekMessage
    // - 메세지 큐에 메세지의 유무와 관계 없이 대기하지 않는다.
    // - 메세지가 있을 경우 true, 없을 경우 false를 반환한다.
    MSG msg;

    while (true)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
            {
                break;
            }

            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {
            // 메세지가 없는 경우 호출
        }
    }

    return (int)msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY2023WIN32APISTUDY));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_MY2023WIN32APISTUDY);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}



//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석: 이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고 주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    // 인스턴스 핸들을 전역 변수에 저장합니다.
    hInst = hInstance;

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}



struct OBJECT
{
    POINT m_position;
    SIZE  m_size;
};

struct MOUSE_INFO
{
    bool  m_isPressed;

    POINT m_oldPosition;
    POINT m_newPosition;
};

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static vector<OBJECT> objects;
    static MOUSE_INFO mouseInfo = {};

    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);

            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT: // 무효화 영역(Invalidate Rect)이 발생한 경우
        {
            PAINTSTRUCT ps;

            // <디바이스 컨택스트(Device Context)>
            // - 그리기를 위한 도구들을 담는 집합체이자 대상
            // - DC의 목적지는 hwnd
            // - DC 기본 펜의 색상은 black
            // - DC 기본 브러쉬의 색상은 white

            // DC를 만든 후 ID 값을 반환한다.
            HDC hdc = BeginPaint(hWnd, &ps);

            // 직접 펜과 브러쉬를 만들어서 DC에 설정해보자.
            // 자주 쓰는 색상의 펜과 브러쉬는 GetStockObject() 함수를 이용할 수 있다.
            HPEN hPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
            HBRUSH hBrush = CreateSolidBrush(RGB(0, 255, 0));

            // 만든 펜과 브러쉬로 설정하고, 기존에 사용하던 펜과 브러쉬를 리턴 받아 저장해 놓는다.
            HPEN hDefaultPen = (HPEN)SelectObject(hdc, hPen);
            HBRUSH hDefaultBrush = (HBRUSH)SelectObject(hdc, hBrush);

            if (mouseInfo.m_isPressed)
            {
                Rectangle(hdc, mouseInfo.m_oldPosition.x, mouseInfo.m_oldPosition.y, mouseInfo.m_newPosition.x, mouseInfo.m_newPosition.y);
            }

            for (const auto& object : objects)
            {
                Rectangle(hdc, object.m_position.x - object.m_size.cx / 2, object.m_position.y - object.m_size.cy / 2, object.m_position.x + object.m_size.cx / 2, object.m_position.y + object.m_size.cy / 2);
            }

            // DC의 펜과 브러쉬를 원래대로 되돌린다.
            SelectObject(hdc, hDefaultPen);
            SelectObject(hdc, hDefaultBrush);

            // 다 쓴 펜과 브러쉬를 삭제한다.
            DeleteObject(hPen);
            DeleteObject(hBrush);

            // 그리기를 종료한다.
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_KEYDOWN:
    {
        // 눌린 키보드 값에 대한 단서는 wParam에 저장되어 있다.
        switch (wParam)
        {
        case VK_UP:
            break;
        case VK_DOWN:
            break;
        case VK_LEFT:
            break;
        case VK_RIGHT:
            break;
        }

        // 강제로 무효화 영역을 발생시킨다.
        InvalidateRect(hWnd, nullptr, true);
    }
        break;
    case WM_LBUTTONDOWN:
    {
        mouseInfo.m_isPressed = true;

        // 눌린 마우스 값에 대한 단서는 lParam에 저장되어 있다.
        mouseInfo.m_oldPosition.x = LOWORD(lParam);
        mouseInfo.m_oldPosition.y = HIWORD(lParam);
    }
        break;
    case WM_MOUSEMOVE:
    {
        mouseInfo.m_newPosition.x = LOWORD(lParam);
        mouseInfo.m_newPosition.y = HIWORD(lParam);

        InvalidateRect(hWnd, nullptr, true);
    }
        break;
    case WM_LBUTTONUP:
    {
        OBJECT object = {};

        object.m_position.x = (mouseInfo.m_oldPosition.x + mouseInfo.m_newPosition.x) / 2;
        object.m_position.y = (mouseInfo.m_oldPosition.y + mouseInfo.m_newPosition.y) / 2;
        object.m_size.cx = abs(mouseInfo.m_oldPosition.x - mouseInfo.m_newPosition.x);
        object.m_size.cy = abs(mouseInfo.m_oldPosition.y - mouseInfo.m_newPosition.y);

        objects.push_back(object);

        mouseInfo.m_isPressed = false;

        InvalidateRect(hWnd, nullptr, true);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}



// 정보 대화 상자의 메시지 처리기입니다.
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
