#include <iostream>
#include <windows.h>
#include <mysql.h>

#include "UI.h"
#include "dbActions.h"

#pragma comment(lib, "user32") //Fullscreen cmd

int main()
{
    ::SendMessage(::GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000); //Fullscreen cmd

    MYSQL* conn = sqlDefaultSetup(); //Start connection with default settings
    if(conn)
        mainMenu(conn);
    else
        std::cout << "Cannot connect to database. Check connection.\n";

    return 0;
}

