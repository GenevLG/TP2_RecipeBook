#include <string>

class Book 
{
    private:
        std::string currentFile; //Le fichier actuellement charg�
        std::string storyFile; //R�pertoire des fichiers `.event`
        std::string* historyOfChoices; //Tableau dynamique pour stocker l'historique
        int historyCount; //Nombre de fichiers dans l'historique
        int maxHistory; //Capacit� maximale de l'historique
    
        void LoadFile(const std::string& filePath); //Charger les fichiers
        void GetHistoryOfChoices(); //Historique des choix (pour le GoBack)

    public:
        Book(const std::string& file); 
        ~Book(); 
    
        void Start(); //D�marrer le d�but de l'histoire
        void GoBack(); //Revenir en arri�re

        std::string RemoveTags(const std::string& line, const std::string& openTag, const std::string& closeTag);
        
        void MenuEvent(const std::string& nextFile);
        void MenuChoices(const std::string* choices, const std::string* nextFiles, int choiceCount);
        void MenuEnd();
};
