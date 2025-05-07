#include "Event.h"
#include <iostream>

Event::Event(const std::string& eventText, const std::string& next)
    : text(eventText), nextFile(next) 
{
}

Event::~Event()
{
}

std::string* Event::GetChoice(int& count) const 
{
    count = 0;
    return nullptr;
}