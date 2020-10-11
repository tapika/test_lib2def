#include "test1.h"
#include <iostream>

using namespace std;

int g_GlobalVar = 3;


namespace mynamespace
{
    bool DECLEXP TimePassesIsEnabled = true;

    bool DECLEXP TestFunction(void)
    {
        cout << "mynamespace::TestFunction() called" << endl;
        return true;
    }
}

