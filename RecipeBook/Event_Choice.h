#pragma once
#include "Event.h"

class Event_Choice : Event 
{
    private:
        std::string* choices; 
        int choiceCount; 

    public:
        Event_Choice(const std::string& choiceText, int choiceCount, std::string* choices);
        ~Event_Choice();
    
        //bool DisplayChoice() const override;
        //std::string* GetChoice(int& count) const override;
};