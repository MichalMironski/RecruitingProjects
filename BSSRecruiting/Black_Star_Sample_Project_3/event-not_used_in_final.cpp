#include <iostream>
#include <string>

#include "event-not_used_in_final.h"

Event::Event()
{
    setName();
    setEventDate();
    setEventStart();
    setEventEnd();
    setDescription();
}

Event::~Event()
{

}

int Event::getDay() { return day; }
int Event::getMonth() { return month; }
int Event::getYear() { return year; }
int Event::getStartHours() { return shours; }
int Event::getStartMinutes() { return sminutes; }
int Event::getEndHours() { return ehours; }
int Event::getEndMinutes() { return eminutes; }
std::string Event::getName() { return name; }
std::string Event::getDescription() { return description;}
std::string Event::getDate()
{
    return std::to_string(Event::getYear()) + "/" + std::to_string(Event::getMonth()) + "/" + std::to_string(Event::getDay());
}

std::string Event::getStartTime()
{
    return std::to_string(Event::getStartHours()) + ":" + std::to_string(Event::getStartMinutes());
}

std::string Event::getEndTime()
{
    return std::to_string(Event::getEndHours()) + ":" + std::to_string(Event::getEndMinutes());
}

void Event::getAllInfo()
{
    std::cout << "Event name: " << getName() << "\n";
    std::cout << "Event date: " << getDate() << "\n";
    std::cout << "Event start time: " << getStartTime() << "\n";
    std::cout << "Event end time: " << getEndTime() << "\n";
    std::cout << "Event description: " << getDescription() << "\n";
}

void Event::setName()
{
    std::string n;
    std::cout << "Enter event name:  ";
    std::cin.ignore();
    std::getline(std::cin, n);
    name = n;
}

void Event::setDescription()
{
    std::string d;
    std::cout << "Enter event description: \n";
    std::cin.ignore();
    std::getline(std::cin, d);
    description = d;
}

void Event::setEventDate()
{
    unsigned int y, m, d; //year, month, day
    std::cout << "Enter year of event:  ";
    std::cin >> y;
    std::cout << "Enter month:  ";
    std::cin >> m;
    std::cout << "Enter day:  ";
    std::cin >> d;
    year = y;
    month = m;
    day = d;
}

void Event::setEventStart()
{
    unsigned int h, m; //hours, minutes;
    std::string s, th, tm; // string, temphour, tempminutes
    std::cout << "Enter event start time (HH:MM):   ";
    std::cin >> s;
    th = s.substr(0,2);
    tm = s.substr(3,2);
    shours = stoi(th);
    sminutes = stoi(tm);
}

void Event::setEventEnd()
{
    unsigned int h, m; //hours, minutes;
    std::string s, th, tm; // string, temphour, tempminutes
    std::cout << "Enter event end time (HH:MM):   ";
    std::cin >> s;
    th = s.substr(0,2);
    tm = s.substr(3,2);
    ehours= stoi(th);
    eminutes = stoi(tm);
}

bool is_integer(double d)
{
    if( d == (int)d ) return true;
    else return false;
}
