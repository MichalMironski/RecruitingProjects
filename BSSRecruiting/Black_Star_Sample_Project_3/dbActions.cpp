#include <iostream>
#include <iomanip>
#include <windows.h>
#include <mysql.h>
#include <sstream>

#include "event-not_used_in_final.h"

#define WALL (char(186)) //char used in presenting data from database

    /*
    Required data format: DD/MM/YYYY.
    First if return 0 when lenght of string s is not equal to 10.
    Second if returns 0 when day and month or monts and year aren't separated with char '/'
    Or when day or month or year is 0 only
    Third if returns 0 for exceptions like 30/02 etc. Every line have suitable comment
    For loop checks if all characters(except '/' - for i == 2 and 5) are numbers. If not also returns 0.
    */
int dataFormatCheck(std::string s) //Date must be saved in DD/MM/YYYY format
{
    if(s.length() != 10)
        return 0;

    if ( s[2] != '/' || s[5] != '/' || //Check if '/' is separator
       ( s[0] == '0' && s[1] == '0' ) || //Check if DD == 00
       ( s[3] == '0' && s[4] == '0' ) || //Check if MM == 00
       ( s[6] == '0' && s[7] == '0' && s[8] == '0' && s[9] == '0')) //Check if YYYY ==  0000
            return 0;

    if  ( int(s[3]) > 49 || //Check if first number of month isn't higher than 1
        ( s[3] == '1' && int(s[4]) > 50 ) || //Checks if when month starts with 1, second number isn't bigger than 2
        ( int(s[0]) > 51) || //Checks if first number of day isn't higher than 3
        ( int(s[0]) == '3' && int(s[1]) > 49) || //Check if when first number is 3, second isn't bigger than 1
        ( s[3] == '0' && s[4] == '2' && int(s[0]) > 50)) //Check for Fabruary, first number of days cant be bigger than 2
            return 0;

    for(int i = 0; i < s.length(); i++)
    {
        if( i == 2 || i == 5) //Skip separators
            continue;
        if( int(s[i]) < 47 || int(s[i]) > 57) //Check if data is build with numbers only
            return 0;
    }
    return 1;
}

    /*
    Required data format: HH:MM.
    First if returns 0 when lenght of string s is not equal to 5.
    Second if returns 0 when first number of hours is bigger than 2 or first minutes number is bigger than 5
    Third if returns 0 when hours and minutes are not separated with char ':'.
    For loop checks if all characters(except '/' - for i == 2) are numbers. If not also returns 0.
    */
int timeFormatCheck(std::string s)
{
    if(s.length() != 5) //Time should have length == 5
        return 0;
    if(int(s[0]) > 50 || int(s[3]) > 53)  //Check if first number of hours is not bigger than 2 or first number of minutes is not bigger than 5
        return 0;
    if( s[0] == '2' && int(s[1]) > 51) //If first number of hours is 2, second can't be bigger than 3
        return 0;
    if(s[2] != ':') //Separator check
        return 0;
    for(int i = 0; i < s.length(); i++)
    {
        if(i == 2) //Skip for separator
            continue;
        if( int(s[i]) < 47 || int(s[i]) > 57) //Check if hours and minutes are numbers only
            return 0;
    }

    return 1;
}

    /*
    Overload of int timeFormatCheck(std::string s)
    Works almost the same.
    Additionally checks if endTime is later than startTime
    */
int timeFormatCheck(std::string e, std::string s)
{
    int isLater = 0;
    if(e.length() != 5) //Time should have length == 5
        return 0;
    if(int(e[0]) > 50 || int(e[3]) > 53) //Check if first number of hours is not bigger than 2 or first number of minutes is not bigger than 5
        return 0;
    if( s[0] == '2' && int(s[1]) > 51) //If first number of hours is 2, second can't be bigger than 3
        return 0;
    if(e[2] != ':')
        return 0;
    for(int i = 0; i < e.length(); i++)
    {
        if(i == 2)
            continue;
        if( int(e[i]) < 47 || int(e[i]) > 57)
            return 0;
        if (isLater == 1) //If endTime is later, no need to check other number of time
            continue;
        if(e[i] > s[i] && isLater != -1) //If some endTime number is bigger than corresponding to him startTime number it is definitely later
            isLater = 1;
        else if(e[i] < s[i] && isLater == 0) //If some startNumber is bigger than corresponding to him endTime number, and isLater is still equal to 0, then startTime is later in time
            isLater = -1;
    }
    if(isLater == -1)
        return 0;

    return 1;
}

