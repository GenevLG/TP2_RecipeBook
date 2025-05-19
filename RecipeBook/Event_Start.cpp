#include "Event_Start.h"
#include <iostream>
#include "Menu.h"

Event_Start::~Event_Start() {}

void Event_Start::DisplayIntro()
{
    std::cout << "\33[33m\tBienvenue dans l’aventure !\n";
    std::cout << "\tLa Princesse et le Dragon commence maintenant...\33[0m\n";

    Menu::DisplayEventMenu();
}

