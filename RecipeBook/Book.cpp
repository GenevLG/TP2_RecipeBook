#include "Book.h"
#include <iostream>
#include <fstream>
#include <string>
#include <conio.h> //Pour le _getch() utilisé dans les menus
//#include <map>
#include <locale>

using namespace std;

const string RESET = "\033[0m";
const string WHITEBRIGHT = "\u001B[97m";
const string GREY = "\033[90m";

Book::Book(const std::string& file)
    : storyFile(file), currentFile(""), historyOfChoices(nullptr), historyCount(0), maxHistory(100) 
{
    std::locale::global(std::locale("fr_FR.UTF-8")); // Définit la locale globale
    std::wcout.imbue(std::locale());
    historyOfChoices = new std::string[maxHistory];
}

Book::~Book() 
{
    delete[] historyOfChoices;
}

//////////////////////////////////////////////////////////////////////////
//Tableau de l'historique des choix (pour le GoBack)
void Book::GetHistoryOfChoices()
{
    maxHistory *= 2;
    std::string* newHistory = new std::string[maxHistory];
    for (int i = 0; i < historyCount; ++i)
    {
        newHistory[i] = historyOfChoices[i];
    }
    delete[] historyOfChoices;
    historyOfChoices = newHistory;
}

//////////////////////////////////////////////////////////////////////////
//Revenir au fichier précédent
void Book::GoBack()
{
    if (historyCount > 1)
    {
        historyCount--;
        std::string previousFile = historyOfChoices[historyCount - 1];
        //Le fichier Start fonctionne indépendament des autres, donc 
        //      doit être rappeler spécifiquement
        if (previousFile.find("Start.event") != std::string::npos)
        {
            std::string startFile = storyFile + "Start.event";
            std::wcout << L"\33[95;2;3m-- Retour à l'accueil\33[0m\n" << std::endl;
            Start(); 
        }
        else
        {
            std::wcout << L"\33[95;2;3m-- Vous êtes revenu à : " << std::endl; std::cout << previousFile << "\33[0m\n" << std::endl;
            LoadFile(previousFile);
        }
    }
    else
    {
        std::wcout << L"\33[31mImpossible de revenir en arrière. Vous êtes au début de l'histoire!\33[0m" << std::endl;
    }
}

//////////////////////////////////////////////////////////////////////////
// Charger et lire les fichiers 
void Book::LoadFile(const std::string& filePath)
{
    currentFile = filePath; // Mettre à jour currentFile
    if (historyCount > 0 && historyOfChoices[historyCount - 1] != filePath)
    {
        //------- Historique -------
        if (historyCount == maxHistory)
        {
            GetHistoryOfChoices();
        }
        historyOfChoices[historyCount] = filePath;
        historyCount++;
    }
    //--------------------------
    //Charger un fichier
    std::ifstream file(filePath);
    if (!file.is_open())
    {
        std::cout << "\33[31mErreur : Impossible d'ouvrir le fichier \33[0m" << filePath << std::endl;
        return;
    }
    std::string line, text = "", nextFile = "", textChoice = "";
    std::string* choices = new std::string[100]; //Tableau pour stocker les textes des choix
    std::string* nextFiles = new std::string[100]; //Tableau pour stocker les chemins des fichiers suivants
    int choiceCount = 0; //Nombre total de choix
    bool insideChoices = false;
    bool isEnd = false;
    //Lecture ligne par ligne
    while (std::getline(file, line))
    {
        //std::cout << line << std::endl;
        if (line.find("<Text>") != std::string::npos)
        {
            text += RemoveTags(line, "<Text>", "</Text>") + "\n";
        }
        else if (line.find("<Next>") != std::string::npos)
        {
            nextFile = RemoveTags(line, "<Next>", "</Next>") + ".event";
        }
        else if (line.find("<Choices>") != std::string::npos)
        {
            insideChoices = true;
            choiceCount = 0;
            while (std::getline(file, line) && line.find("</Choices>") == std::string::npos)
            {
                text += RemoveTags(line, "<Text>", "</Text>") + "\n";
                //std::cout << line << std::endl;
                if (line.find("<Choice>") != std::string::npos)
                {                  
                    std::string choiceText = "", choiceNextFile = "";
                    // Lire le contenu de chaque choix
                    while (std::getline(file, line) && line.find("</Choice>") == std::string::npos)
                    {
                        text += RemoveTags(line, "<Text>", "</Text>") + "\n";
                        //std::cout << line << std::endl;
                        if (line.find("<Text>") != std::string::npos)
                        {
                            choiceText = RemoveTags(line, "<Text>", "</Text>");
                        }
                        else if (line.find("<Next>") != std::string::npos)
                        {
                            choiceNextFile = RemoveTags(line, "<Next>", "</Next>") + ".event";
                        }
                    }
                    //Stocker le choix et le fichier suivant
                    if (!choiceText.empty() && !choiceNextFile.empty() && choiceCount < 100)
                    {
                        choices[choiceCount] = choiceText;
                        nextFiles[choiceCount] = choiceNextFile;
                        choiceCount++;
                    }
                }
            }
        }
        else if (line.find("<End>") != std::string::npos)
        {           
            isEnd = true;
        }
    }
    file.close();//Fermer le fichier après la lecture
    //Afficher le texte sans les balises
    std::cout<< WHITEBRIGHT << text << RESET << std::endl;
    std::cout << textChoice << std::endl;
    //Gestion des menus
    if (isEnd)
    {
        MenuEnd();
    }
    else if (insideChoices)
    {
        MenuChoices(choices, nextFiles, choiceCount);
    }
    else
    {
        MenuEvent(nextFile);
    }
    //Libérer la mémoire
    delete[] choices;
    choices = nullptr;
    delete[] nextFiles;
    nextFiles = nullptr;
}

