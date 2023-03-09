#ifndef _WIN32_NOTIFICATION_H_
#define _WIN32_NOTIFICATION_H_

#include <windef.h>
#include <shellapi.h>

class Win32Notification
{
public:
    Win32Notification(HWND hWnd, HICON hIcon, const wchar_t* tip)
        :nid({})
    {
        nid.cbSize = sizeof(nid);
        nid.hWnd = hWnd;
        nid.uFlags = NIF_ICON | NIF_TIP;
        nid.hIcon = hIcon;
        wcscpy(nid.szTip,tip);
        Shell_NotifyIcon(NIM_ADD, &nid);
    }
    ~Win32Notification()
    {
        Shell_NotifyIcon(NIM_DELETE, &nid);
    }
private:
    HICON hIcon;
    NOTIFYICONDATA nid;
};
#endif
