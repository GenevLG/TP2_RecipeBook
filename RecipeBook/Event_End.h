#pragma once
#include "Event.h"

class Event_End : public Event 
{
public:
    Event_End(const std::string& eventText);
    
    ~Event_End();
};