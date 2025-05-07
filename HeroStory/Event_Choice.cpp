#include "Event_Choice.h"
#include <iostream>

Event_Choice::Event_Choice(const std::string& choiceText, int choiceCount, std::string* choices)
    : Event(choiceText, ""), choiceCount(choiceCount) 
{
    // Allouer et copier les choix dans le tableau
    this->choices = new std::string[choiceCount];
    for (int i = 0; i < choiceCount; ++i) 
    {
        this->choices[i] = choices[i];
    }
}

Event_Choice::~Event_Choice() 
{
    delete[] choices; 
}

//bool Event_Choice::DisplayChoice() const 
//{
//    return choiceCount > 0; 
//}
//
//std::string* Event_Choice::GetChoice(int& count) const 
//{
//    count = choiceCount; 
//    return choices;      
//}
