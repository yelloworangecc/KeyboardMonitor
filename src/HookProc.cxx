#include <windows.h>
#include <winuser.h>
#include <iostream>
 
#define EOF (-1)
 
#ifdef __cplusplus    // If used by C++ code, 
extern "C" {          // we need to export the C interface
#endif

__declspec(dllexport) LRESULT KeyboardProc(int code, WPARAM wParam, LPARAM lParam)
{
    std::cout<<"code="<<code<<",wParam="<<wParam<<",lParam="<<lParam<<std::endl;
    switch (wParam)
    {
        case WM_KEYDOWN:
            std::cout<<"WM_KEYDOWN"<<std::endl;
            break;
        case WM_KEYUP:
            std::cout<<"WM_KEYUP"<<std::endl;
            break;
        case WM_SYSKEYDOWN:
            std::cout<<"WM_SYSKEYDOWN"<<std::endl;
            break;
        case WM_SYSKEYUP:
            std::cout<<"WM_SYSKEYUP"<<std::endl;
            break;
        default:
            break;
    }

    KBDLLHOOKSTRUCT* pKBDLLHOOKSTRUCT = (KBDLLHOOKSTRUCT*)lParam;
    std::cout<<"vkCode="<<pKBDLLHOOKSTRUCT->vkCode<<std::endl;
    std::cout<<"scanCode="<<pKBDLLHOOKSTRUCT->scanCode<<std::endl;
    return CallNextHookEx(0, code, wParam, lParam); 
}
 
#ifdef __cplusplus
}
#endif