void printCurrentSetup(MYSQL* conn)
{
    std::cout << "Current MySQL settings: \n";
    std::cout << "Database name: " << conn -> db<< "\n";
    std::cout << "Database address: " << conn -> host << "\n";
    std::cout << "Login: " << conn -> user << "\n";
    std::cout << "Password: " << conn -> passwd << "\n\n";
}

MYSQL* changeSettings(MYSQL* conn)
{
    std::string newdbadress = " ", newdbname = " ", newuser = " ", newpassword = " ";
    MYSQL* newconn;

    std::cout << "Enter database ADDRESS:  ";
    std::cin >> newdbadress;
    std::cout << "Enter database NAME:  ";
    std::cin >> newdbname;
    std::cout << "Enter LOGIN:  ";
    std::cin >> newuser;
    std::cout << "Enter PASSWORD:  ";
    std::cin >> newpassword;

    newconn = mysql_init(0);
    newconn = mysql_real_connect(newconn, newdbadress.c_str(), newuser.c_str(), newpassword.c_str(), newdbname.c_str(), 0, NULL, 0);
    if(newconn)
    {
        std::cout << "Connected. Settings will be changed.\n";
        system("pause");
        return newconn;
    }
    else
    {
        std::cout << "Cannot connect to given database. Check if data is correct\nEarlier settings will not be changed.\n";
        system("pause");
        return conn;
    }
}

void printAllEvents(MYSQL* conn)
{
    MYSQL_ROW rows;
    MYSQL_RES* res;
    int i = 0;
    std::stringstream dateAndTime; //String stream to correctly print time
    int query = mysql_query(conn, "SELECT id,name,date,startTime,endTime,description FROM `planner`"); // query = 0 if everything went well
    if(!query)
    {
        res = mysql_store_result(conn);
        while( rows = mysql_fetch_row(res) )
        {
            std::cout.fill(' ');
            dateAndTime << rows[2] << "   " << rows[3] << " - " << rows[4];

            std::cout << WALL << std::setw(8) << "ID: " << std::setw(3)<<rows[0] << WALL << std::setw(60) << rows[1] << WALL <<"\n"; //ID
            std::cout << WALL << std::setw(11) << "Date" << WALL << std::setw(60) <<dateAndTime.str() << WALL << "\n";
            std::cout << WALL << std::setw(11) << "Description" << WALL << std::setw(60) << rows[5] << WALL << "\n";
            std::cout << WALL;
            std::cout.width(73);
            std::cout << WALL;
            std::cout << "\n";
            std::cout << WALL;
            std::cout.width(73);
            std::cout << WALL;
            std::cout << "\n";

            dateAndTime.str(""); //Clearing stringstream for next iteration
        }
    }
}


void addNewEvent(MYSQL* conn)
{
    int querystate = 0;
    std::string name, date, startTime, endTime, description, query;
    std::stringstream ss;

    std::cin.ignore();
    std::cout << "Enter events name: ";
    do {
        std::getline(std::cin, name);
        if(name.length() > 60)
            std::cout << "Events name is too long(Max 60 characters). Try again.\n";
    } while (name.length() > 60);

    std::cout << "Enter events date: ";
    do {
        std::getline(std::cin, date);
        if(dataFormatCheck(date) != 1)
            std::cout << "Invalid date format. Required format is DD/MM/YYYY. Try again.\n";
    } while (dataFormatCheck(date) != 1);


    std::cout << "Enter events start time: ";
    do {
        std::getline(std::cin, startTime);
        if(timeFormatCheck(startTime) != 1)
            std::cout << "Invalid time format or invalid data. Required format is HH:MM. Try again.\n";
    } while (timeFormatCheck(startTime) != 1);

    std::cout << "Enter events end time: ";
    do {
        std::getline(std::cin, endTime);
        if(timeFormatCheck(endTime, startTime) != 1)
            std::cout << "Invalid date format or invalid data. Required format is HH:MM. Make sure that end time is later than start time. Try again.\n";
    } while (timeFormatCheck(endTime, startTime) != 1);


    std::cout << "Enter events description: ";
    do {
        std::getline(std::cin, description);
        if(description.length() > 60)
            std::cout << "Events description is too long(Max 60 characters). Try again.\n";
    } while (description.length() > 60);


    ss << "INSERT INTO planner(name,date,startTime,endTime,description) VALUES('"<<name<<"','"<< date << "','"<< startTime << "','"<< endTime << "','"<< description << "')";

    query = ss.str(); //Converting stringstream to string - it allows to use c_str() function on it
    querystate = mysql_query(conn, query.c_str());
    if(!querystate) //mysql_query() returns 0 when no problems were encountered
    {
        std::cout << "Event created!\n";
        system("pause");
    }
    else
    {
        std::cout << "Something went wrong. Event will not be created.\n";
        system("pause");
    }

}

