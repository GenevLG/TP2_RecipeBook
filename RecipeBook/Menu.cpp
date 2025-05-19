#include "Book.h"
#include <iostream>
#include <conio.h>

void Book::MenuEvent(const std::string& nextFile)
{
    char userChoice;
    while (true)
    {
        std::cout << "\33[96m ----------------------------------------------------------\33[0m"<< std::endl;
        std::wcout << L"\n\33[96m|\33[0m Continuer [ENTER] \33[96m||\33[0m Retour en arrière [B] \33[96m||\33[0m Sortir [E] \33[96m|\33[0m" << std::endl;
        std::cout << "\33[96m\n ----------------------------------------------------------\33[0m\n\n" << std::endl;

        userChoice = _getch();
        if (userChoice == '\r')
        {
            if (!nextFile.empty())
            {
                currentFile = storyFile + nextFile;
                std::cout << "Chargement du fichier suivant : " << currentFile << std::endl;
                LoadFile(currentFile);
            }
            else
            {
                std::wcout << L"\33[31mAucun fichier suivant spécifié...\33[0m" << std::endl;
            }
        }
        else if (userChoice == 'B' || userChoice == 'b')
        {
            std::cout << "Retour...\n";
            GoBack();
        }
        else if (userChoice == 'E' || userChoice == 'e')
        {
            std::cout << "Merci d'avoir joué !\n";
            std::cin.get(); 
            exit(0);
        }
        else
        {
            std::wcout << L"\33[31mEntrée invalide, veuillez entrer une commande valide.\33[0m" << std::endl;
        }
    }
}

void Book::MenuChoices(const std::string* choices, const std::string* nextFiles, int choiceCount)
{
    char userChoice;
    while (true)
    {
        std::cout << "\33[96m ----------------------------------------------------------------------------\33[0m\n";
        for (int i = 0; i < choiceCount; ++i)
        {
            std::cout << "\33[96m|\33[0m Choix [" << i + 1 << "] \33[96m|\33[0m";
        }
        std::wcout << L"\33[96m|\33[0m Retour en arrière [B] \33[96m||\33[0m Sortir [E] \33[96m|\33[0m";
        std::cout << "\33[96m\n ----------------------------------------------------------------------------\33[0m\n\n";

        userChoice = _getch();
        if (userChoice >= '1' && userChoice < '1' + choiceCount)
        {
            int choiceIndex = userChoice - '1';
            std::cout << "Chargement du fichier suivant : " << nextFiles[choiceIndex] << std::endl;
            currentFile = storyFile + nextFiles[choiceIndex];
            LoadFile(currentFile);
        }
        else if (userChoice == 'B' || userChoice == 'b')
        {
            std::cout << "Retour...\n";
            GoBack();
        }
        else if (userChoice == 'E' || userChoice == 'e')
        {
            std::cout << "Merci d'avoir joué !\n";
            std::cin.get();
            exit(0);
        }
        else
        {
            std::wcout << L"\33[31mEntrée invalide, veuillez entrer une commande valide.\33[0m" << std::endl;
        }
    }
}

void Book::MenuEnd()
{
    char userChoice;
    while (true) 
    {
        std::cout << "\33[96m -------------------------------------\33[0m";
        std::wcout << L"\33[96m\n|\33[0m Retour en arrière [B] \33[96m||\33[0m Sortir [E] \33[96m|\33[0m";
        std::cout << "\33[96m\n -------------------------------------\33[0m\n\n";

        userChoice = _getch();
        if (userChoice == 'B' || userChoice == 'b')
        {
            std::cout << "Retour...\n";
            GoBack();
        }
        else if (userChoice == 'E' || userChoice == 'e')
        {
            std::cout << "Merci d'avoir joué !\n";
            std::cin.get();
            exit(0);
        }
        else
        {
            std::wcout << L"\33[31mEntrée invalide, veuillez entrer une commande valide.\33[0m" << std::endl;
        }
    }
}
