#include <iostream>


class Event
{
private:
    std::string name, description;
    unsigned int year, month, day, shours, sminutes, ehours, eminutes;
public:
    Event(); //constructor
    ~Event(); //desctructor

    //getters
    std::string getName();
    std::string getDescription();
    std::string getDate(); //Function returns date in YYYY/MM/DD format
    std::string getStartTime(); //Function return time HH:MM
    std::string getEndTime(); // -||-
    void getAllInfo(); //print all import information to console
    int getYear();
    int getMonth();
    int getDay();
    int getStartHours();
    int getStartMinutes();
    int getEndHours();
    int getEndMinutes();

    //setters
    void setName(); //Set events name
    void setDescription(); //Set description of event
    void setEventStart(); //Set event start time (HH:MM)
    void setEventEnd(); //Set events end time (HH::MM)
    void setEventDate(); //Set events date (YYYY:MM:DD)

    bool is_integer(int);
};