void editEvent(MYSQL* conn) //Comments match those from the addNewEvent() function
{
    int querystate = 0, eventId = 0;
    std::string eName, eDate, eStartTime, eEndTime, eDescription, query; // e - edited
    std::stringstream ss;

    printAllEvents(conn);
    std::cout << "\n\nWhich event do you want to change? Enter ID.\n";
    std::cin >> eventId;

    std::cin.ignore();
    std::cout << "Enter events new name: ";
    do {
        std::getline(std::cin, eName);
        if(eName.length() > 60)
            std::cout << "Events name is too long(Max 60 characters). Try again.\n";
    } while (eName.length() > 60);

    std::cout << "Enter events new date: ";
    do {
        std::getline(std::cin, eDate);
        if(dataFormatCheck(eDate) != 1)
            std::cout << "Invalid date format. Required format is DD/MM/YYYY. Try again.\n";
    } while (dataFormatCheck(eDate) != 1);

    std::cout << "Enter events start new time: ";
    do {
        std::getline(std::cin, eStartTime);
        if(timeFormatCheck(eStartTime) != 1)
            std::cout << "Invalid time format or invalid data. Required format is HH:MM. Try again.\n";
    } while (timeFormatCheck(eStartTime) != 1);

    std::cout << "Enter events end new time: ";
    do {
        std::getline(std::cin, eEndTime);
        if(timeFormatCheck(eEndTime, eStartTime) != 1)
            std::cout << "Invalid date format or invalid data. Required format is HH:MM. Make sure that end time is later than start time. Try again.\n";
    } while (timeFormatCheck(eEndTime, eStartTime) != 1);

    std::cout << "Enter events new description: ";
    do {
        std::getline(std::cin, eDescription);
        if(eDescription.length() > 60)
            std::cout << "Events description is too long(Max 60 characters). Try again.\n";
    } while (eDescription.length() > 60);

    ss << "UPDATE planner SET name = '" << eName << "', date = '" << eDate << "', startTime = '" << eStartTime << "', endTime = '" << eEndTime << "', description = '" << eDescription << "' WHERE id = " << eventId;
    query = ss.str();
    querystate = mysql_query(conn, query.c_str());
    if(!querystate)
    {
        std::cout << "Event edited!\n";
        system("pause");
    }
    else
    {
        std::cout << "Something went wrong. Event will not be edited.\n";
        system("pause");
    }
}

void deleteEvent(MYSQL* conn)
{
    int querystate = 0, eventId = 0;
    std::string eName, eDate, eStartTime, eEndTime, eDescription, query; // e - edited
    std::stringstream ss;

    printAllEvents(conn);
    std::cout << "\n\nChoose id of element that you want delete\n";
    std::cin >> eventId;

    ss << "DELETE FROM planner WHERE id = " << eventId;
    query = ss.str();
    querystate = mysql_query(conn, query.c_str());
    if(!querystate)
    {
        std::cout << "Event deleted!\n";
        system("pause");
    }
    else
    {
        std::cout << "Something went wrong. Event will not be edited.\n";
        system("pause");
    }
}

MYSQL* sqlDefaultSetup()
{
    //Default settings, program starts with them
    std::string dbadress = "127.0.0.1", dbname = "bs_planner", user = "admin",
                password = "admin";

    MYSQL* conn;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn, dbadress.c_str(), user.c_str(), password.c_str(),
                              dbname.c_str(), 0, NULL, 0);

    if(conn)
        return conn;
    else
        return NULL;
}
