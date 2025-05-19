#pragma once
#include "IEvent.h"
#include <string>

class Event : public IEvent
{
	protected:
	std::string text; // Texte principal
	std::string nextFile; // Fichier suivant	

	public:
		Event(const std::string& eventText, const std::string& next);
		virtual ~Event();
	
		void DisplayEvent() const; // Ajout pour l'affichage de l'événement
		std::string GetNextEvent() const; // Obtenir le fichier suivant
};
