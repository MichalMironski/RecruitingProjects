#include <iostream>
#include <windows.h>
#include <mysql.h>

#include "UI.h"
#include "dbActions.h"

void plannerMenu(MYSQL*);
void settingsMenu(MYSQL*);

void mainMenu(MYSQL* conn)
{
    char mainMenuChoice = ' ';
    std::cout << "Menu\n";
    std::cout << "1. Planner\n";
    std::cout << "2. Settings\n";
    std::cout << "0. Exit\n";
    std::cin >> mainMenuChoice;
    switch(mainMenuChoice)
    {
    case '1':
        system("cls");
        plannerMenu(conn);
        break;
    case '2':
        system("cls");
        settingsMenu(conn);
        break;
    case '0':
        system("exit");
        break;
    default:
        system("cls");
        std::cout << "Choose correct number.\n\n";
        mainMenu(conn);
    }
}

void plannerMenu(MYSQL* conn)
{
    system("cls");

    char plannerMenuChoice = ' ';
    if(!conn)
    {
        system("cls");
        std::cout << "Something went wrong. Check connection to database.\n\n";
        mainMenu(conn);
    }
    else
    {
        std::cout << "1. Show my events.\n";
        std::cout << "2. Add new event.\n";
        std::cout << "3. Edit event.\n";
        std::cout << "4. Delete event.\n";
        std::cout << "5. Go back to main menu.\n";
        std::cin >> plannerMenuChoice;

        switch(plannerMenuChoice)
        {
        case '1':
            system("cls");
            printAllEvents(conn);
            system("pause");
            plannerMenu(conn);
            break;
        case '2':
            system("cls");
            addNewEvent(conn);
            plannerMenu(conn);
            break;
        case '3':
            system("cls");
            editEvent(conn);
            plannerMenu(conn);
            break;
        case '4':
            system("cls");
            deleteEvent(conn);
            plannerMenu(conn);
            break;
        case '5':
            system("cls");
            mainMenu(conn);
            break;
        default:
            system("cls");
            std::cout << "Choose correct option.\n\n";
            plannerMenu(conn);
            break;
        }
    }
}

void settingsMenu(MYSQL* conn)
{
    char settingMenuChoice = ' ';
    printCurrentSetup(conn);

    std::cout << "1. Change settings.\n";
    std::cout << "2. Back.\n";

    std::cin >> settingMenuChoice;
    switch(settingMenuChoice)
    {
    case '1':
        conn = changeSettings(conn);
        system("cls");
        settingsMenu(conn);
        break;
    case '2':
        system("cls");
        mainMenu(conn);
        break;
    default:
        system("cls");
        std::cout << "Pick correct option.\n\n";
        settingsMenu(conn);
        break;
    }
}
