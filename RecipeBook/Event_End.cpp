#include "Event_End.h"
#include <iostream>
#include <conio.h>
#include "Menu.h"

Event_End::Event_End(const std::string& eventText)
    : Event(eventText, "") 
{
}

Event_End::~Event_End()
{
}

void Event_End::MenuEnd() const
{
    Menu::EndMenu();
}