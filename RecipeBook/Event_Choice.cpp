#include "Event_Choice.h"
#include <iostream>
#include <conio.h> //Pour le _getch() utilisé dans les menus
#include "Menu.h"

Event_Choice::Event_Choice(const std::string& choiceText, int choiceCount, std::string* choices)
    : Event(choiceText, ""), choiceCount(choiceCount), choices(nullptr)
{
    // Allouer et copier les choix dans un tableau dynamique
    choices = new std::string[choiceCount]; // Allocation avec new[]
    for (int i = 0; i < choiceCount; ++i)
    {
        choices[i] = choices[i]; // Copie des choix
    }
}

Event_Choice::~Event_Choice()
{
    delete[] choices;
}

void Event_Choice::ChoiceMenu() const
{
    Menu::ChoiceMenu(choices, choiceCount);
}

std::string* Event_Choice::GetChoice(int& count) const
{
    count = choiceCount;
    return choices; // Renvoie le tableau de choix
}

std::string Event_Choice::GetNextEvent() const
{
    std::cout << "Debug - Accès à nextFile : " << nextFile << std::endl;
    return nextFile; // Renvoie le fichier suivant
}