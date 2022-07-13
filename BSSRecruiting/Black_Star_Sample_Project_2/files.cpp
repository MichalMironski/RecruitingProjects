#include <iostream>
#include <fstream>
#include <windows.h>

#include "files.h"

void restarting();
void filesFunction()
{
    system("cls");
    std::string source = "", destination = "", line = "";
    std::ifstream src;
    std::ofstream dst;

    std::cout << "Enter source:\n";
    std::getline(std::cin, source);
    try
    {
        src.open(source, std::ios::binary);
        if(!src) throw ( "Can't open source file!\nCheck source path and try again." );
    }
    catch (const char* err)
    {
        std::cerr << err << "\n";
        system("pause");
        filesFunction();
    }

    std::cout << "Enter destination. IF THERE IS A FILE WITH THE SAME NAME IT WILL BE OVERWRITTEN.\n";
    std::getline(std::cin, destination);
    dst.open(destination, std::ios::binary);

    if(src && dst)
    {
        while(getline(src, line))
            dst << line << "\n";
        std::cout << "File copied.\n";
    }
    else
    {
        std::cout << "Something went wrong. Check if path is correct.\n";
        system("pause");
        filesFunction();
    }



    src.close();
    dst.close();
}

//source: C:\Users\mmironsx\OneDrive - Intel Corporation\Desktop\test\t1\t5.rar
//dest: C:\Users\mmironsx\OneDrive - Intel Corporation\Desktop\test\t2\t5.rar
