#pragma once

#ifdef EXPORT_VIA_DECLSPEC
    #ifdef TEST1
    #define DECLEXP __declspec(dllexport)
    #else
    #define DECLEXP __declspec(dllimport)
    #endif
#else
    #define DECLEXP
#endif

extern int DECLEXP g_GlobalVar;

namespace mynamespace
{
    extern DECLEXP bool TimePassesIsEnabled;

    bool DECLEXP TestFunction(void);
}

