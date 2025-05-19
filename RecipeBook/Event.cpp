#include "Event.h"
#include <iostream>

Event::Event(const std::string& eventText, const std::string& next)
    : text(eventText), nextFile(next) 
{
}

Event::~Event()
{
}

void Event::DisplayEvent() const
{
    std::cout << "\33[97m" << text << "\33[0m" << std::endl;
}

std::string Event::GetNextEvent() const
{
	return nextFile;
}