//////////////////////////////////////////////////////////////////////////
// Démarrer le début de l'histoire
void Book::Start()
{
    std::string startFile = storyFile + "Start.event";
    std::ifstream file(startFile);
    std::string nextFile;
    std::string line;
    std::string text;
    //------- Historique -------
    if (historyCount == maxHistory)
    {
        GetHistoryOfChoices();
    }
    historyOfChoices[historyCount] = startFile;
    historyCount++;
    //--------------------------   
    std::cout << "\33[33m";
    std::cout << "\t\33[33;5m*      *     *       *   *   *\33[33;0m\n";
    std::cout << "\33[33;5m    *\33[33;0m    *    *        \33[33m*\33[33;0m    *     \33[33;5m*    *\33[33;0m\n";
    std::cout << "\t\33[33;5m    *       *    *      *   *    *     \33[33;0m\n";
    std::cout << "\t \33[96mLa Princesse et le Dragon\33[0m\n";
    std::cout << "\33[33;5m    *\33[33;0m    *    *        \33[33m*\33[33;0m    *     \33[33;5m*    *\33[33;0m\n";
    std::cout << "\33[33;5m    *       *    *      *   *    *     \33[33;0m\n";
    std::cout << "\33[0m";
    std::cout << "\t   *            \033[90mT~~\033[0m     \n";
    std::cout << "\t        \33[33;5m*\33[0m       \033[90m|\033[0m";
    //Lecture du fichier ligne par ligne
    while (std::getline(file, line))
    {
        //std::cout << line << std::endl;
        if (line.find("<Text>") != std::string::npos)
        {
            text += RemoveTags(line, "<Text>", "</Text>") + "\n";
        }
        else if (line.find("<Next>") != std::string::npos)
        {
            nextFile = RemoveTags(line, "<Next>", "</Next>") + ".event";
        }
    }
    file.close(); // Fermer le fichier
    std::cout << GREY << text << RESET << std::endl;
    std::cout << "\t     Bonne lecture!" << std::endl;
    std::cout << "\n\n\33[96mAppuyez sur \33[5mENTER\33[0m \33[96mpour commencer...\n\33[0m" << std::endl;
    //Attendre que l'utilisateur appuie sur ENTER
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Attendre un appui sur ENTER
    //Charger le fichier suivant, si spécifié
    if (!nextFile.empty())
    {
        currentFile = storyFile + nextFile;
        LoadFile(currentFile); // Charger le fichier suivant
    }
    else 
    {
        std::wcout << L"\33[31mAucun fichier suivant spécifié comme étant le suivant...\33[0m" << std::endl;
    }
}

