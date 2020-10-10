#pragma once

//#define EXPORT_VIA_DECLSPEC

#ifdef EXPORT_VIA_DECLSPEC
    #ifdef TEST1
    #define DECLEXP __declspec(dllexport)
    #else
    #define DECLEXP __declspec(dllimport)
    #endif
#else
    #define DECLEXP
#endif

namespace mynamespace
{
    extern DECLEXP bool TimePassesIsEnabled;

    bool TestFunction(void);
}

