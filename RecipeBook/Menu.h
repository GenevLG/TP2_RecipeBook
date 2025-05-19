#pragma once
#include <string>
#include "Book.h"

class Menu
{
public:
    static void EventMenu(Book& book, const std::string& nextFile);
    static void ChoiceMenu(Book& book, const std::string* choices, const std::string* nextFiles, int choiceCount);
    static void EndMenu();
};
