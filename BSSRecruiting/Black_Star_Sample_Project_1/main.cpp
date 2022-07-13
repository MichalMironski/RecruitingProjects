#include <iostream>
#include <cstdlib>
#include <windows.h>

#include "matrix.h"
#include "otherFunctions.h"
#include "UI.h"

#pragma comment(lib, "user32") //Fullscreen cmd

int main()
{
    ::SendMessage(::GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000); //Fullscreen cmd

    initializeMatrices();

    return 0;
}
