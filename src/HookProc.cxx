#include <windows.h>
#include <winuser.h>
#include <iostream>
#include <ctime>
#include "console.h"

CONSOLE_INIT();

bool WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID)
{
    switch(dwReason)
    {
        case DLL_PROCESS_ATTACH:
            CONSOLE<<"DLL_PROCESS_ATTACH"<<ENDL;
            DisableThreadLibraryCalls(hInstance);
            CONSOLE.attach();
            break;
        case DLL_THREAD_ATTACH:
            CONSOLE<<"DLL_THREAD_ATTACH"<<ENDL;
            break;
        case DLL_PROCESS_DETACH:
            CONSOLE<<"DLL_PROCESS_DETACH"<<ENDL;
            break;
        case DLL_THREAD_DETACH:
            CONSOLE<<"DLL_THREAD_DETACH"<<ENDL;
            break;
        default:
            break;
    }
    return true;
}

__declspec(dllexport) LRESULT WINAPI KeyboardProc(int code, WPARAM wParam, LPARAM lParam)
{
    switch (wParam)
    {
        case WM_KEYDOWN:
            CONSOLE<<"\nWM_KEYDOWN"<<ENDL;
            break;
        case WM_KEYUP:
            CONSOLE<<"\nWM_KEYUP"<<ENDL;
            break;
        case WM_SYSKEYDOWN:
            CONSOLE<<"\nWM_SYSKEYDOWN"<<ENDL;
            break;
        case WM_SYSKEYUP:
            CONSOLE<<"\nWM_SYSKEYUP"<<ENDL;
            break;
        default:
            break;
    }

    KBDLLHOOKSTRUCT* pKBDLLHOOKSTRUCT = (KBDLLHOOKSTRUCT*)lParam;
    BYTE keyboardStat[256] = {0};
    WORD key;
    ToAscii(pKBDLLHOOKSTRUCT->vkCode,pKBDLLHOOKSTRUCT->scanCode,keyboardStat,&key,0);
    char* pChar=(char*)&key;
    for (auto keyItem:keyboardStat) CONSOLE<<HEX<<int(keyItem)<<',';
    CONSOLE<<ENDL;
    CONSOLE<<DEC<<pKBDLLHOOKSTRUCT->time<<": char1="<<pChar[0]<<", char2="<<pChar[1]<<", vkCode="<<HEX<<pKBDLLHOOKSTRUCT->vkCode
        <<", scanCode="<<pKBDLLHOOKSTRUCT->scanCode<<DEC<<ENDL;
    return CallNextHookEx(0, code, wParam, lParam); 
}
