#include <iostream>

using namespace std;

namespace mynamespace
{
    bool TimePassesIsEnabled = true;


    bool TestFunction(void)
    {
        cout << "mynamespace::TestFunction() called" << endl;
        return true;
    }

}

