#include <windows.h>
#include <string.h>
#include "internal.h"
#include "comctl32.h"

#ifndef OCM__BASE      /* avoid including olectl.h */
#define OCM__BASE (WM_USER+0x1c00)
#endif

COMCTL32_SysColor comctl32_color;

LPVOID WINAPI Alloc(DWORD cb) __WINE_ALLOC_SIZE(1)
{
    return malloc(cb);
}

LPVOID WINAPI ReAlloc(LPVOID ptr, DWORD cb) __WINE_ALLOC_SIZE(2)
{
    return realloc(ptr, cb);
}

BOOL   WINAPI Free(LPVOID ptr)
{
    free(ptr);
}

DWORD  WINAPI GetSize(LPVOID ptr)
{
    return (DWORD)_msize(ptr);
}

/***********************************************************************
 * COMCTL32_RefreshSysColors [NOT AN API]
 *
 * Invoked on any control recognizing a WM_SYSCOLORCHANGE message to
 * refresh the color values in the color structure
 *
 * PARAMS
 *     none
 *
 * RETURNS
 *     none
 */

VOID
COMCTL32_RefreshSysColors(void)
{
    comctl32_color.clrBtnHighlight = GetSysColor (COLOR_BTNHIGHLIGHT);
    comctl32_color.clrBtnShadow = GetSysColor (COLOR_BTNSHADOW);
    comctl32_color.clrBtnText = GetSysColor (COLOR_BTNTEXT);
    comctl32_color.clrBtnFace = GetSysColor (COLOR_BTNFACE);
    comctl32_color.clrHighlight = GetSysColor (COLOR_HIGHLIGHT);
    comctl32_color.clrHighlightText = GetSysColor (COLOR_HIGHLIGHTTEXT);
    comctl32_color.clrHotTrackingColor = GetSysColor (COLOR_HOTLIGHT);
    comctl32_color.clr3dHilight = GetSysColor (COLOR_3DHILIGHT);
    comctl32_color.clr3dShadow = GetSysColor (COLOR_3DSHADOW);
    comctl32_color.clr3dDkShadow = GetSysColor (COLOR_3DDKSHADOW);
    comctl32_color.clr3dFace = GetSysColor (COLOR_3DFACE);
    comctl32_color.clrWindow = GetSysColor (COLOR_WINDOW);
    comctl32_color.clrWindowText = GetSysColor (COLOR_WINDOWTEXT);
    comctl32_color.clrGrayText = GetSysColor (COLOR_GRAYTEXT);
    comctl32_color.clrActiveCaption = GetSysColor (COLOR_ACTIVECAPTION);
    comctl32_color.clrInfoBk = GetSysColor (COLOR_INFOBK);
    comctl32_color.clrInfoText = GetSysColor (COLOR_INFOTEXT);
}

/***********************************************************************
 * COMCTL32_IsReflectedMessage [internal]
 *
 * Some parents reflect notify messages - for some messages sent by the child,
 * they send it back with the message code increased by OCM__BASE (0x2000).
 * This allows better subclassing of controls. We don't need to handle such
 * messages but we don't want to print ERRs for them, so this helper function
 * identifies them.
 *
 * Some of the codes are in the CCM_FIRST..CCM_LAST range, but there is no
 * collision with defined CCM_ codes.
 */
BOOL COMCTL32_IsReflectedMessage(UINT uMsg)
{
    switch (uMsg)
    {
        case OCM__BASE + WM_COMMAND:
        case OCM__BASE + WM_CTLCOLORBTN:
        case OCM__BASE + WM_CTLCOLOREDIT:
        case OCM__BASE + WM_CTLCOLORDLG:
        case OCM__BASE + WM_CTLCOLORLISTBOX:
        case OCM__BASE + WM_CTLCOLORMSGBOX:
        case OCM__BASE + WM_CTLCOLORSCROLLBAR:
        case OCM__BASE + WM_CTLCOLORSTATIC:
        case OCM__BASE + WM_DRAWITEM:
        case OCM__BASE + WM_MEASUREITEM:
        case OCM__BASE + WM_DELETEITEM:
        case OCM__BASE + WM_VKEYTOITEM:
        case OCM__BASE + WM_CHARTOITEM:
        case OCM__BASE + WM_COMPAREITEM:
        case OCM__BASE + WM_HSCROLL:
        case OCM__BASE + WM_VSCROLL:
        case OCM__BASE + WM_PARENTNOTIFY:
        case OCM__BASE + WM_NOTIFY:
            return TRUE;
        default:
            return FALSE;
    }
}

BOOL IsSysLinkRegistered(HINSTANCE hinstDLL)
{
    WNDCLASSEXW wcx;
    if (GetClassInfoExW(NULL, L"SysLink", &wcx))
        return TRUE;
    if (GetClassInfoExW(GetModuleHandleW(L"comctl32"), L"SysLink", &wcx))
        return TRUE;
    if (GetClassInfoExW(hinstDLL, L"SysLink", &wcx))
        return TRUE;
    return FALSE;
}

BOOL WINAPI
DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    static BOOL s_bDoWorkaround;
    switch (fdwReason)
    {
    case DLL_PROCESS_ATTACH:
        COMCTL32_RefreshSysColors();
        s_bDoWorkaround = !IsSysLinkRegistered(hinstDLL);
        if (s_bDoWorkaround)
        {
            SYSLINK_Register();
        }
        break;
    case DLL_PROCESS_DETACH:
        if (s_bDoWorkaround)
        {
            SYSLINK_Unregister();
        }
        break;
    }
    return TRUE;
}
