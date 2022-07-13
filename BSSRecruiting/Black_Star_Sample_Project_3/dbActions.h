#include <iostream>
#include <windows.h>
#include <mysql.h>

void printCurrentSetup(MYSQL*); //Printing current MySQL configuration
void printAllEvents(MYSQL*); //Printing all event from database
void addNewEvent(MYSQL*); //Add new event to database
void editEvent(MYSQL*); //Edit event from database
void deleteEvent(MYSQL*); //Delete event from database
int dataFormatCheck(std::string); //Check if data is in correct format
int timeFormatCheck(std::string); //Check if time is in correct format
int timeFormatCheck(std::string, std::string); //Check if time is in correct format and endTime is later than startTime
MYSQL* changeSettings(MYSQL*); //Change connection settings
MYSQL* sqlDefaultSetup(); //Load default setup
