#include <windows.h>
#include <stdio.h>
#include "os.h"

typedef LONG (WINAPI * RtlGetVersionPtr) (PRTL_OSVERSIONINFOW);

const char * get_os_name()
{
    HMODULE hMod = GetModuleHandleW(L"ntdll.dll");
    if (!hMod)
    {
        perror("Cannot load htdll.dll\n");
        return NULL;
    }

    RtlGetVersionPtr fxPtr = (RtlGetVersionPtr)GetProcAddress(hMod, "RtlGetVersion");
    if (!fxPtr)
    {
        perror("Cannot find RtlGetVersion function\n");
        return NULL;
    }

    RTL_OSVERSIONINFOW rovi = {0};
    rovi.dwOSVersionInfoSize = sizeof(rovi);

    static char name[128] = {0};
    if (fxPtr(&rovi) == 0)
    {
        snprintf(name, sizeof(name), "Windows %lu.%lu.%lu", 
                rovi.dwMajorVersion, 
                rovi.dwMinorVersion, 
                rovi.dwBuildNumber);

        return name;
    }

    perror("Cannot recognise system.\n");
    return NULL;
}

