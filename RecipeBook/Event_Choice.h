#pragma once
#include "Event.h"

class Event_Choice : public Event 
{
    private:
        std::string* choices; 
        int choiceCount; 

    public:
        Event_Choice(const std::string& choiceText, int choiceCount, std::string* choices);
        ~Event_Choice();

        void DisplayChoiceMenu() const override; // Nouvelle méthode  
        std::string* GetChoice(int& count) const override;
        std::string GetNextEvent() const override;
};