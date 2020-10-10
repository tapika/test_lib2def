#include "test1.h"
#include <iostream>

using namespace std;

void main(void)
{
    cout << llvm::TimePassesIsEnabled;

    llvm::TimePassesIsEnabled = false;
    
    cout << llvm::TimePassesIsEnabled;

}