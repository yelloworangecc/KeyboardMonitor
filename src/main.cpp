#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>
#include <winuser.h>
#include <cstring>
#include <vector>
#include "console.h"
#include "win32Notification.h"

CONSOLE_INIT();

#define NOT_DEFINED "NOT_DEFINED"
std::vector<std::string> msgPrintName = {
    "WM_NULL","WM_CREATE","WM_DESTROY","WM_MOVE",
    "NOT DEFINED","WM_SIZE","WM_ACTIVATE","WM_SETFOCUS",
    "WM_KILLFOCUS",NOT_DEFINED,"WM_ENABLE","WM_SETREDRAW",
    "WM_SETTEXT","WM_GETTEXT","WM_GETTEXTLENGTH","WM_PAINT",
    "WM_CLOSE","WM_QUERYENDSESSION","WM_QUIT","WM_QUERYOPEN",
    "WM_ERASEBKGND","WM_SYSCOLORCHANGE","WM_ENDSESSION",NOT_DEFINED,
    "WM_SHOWWINDOW",NOT_DEFINED,"WM_SETTINGCHANGE | WM_WININICHANGE","WM_DEVMODECHANGE",
    "WM_ACTIVATEAPP","WM_FONTCHANGE","WM_TIMECHANGE","WM_CANCELMODE",
    "WM_SETCURSOR","WM_MOUSEACTIVATE","WM_CHILDACTIVATE","WM_QUEUESYNC",
    "WM_GETMINMAXINFO",NOT_DEFINED,"WM_PAINTICON","WM_ICONERASEBKGND",
    "WM_NEXTDLGCTL",NOT_DEFINED,"WM_SPOOLERSTATUS","WM_DRAWITEM",
    "WM_MEASUREITEM","WM_DELETEITEM","WM_VKEYTOITEM","WM_CHARTOITEM",
    "WM_SETFONT","WM_GETFONT","WM_SETHOTKEY","WM_GETHOTKEY",
    NOT_DEFINED,NOT_DEFINED,NOT_DEFINED,"WM_QUERYDRAGICON",
    "WM_COMPAREITEM",NOT_DEFINED,NOT_DEFINED,NOT_DEFINED,
    NOT_DEFINED,"WM_GETOBJECT",NOT_DEFINED,NOT_DEFINED,
};

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    if (uMsg >= msgPrintName.size()) CONSOLE<<"MSG ID:"<<HEX<<uMsg<<ENDL;
    else CONSOLE << "MSG NAME:" << msgPrintName[uMsg] << ENDL;

    switch (uMsg)
    {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        default:
            break;
    }
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    CONSOLE.attach();

    // Register the window class.
    const wchar_t CLASS_NAME[]  = L"Main Window Class";
    HICON icon = LoadIcon(hInstance, L"ID_ICON_APP");
    
    WNDCLASSEX wc = { };
    wc.cbSize = sizeof(wc);
    wc.lpfnWndProc   = WindowProc;
    wc.hInstance     = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hIcon = icon;

    RegisterClassEx(&wc);

    HWND hWnd = CreateWindowEx(
        0,                              // Optional window styles.
        CLASS_NAME,                     // Window class
        L"Keyboard Monitor",    // Window text
        WS_OVERLAPPEDWINDOW,            // Window style
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, // Size and positio
        NULL,       // Parent window    
        NULL,       // Menu
        hInstance,  // Instance handle
        NULL        // Additional application data
        );

    RECT clientRect;
    GetClientRect(hWnd, &clientRect);

    HWND hTextBox = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        L"EDIT",
        L"",
        WS_VSCROLL|WS_VISIBLE|WS_CHILD|ES_AUTOVSCROLL|ES_MULTILINE,
        clientRect.left, clientRect.top, clientRect.right-clientRect.left, clientRect.bottom-clientRect.top,
        hWnd,
        NULL,
        hInstance,
        NULL
        );
    SendMessage(hTextBox,EM_SETREADONLY,1,0);
    std::wstring text = L"Keyboard record start:";
    SetWindowText(hTextBox, text.c_str());
    ShowWindow(hWnd, true);
    
    //SetFocus(hTextBox);

    HOOKPROC hookProc;
    HINSTANCE instDLL;
    HHOOK hhook;

    instDLL = LoadLibrary(TEXT("HookProc.dll"));
    hookProc = (HOOKPROC)GetProcAddress(instDLL, "?KeyboardProc@@YA_JH_K_J@Z");

    hhook = SetWindowsHookEx(
        WH_KEYBOARD_LL,
        hookProc,
        instDLL,
        0);

    // Add notification area icon
    Win32Notification notifi(hWnd, icon,L"test");

    // Run the message loop.
    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
