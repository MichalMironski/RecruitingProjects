#include <iostream>
#include <windows.h>
#include <mysql.h>


void mainMenu(MYSQL* conn); //Display main menu in cmd
void plannerMenu(); //Display functions available to use on database called 'planner'
void settingsMenu(MYSQL* conn); //Display current configuration of mysql connection and gives option to change it