//////////////////////////////////////////////////////////////////////////
//Pour enlever le balise de l'affichage des fichiers
std::string Book::RemoveTags(const std::string& line, const std::string& openTag, const std::string& closeTag)
{
    size_t start = line.find(openTag) + openTag.length();
    size_t end = line.find(closeTag, start);
    if (start != std::string::npos && end != std::string::npos)
    {
        return line.substr(start, end - start);
    }
    return ""; // Retourne une chaîne vide si les balises ne sont pas trouvées
}

//////////////////////////////////////////////////////////////////////////
// MENU 
//////////////////////////////////////////////////////////////////////////

//------- EVENT -------
void Book::MenuEvent(const std::string& nextFile)
{
    char userChoice;
    while (true)
    {
        std::cout << "\33[96m ----------------------------------------------------------\33[0m";
        std::wcout << L"\n\33[96m|\33[0m Continuer [ENTER] \33[96m||\33[0m Retour en arrière [B] \33[96m||\33[0m Sortir [E] \33[96m|\33[0m";
        std::cout << "\33[96m\n ----------------------------------------------------------\33[0m\n\n";
        userChoice = _getch(); //Le choix s'execute dès l'entré de la commande
        if (userChoice == '\r') 
        {
            if (!nextFile.empty()) 
            {
                currentFile = storyFile + nextFile;
                LoadFile(currentFile); //Charge le fichier suivant
            }
            else 
            {
                std::wcout << L"\33[31mAucun fichier suivant spécifié comme étant le suivant...\33[0m" << std::endl;
            }
        }
        else if (userChoice == 'B' || userChoice == 'b') 
        {
            GoBack(); //Retourner au fichier précédent
        }
        else if (userChoice == 'E' || userChoice == 'e') 
        {
            std::cout << "\33[95m\nNoooo!\33[0m" << std::endl;
            exit(0); //Quitter le programme
        }
        else 
        {
            std::wcout << L"\33[31mEntrée invalide, veuillez entrer une commande valide.\33[0m" << std::endl;
        }
    }
}

//------- CHOICES -------
void Book::MenuChoices(const std::string* choices, const std::string* nextFiles, int choiceCount)
{
    char userChoice;
    while (true) 
    {
        std::cout << "\33[96m ----------------------------------------------------------------------------\33[0m\n";
        for (int i = 0; i < choiceCount; ++i) 
        {
            std::cout << "\33[96m|\33[0m Choix ["<< i + 1 <<"] \33[96m|\33[0m";
        }
        std::wcout << L"\33[96m|\33[0m Retour en arrière [B] \33[96m||\33[0m Sortir [E] \33[96m|\33[0m";
        std::cout << "\33[96m\n ----------------------------------------------------------------------------\33[0m\n\n";
        userChoice = _getch(); //Le choix s'execute dès l'entré de la commande
        if (userChoice >= '1' && userChoice <= '0' + choiceCount) 
        {
            // Charger le fichier correspondant au choix
            int choiceIndex = userChoice - '1';
            currentFile = storyFile + nextFiles[choiceIndex];
            LoadFile(currentFile); // Charge le fichier correspondant
        }
        else if (userChoice == 'B' || userChoice == 'b') 
        {
            GoBack();
        }
        else if (userChoice == 'E' || userChoice == 'e') 
        {
            std::cout << "\33[95m\nNoooo!\33[0m" << std::endl;
            exit(0);
        }
        else 
        {
            std::wcout << L"\33[31mEntrée invalide, veuillez entrer une commande valide.\33[0m" << std::endl;
        }
    }
}

//------- END -------
void Book::MenuEnd()
{
    char userChoice;
    while (true) 
    {
        std::cout << "\33[96m -------------------------------------\33[0m";
        std::wcout << L"\33[96m\n|\33[0m Retour en arrière [B] \33[96m||\33[0m Sortir [E] \33[96m|\33[0m";
        std::cout << "\33[96m\n -------------------------------------\33[0m\n\n";
        userChoice = _getch(); //Le choix s'execute dès l'entré de la commande
        if (userChoice == 'B' || userChoice == 'b') 
        {
            GoBack(); // Retourner au fichier précédent
        }
        else if (userChoice == 'E' || userChoice == 'e') 
        {
            std::cout << "\t\33[95m\nNoooo!\33[0m" << std::endl;
            exit(0); 
        }
        else 
        {
            std::wcout << L"\33[31mEntrée invalide, veuillez entrer une commande valide.\33[0m" << std::endl;
        }
    }
}

